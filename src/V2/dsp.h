#ifndef DSP_H
#define DSP_H

#include "util.h"
#include "filters.h"

static const uint32_t __not_in_flash_func(get_mic_peak_level)(const int16_t mic_in)
{
  static const uint32_t MIC_LEVEL_DECAY_RATE = 50ul;
  static const uint32_t MIC_LEVEL_HANG_TIME = 1000ul;
  static uint32_t mic_peak_level = 0;
  static uint32_t mic_level_update = 0;
  static uint32_t mic_hangtime_update = 0;
  const uint32_t now = millis();
  const uint32_t mic_level = abs(mic_in)>>9;
  if (mic_level>mic_peak_level)
  {
    mic_peak_level = mic_level;
    mic_level_update = now + MIC_LEVEL_DECAY_RATE;
    mic_hangtime_update = now + MIC_LEVEL_HANG_TIME;
  }
  else
  {
    if (now>mic_hangtime_update)
    {
      if (now>mic_level_update)
      {
        if (mic_peak_level) mic_peak_level--;
        mic_level_update = now + MIC_LEVEL_DECAY_RATE;
      }
    }
  }
  return mic_peak_level;
}

static const int16_t __not_in_flash_func(process_ssb_tx)(const int16_t s,const bool mode_LSB)
{
  // generate an SSB signal at FS/4 (7812 Hz)
  // 1. bandpass filter (300 - 2400)
  // 2. upconvert to FS/4 (mix with BFO at FS/4)
  // 3. remove unwanted sideband (LPF/HPF at FS/4)
  volatile static int32_t alc = 256L;

  // BFO oscillates
  static uint8_t bfo = 0;
  const uint8_t phase = bfo & 0x03;
  bfo++;

  // bandpass filter mic signal
  const int16_t bpf2400 = FILTER::bpf_300_2400_tx(s);

  // up convert to FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t v = 0;
  switch (phase)
  {
    case 0: v = +bpf2400; break;
    case 2: v = -bpf2400; break;
  }

  // remove the unwanted sideband
  v = mode_LSB?FILTER::lpf_fs4_tx(v):FILTER::hpf_fs4_tx(v);

  // ALC
  v = (int16_t)(((int32_t)v * alc) >> 8);
  if (abs(v)>511) alc--;

  return v;
}

static const int16_t __not_in_flash_func(process_am_tx)(const int16_t s)
{
  // generate an AM signal at FS/4 (7812 Hz)
  // 1. bandpass filter (300 - 2400)
  // 2. Add DC
  // 2. upconvert to FS/4 (mix with BFO at FS/4)
  volatile static int32_t alc = 256L;

  // BFO oscillates
  static uint8_t bfo = 0;
  const uint8_t phase = bfo & 0x03;
  bfo++;

  // setup DC bias for AM
  static const int16_t DC = 256l;

  // bandpass filter
  const int16_t bpf2400 = FILTER::bpf_300_2400_tx(s>>5) + DC;

  // up convert to FS/4
  int16_t v = 0;
  switch (phase)
  {
    case 0: v = +bpf2400; break;
    case 2: v = -bpf2400; break;
  }

  // ALC
  v = (int16_t)(((int32_t)v * alc) >> 8);
  if (abs(v)>511) alc--;

  return v;
}

volatile static float agc_peak = 0.0f;

static const int16_t __not_in_flash_func(agc)(const int16_t in)
{
  const float magnitude = (float)abs(in);
  if (magnitude>agc_peak)
  {
    agc_peak = magnitude;
  }
  else
  {
    // 0.99996 is about 10dB per second
    agc_peak *= 0.99996f;
  }

  // set maximum gain possible for 12 bits DAC
  const float m = 2047.0f/agc_peak;

  // limit gain to max of 40 (32db)
  const float max_gain = 40.0f;
  return (int16_t)((float)in*min(m,max_gain));
}

static const uint8_t __not_in_flash_func(smeter)(void)
{
  // S9 = peak of 50 (measured)
  uint8_t s = 0;
  if (agc_peak<5.0f) return s;
  if (agc_peak<50)
  {
    s = (uint8_t)roundf((log10f(agc_peak-4.0f)*5.4f));
  }
  else
  {
    s = (uint8_t)roundf((log10f(agc_peak-4.0f)*4.5f));
    if (s<9) s = 9;
  }
  return s;
}

