#ifndef DSP_H
#define DSP_H

#include "util.h"
#include "filters.h"

namespace DSP
{
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

  static const int16_t __not_in_flash_func(process_ssb_tx)(const int16_t s,const bool mode_LSB,const float mic_gain)
  {
    // generate an SSB signal at FS/4 (7812 Hz)
    // 1. bandpass filter (300 - 2400)
    // 2. upconvert to FS/4 (mix with BFO at FS/4)
    // 3. remove unwanted sideband (LPF/HPF at FS/4)

    // BFO oscillates
    static uint8_t bfo = 0;
    const uint8_t phase = bfo & 0x03;
    bfo++;

    // bandpass filter mic signal
    const float bpf2400 = FILTER::bpf_300_2400f_tx((float)s / 8192.0f);

    // up convert to FS/4
    // LO signal reduces to 0, 1 and -1 at FS/4
    // note, 6dB loss
    float v = 0;
    switch (phase)
    {
      case 0: v = +bpf2400; break;
      case 2: v = -bpf2400; break;
    }

    // remove the unwanted sideband
    v = mode_LSB?FILTER::lpf_fs4f_tx(v):FILTER::hpf_fs4f_tx(v);

    // make up for 6dB loss
    return (int16_t)(v * mic_gain * 2.0f * 512.0f);
  }

  static const int16_t __not_in_flash_func(process_am_tx)(const int16_t s,const float mic_gain)
  {
    // generate an AM signal at FS/4 (7812 Hz)
    // 1. bandpass filter (300 - 2400)
    // 2. Add DC
    // 2. upconvert to FS/4 (mix with BFO at FS/4)

    // BFO oscillates
    static uint8_t bfo = 0;
    const uint8_t phase = bfo & 0x03;
    bfo++;

    // setup DC bias for AM
    static const float DC = 0.25f;

    // bandpass filter
    const float bpf2400 = FILTER::bpf_300_2400f_tx((float)s * mic_gain * (1.0f / 8192.0f / 4.0f)) + DC;

    // up convert to FS/4
    float v = 0;
    switch (phase)
    {
      case 0: v = +bpf2400; break;
      case 2: v = -bpf2400; break;
    }

    // convert to 10 bit integer
    return (int16_t)(v * 512.0f);
  }

  volatile static float agc_peak = 0.0f;

  static const int16_t __not_in_flash_func(agc)(const float in)
  {
    // limit gain to max of 40 (32db)
    static const float max_gain = 40.0f;
    // about 10dB per second
    static const float k = 0.99996f;

    const float magnitude = fabsf(in);
    if (magnitude>agc_peak)
    {
      agc_peak = magnitude;
    }
    else
    {
      agc_peak *= k;
    }

    // trap issues with low values
    if (agc_peak<1.0f) return (int16_t)(in * max_gain);

    // set maximum gain possible for 12 bits DAC
    const float m = 2047.0f/agc_peak;
    return (int16_t)(in*fminf(m,max_gain));
  }

  static const uint8_t __not_in_flash_func(smeter)(void)
  {
    // S9 = -73dBm = 141uV PP
    // measured 50 after SSB processing
    // need to return 10 for S9
    static const float S0_sig = 5.0f;
    static const float S9_sig = 25.0f;
    static const float S9p_sig = 1024.0f;
    static const uint32_t S9_from_min = (uint32_t)(log10f(S0_sig) * 1024.0f);
    static const uint32_t S9_from_max = (uint32_t)(log10f(S9_sig) * 1024.0f);
    static const uint32_t S9_min = 0ul;
    static const uint32_t S9_max = 10ul;
    static const uint32_t S9p_from_min = (uint32_t)(log10f(S9_sig) * 1024.0f);
    static const uint32_t S9p_from_max = (uint32_t)(log10f(S9p_sig) * 1024.0f);
    static const uint32_t S9p_min = 11ul;
    static const uint32_t S9p_max = 15ul;
    if (agc_peak<1.0f)
    {
      return 0u;
    }
    const uint32_t log_peak = (uint32_t)(log10f(agc_peak) * 1024.0f);
    if (agc_peak>S9_sig)
    {
      return (uint8_t)UTIL::map(log_peak,S9p_from_min,S9p_from_max,S9p_min,S9p_max);
    }
    return (uint8_t)UTIL::map(log_peak,S9_from_min,S9_from_max,S9_min,S9_max);
  }

  static const int16_t __not_in_flash_func(process_cw_rx)(const int16_t s,const uint32_t phase)
  {
    // demodulate a CW signal at FS/4 (7812 Hz)
    // 1. narrow bandpass at FS/4
    // 2. down-convert to baseband (mix with BFO at FS/4 +/- sidetone)
    // 3. lowpass at FS/4 remove mixing image

    // set up DDS BFO
    volatile static uint32_t dds = 0;

    // narrow bandpass (also removes DC)
    const float m = FILTER::bpf_fs4f_cw((float)s / 8192.0f);

    // mix with BFO
    const float bfo = (float)UTIL::sin_tab[dds>>22] / 32768.0f;
    float v = m * bfo;

    // remove image after mixing
    v = FILTER::bpf_500_1500f_cw(v);

    // update DDS
    dds += phase;
    return agc(v * 8192.0f);
  }

  static const int16_t __not_in_flash_func(process_ssb_rx)(const int16_t s,const bool mode_LSB)
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
    float v = FILTER::hpf_fs8f_rx((float)s / 8192.0f);

    // remove the unwanted sideband
    v = mode_LSB?FILTER::lpf_fs4f_rx(v):FILTER::hpf_fs4f_rx(v);

    // down convert from FS/4
    // note LO signal reduces to 0, 1 and -1 at FS/4
    float m = 0;
    switch (phase)
    {
      case 0: m = +v; break;
      case 2: m = -v; break;
    }

    // 300Hz - 2400Hz BPF
    v = FILTER::bpf_300_2400f_rx(m);
    return agc(v * 8192.0f);
  }

  static const int16_t __not_in_flash_func(process_amn_rx)(const int16_t s)
  {
    // AM Narrow
    // demodulate an AM signal at FS/4 (7812 Hz)
    // 1. bandpass filter AM signal (6KHz)
    // 2. down-convert to baseband (mix with BFO at FS/4 - note, this reduces to ABS()!)
    // 3. get magnitude of IQ signal (AM)
    // 4. remove DC bias
    // 5. filter out carrier

    // bandpass AM signal
    float v = FILTER::bpf_fs4f_amn((float)s / 8192.0f);

    // quadrature mixer and magnitude (rectify)!
    v = fabsf(v);

    // remove DC and filter
    v = FILTER::bpf_300_3000f_rx(FILTER::dcf(v));
    return agc(v * 8192.0f);
  }

  static const int16_t __not_in_flash_func(process_amw_rx)(const int16_t s)
  {
    // AM Wide
    // demodulate an AM signal at FS/4 (7812 Hz)
    // 1. bandpass filter AM signal (6KHz)
    // 2. down-convert to baseband (mix with BFO at FS/4 - note, this reduces to ABS()!)
    // 3. get magnitude of IQ signal (AM)
    // 4. remove DC bias
    // 5. filter out carrier

    // bandpass AM signal
    float v = FILTER::bpf_fs4f_amw((float)s / 8192.0f);

    // quadrature mixer and magnitude (rectify)!
    v = fabsf(v);

    // remove DC and filter
    v = FILTER::bpf_100_4000f_rx(FILTER::dcf(v));
    return agc(v * 8192.0f);
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
}
#endif