static const int16_t __not_in_flash_func(process_cw_rx)(const int16_t s,const uint32_t phase,const bool higain)
{
  // demodulate a CW signal at FS/4 (7812 Hz)
  // 1. narrow bandpass at FS/4
  // 2. downconvert to baseband (mix with BFO at FS/4 +/- sidetone)
  // 3. lowpass at FS/4 remove mixing image

  // set up DDS BFO
  volatile static uint32_t dds = 0;

  // narrow bandpass (also removes DC)
  const int32_t m = (int32_t)FILTER::bpf_fs4_cw(s);

  // mix with BFO
  const int32_t bfo = (int32_t)sin_tab[dds>>22];
  int16_t v = (int16_t)((m * bfo)>>15);

  // recover 6dB loss and remove image after mixing
  v = FILTER::bpf_500_1500_cw(v<<1);

  // extra gain for CW
  v <<= 1;

  // noise reduction
  v = FILTER::ma_order_4(v<<1);
  
  // AGC will fix it
  if (higain) v <<= 1;
  v = agc(v);

  // update DDS
  dds += phase;
  return v;
}

static const int16_t __not_in_flash_func(process_ssb_rx)(const int16_t s,const bool mode_LSB,const bool higain)
{
  // demodulate an SSB signal at FS/4 (7812 Hz)
  // 1. remove DC (FS/8 HPF)
  // 2. remove unwanted sideband (LPF/HPF at FS/4)
  // 3. downconvert to baseband (mix with BFO at FS/4)
  // 4. bandpass filter (300 - 2400)

  // BFO oscillates
  volatile static uint8_t bfo = 0;
  const uint8_t phase = bfo & 0x03;
  bfo++;

  // remove DC
  int16_t v = FILTER::hpf_fs8_rx(s);

  // remove the unwanted sideband
  v = mode_LSB?FILTER::lpf_fs4_rx(v):FILTER::hpf_fs4_rx(v);

  // down convert from FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t m = 0;
  switch (phase)
  {
    case 0: m = +v; break;
    case 2: m = -v; break;
  }

  // 300Hz - 2400Hz BPF
  v = FILTER::bpf_300_2400_rx(m<<1);

  if (higain) v <<= 1;
  v = agc(v);
  return v;
}

static const int16_t __not_in_flash_func(process_amn_rx)(const int16_t s,const bool higain)
{
  // AM Narrow
  // demodulate an AM signal at FS/4 (7812 Hz)
  // 1. bandpass filter AM signal (6KHz)
  // 2. down-convert to baseband (mix with BFO at FS/4 - note, this reduces to ABS()!)
  // 3. get magnitude of IQ signal (AM)
  // 4. remove DC bias
  // 5. filter out carrier

  // bandpass AM signal
  int16_t v = FILTER::bpf_fs4_amn(s);

  // quadrature mixer and magnitude (rectify)!
  v = abs(v);

  // remove DC and filter
  //v = FILTER::lpf_fs8_rx(FILTER::dc(v));
  v = FILTER::lpf_3000_rx(FILTER::dc(v));

  // more gain on higher bands
  if (higain) v <<= 1;
  v = agc(v);
  return v;
}

static const int16_t __not_in_flash_func(process_amw_rx)(const int16_t s,const bool higain)
{
  // AM Wide
  // demodulate an AM signal at FS/4 (7812 Hz)
  // 1. bandpass filter AM signal (6KHz)
  // 2. down-convert to baseband (mix with BFO at FS/4 - note, this reduces to ABS()!)
  // 3. get magnitude of IQ signal (AM)
  // 4. remove DC bias
  // 5. filter out carrier

  // bandpass AM signal
  int16_t v = FILTER::bpf_fs4_amw(s);

  // quadrature mixer and magnitude (rectify)!
  v = abs(v);

  // remove DC and filter
  v = FILTER::lpf_fs4_rx(FILTER::dc(v));

  // more gain on higher bands
  if (higain) v <<= 1;
  v = agc(v);
  return v;
}

static const int16_t __not_in_flash_func(jnr)(const int16_t s,const uint32_t level)
{
  // just noise reduction (not dynamic)
  switch (level)
  {
    case 1: return FILTER::jnr_maf1(s);
    case 2: return FILTER::jnr_maf2(FILTER::jnr_maf1(s));
    case 3: return FILTER::jnr_maf4(FILTER::jnr_maf3(FILTER::jnr_maf2(FILTER::jnr_maf1(s))));
  }
  return s;
}

#endif