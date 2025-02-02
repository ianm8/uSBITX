/*
 * uSBITX Version 3.2.225
 *
 * Copyright 2024 Ian Mitchell VK7IAN
 * Licenced under the GNU GPL Version 3
 *
 * libraries
 *
 * https://github.com/Bodmer/TFT_eSPI
 *
 * Important:
 *   Copy "User_Setup.h" to  ..\Arduino\libraries\TFT_eSPI whenever the TFT_eSPI library is installed
 *   Important Note, there is a bug in version that requires the following change in TFT_eSPI_RP2040.h:
 *
 *     #define SET_BUS_READ_MODE  // spi_set_format(SPI_X,  8, (spi_cpol_t)0, (spi_cpha_t)0, SPI_MSB_FIRST)
 *
 *   that is, comment out: spi_set_format(SPI_X,  8, (spi_cpol_t)0, (spi_cpha_t)0, SPI_MSB_FIRST)
 *
 * Build:
 *  Pico 2
 *  CPU Speed: 225Mhz
 *  Optimize: -O2
 *  USB Stack: No USB
 *  Flash Size: 4MB (Sketch: 4032KB, FS: 64KB)
 *
 * Some history
 *  0.7.255 fixed bug in auto mode
 *  0.8.255 fixed bug in spectrum dynamic range
 *  0.9.255 fixed sidetone level
 *  0.9.255 fixed CW RX noise
 *  0.9.255 fixed AGC TX/RX transition
 *  0.9.255 remove experimental CWL and CWU
 *  0.9.255 LCW and UCW become CWL and CWU
 *  0.9.225 CW Speed, sidetone frequency, and level
 *  1.0.225 save/restore CW settings to EEPROM
 *  1.0.225 general code cleanup
 *  1.1.225 add spectrum type (wind or grass)
 *  1.1.225 add IF shift
 *  1.1.225 CW transition to receive mute
 *  1.2.225 add AM mode
 *  1.2.225 add noise reduction
 *  1.3.225 show CW settings
 *  1.4.225 move filter code to filters.h
 *  2.0.225 add AMN and AMW (RX only) modes
 *  2.1.225 fix issue with noise on AMN
 *  2.2.225 move IRQ to SRAM fixes DSP issues
 *  2.3.225 add AML and AMU modes (TX in AM, RX in SSB)
 *  2.4.225 general coverage receive mode
 *  2.5.225 improve AM and CW filtering
 *  2.6.225 fix bug in CW overloading
 *  2.7.225 move extra gain to AGC
 *  3.0.225 move all DSP to float
 *  3.1.225 improved smeter
 *  3.2.225 mic gain
 */

#include <SPI.h>
#include <EEPROM.h>
#include <TFT_eSPI.h>
#include "util.h"
#include "si5351mcu.h"
#include "mcp3021.h"
#include "Rotary.h"
#include "spectrum.h"
#include "dsp.h"
#include "menu.h"
#include "cw.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/vreg.h"

//#define YOUR_CALL "VK7IAN"

#define VERSION_STRING "  V3.2."
#define CRYSTAL_CENTRE 39999500UL
#define IF_CENTRE 7812UL
#define CW_TIMEOUT 800u
#define MENU_TIMEOUT 5000u
#define BAND_80M 0
#define BAND_40M 1
#define BAND_30M 2
#define BAND_20M 3
#define BAND_17M 4
#define BAND_15M 5
#define BAND_12M 6
#define BAND_10M 7
#define BAND_SWL 8
#define BAND_MIN BAND_80M
#define BAND_MAX BAND_SWL
#define DEFAULT_FREQUENCY 14200000ul
#define DEFAULT_BAND BAND_20M
#define DEFAULT_MODE MODE_USB
#define DEFAULT_STEP 1000ul
#define DEFAULT_CW_SPEED 60ul
#define DEFAULT_SIDETONE 700ul
#define DEFAULT_CW_LEVEL 2ul
#define DEFAULT_MICGAIN 100ul
#define BUTTON_LONG_PRESS_TIME 800ul
#define TCXO_FREQ 26000000ul

#define PIN_PTT      0 // Mic PTT (active low)
#define PIN_TX       1 // high = TX and bias enable, low = RX
#define PIN_PADB     2 // CW Paddle B
#define PIN_PADA     3 // CW Paddle A
#define PIN_SDA      4 // I2C
#define PIN_SCL      5 // I2C
#define PIN_ENCBUT   6 // rotary
#define PIN_ENCA     7 // rotary
#define PIN_ENCB     8 // rotary
#define PIN_RX       9 // Enable RX Relay
#define PIN_FILTER1 10 // 80m/60m
#define PIN_FILTER2 11 // 40m/30m
#define PIN_FILTER3 12 // 20m/17m
#define PIN_FILTER4 13 // 15m/12m/10m
#define PIN_TXP     14 // TX PWM
#define PIN_TXN     15 // TX PWM
#define PIN_MISO2   16 // LCD (not used)
#define PIN_CS      17 // LCD
#define PIN_SCK     18 // LCD
#define PIN_MOSI2   19 // LCD
#define PIN_DC      20 // LCD
#define PIN_RST     21 // LCD
#define PIN_APWM    22 // Audio PWM
#define PIN_REG     23 // Pico regulator
#define PIN_IF      26 // analog IF in
#define PIN_MUTE    27 // mute
#define PIN_MIC     28 // analog MIC

// width and height of LCD
#define LCD_WIDTH         240
#define LCD_HEIGHT        135
#define POS_SPLASH_X       80
#define POS_SPLASH_Y       50
#define POS_VERSION_X       0
#define POS_VERSION_Y     122
#define POS_FREQUENCY_X    60
#define POS_FREQUENCY_Y     0
#define POS_TX_X            0
#define POS_TX_Y            5
#define POS_RX_X           30
#define POS_RX_Y            5
#define POS_MODE_X         10
#define POS_MODE_Y         30
#define POS_BAND_X         57
#define POS_BAND_Y         30
#define POS_CPU_X         199
#define POS_CPU_Y          30
#define POS_JNR_X         199
#define POS_JNR_Y          52
#define POS_DEBUG_X        20
#define POS_DEBUG_Y        50
#define POS_ATT_X         190
#define POS_ATT_Y          30
#define POS_MULTI_X        55
#define POS_MULTI_Y        30
#define POS_MULTIVALUE_X   80
#define POS_MULTIVALUE_Y   65
#define POS_METER_X       100
#define POS_METER_Y        25
#define POS_TUNING_STEP_X 130
#define POS_TUNING_STEP_Y  40
#define POS_SWR_X         125
#define POS_SWR_Y          40
#define POS_WATER_X         0
#define POS_WATER_Y        62
#define POS_CW_SETTINGS_X   0
#define POS_CW_SETTINGS_Y  52
#define POS_CENTER_LEFT   119
#define POS_CENTER_RIGHT  120
#define POS_MENU_X         40
#define POS_MENU_Y         30
#define MENU_WIDTH        160
#define MENU_HEIGHT        82

#define SPECTRUM_WIND  0u
#define SPECTRUM_GRASS 1u
#define JNR_OFF 0u
#define JNR_LEVEL1 1u
#define JNR_LEVEL2 2u
#define JNR_LEVEL3 3u

#if PIN_MIC == 26U
#define MIC_MUX 0U
#elif PIN_MIC == 27U
#define MIC_MUX 1U
#elif PIN_MIC == 28U
#define MIC_MUX 2U
#elif PIN_MIC == 29U
#define MIC_MUX 3U
#endif

#if PIN_IF == 26U
#define IF_MUX 0U
#elif PIN_IF == 27U
#define IF_MUX 1U
#elif PIN_IF == 28U
#define IF_MUX 2U
#elif PIN_IF == 29U
#define IF_MUX 3U
#endif

// two buffers of 1024 gives 512 FFT bins
#define MAX_ADC_SAMPLES 2048
#define WATERFALL_ROWS 41

enum radio_mode_t
{
  MODE_LSB,
  MODE_USB,
  MODE_CWL,
  MODE_CWU,
  MODE_AMN,
  MODE_AMW,
  MODE_AML,
  MODE_AMU
};

auto_init_mutex(rotary_mutex);
volatile static uint32_t tx_pwm = 0;
volatile static uint32_t audio_pwm = 0;
volatile static bool setup_complete = false;

volatile static uint32_t wp = 0;
static uint8_t water[WATERFALL_ROWS][LCD_WIDTH] = {0};
static uint8_t magnitude[1024] = {0};

volatile static struct
{
  int32_t tune;
  int32_t ifshift;
  uint32_t step;
  uint32_t frequency;
  uint32_t band;
  uint32_t cw_dit;
  uint32_t cw_level;
  uint32_t sidetone;
  uint32_t cw_bfo;
  uint32_t cw_phase;
  uint32_t spectype;
  uint32_t jnrlevel;
  uint32_t mic;
  radio_mode_t mode;
  bool tx_enable;
  bool keydown;
  bool gaussian;
  bool menu_active;
  bool mode_auto;
}
radio =
{
  0l,
  0l,
  DEFAULT_STEP,
  DEFAULT_FREQUENCY,
  DEFAULT_BAND,
  DEFAULT_CW_SPEED,
  DEFAULT_CW_LEVEL,
  DEFAULT_SIDETONE,
  (uint32_t)(((uint64_t)(SAMPLERATE/4u - DEFAULT_SIDETONE) * (1ull << 32)) / SAMPLERATE),
  (uint32_t)(((uint64_t)DEFAULT_SIDETONE * (1ull << 32)) / SAMPLERATE),
  SPECTRUM_WIND,
  JNR_OFF,
  DEFAULT_MICGAIN,
  DEFAULT_MODE,
  false,
  false,
  true,
  false,
  true
};

static struct
{
  const uint32_t lo;
  const uint32_t hi;
  uint32_t frequency;
}
bands[] =
{
  { 3500000UL,  3800000UL,  3600000UL},
  { 7000000UL,  7300000UL,  7100000UL},
  {10100000UL, 10150000UL, 10120000UL},
  {14000000UL, 14350000UL, 14200000UL},
  {18068000UL, 18168000UL, 18100000UL},
  {21000000UL, 21450000UL, 21200000UL},
  {24890000UL, 24990000UL, 24900000UL},
  {28000000UL, 29700000UL, 28500000UL},
  {  500000UL, 30000000UL,  5000000UL}
};

volatile static struct
{
  uint32_t frequency;
}
save_data[] =
{
  { 3600000UL},
  { 7100000UL},
  {10120000UL},
  {14200000UL},
  {18100000UL},
  {21200000UL},
  {24900000UL},
  {28500000UL},
  { 5000000UL}
};

volatile static struct
{
  uint32_t usage;
  uint32_t count;
} cpu = {0,0};

Si5351mcu SI5351;
MCP3021 fwdADC;
MCP3021 refADC;
Rotary r = Rotary(PIN_ENCA,PIN_ENCB);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite lcd = TFT_eSprite(&tft);

static void set_filter(void)
{
  static pin_size_t old_filter = 0;
  pin_size_t new_filter = PIN_FILTER4;
  if (radio.frequency<6000000UL)
  {
    new_filter = PIN_FILTER1;
  }
  else if (radio.frequency<11000000UL)
  {
    new_filter = PIN_FILTER2;
  }
  else if (radio.frequency<20000000UL)
  {
    new_filter = PIN_FILTER3;
  }
  if (old_filter != new_filter)
  {
    old_filter = new_filter;
    digitalWrite(PIN_FILTER1,LOW);
    digitalWrite(PIN_FILTER2,LOW);
    digitalWrite(PIN_FILTER3,LOW);
    digitalWrite(PIN_FILTER4,LOW);
    digitalWrite(new_filter,HIGH);
  }
}

static void display_clear(void)
{
  lcd.fillSprite(LCD_BLACK);
}

static void display_refresh(void)
{
  lcd.pushSprite(0,0);
}

static void save_settings(void)
{
  static const uint32_t key = 0x12345678ul;
  EEPROM.begin(256);
  EEPROM.put(0*sizeof(uint32_t),key);
  EEPROM.put(1*sizeof(uint32_t),(uint32_t)radio.cw_dit);
  EEPROM.put(2*sizeof(uint32_t),(uint32_t)radio.cw_level);
  EEPROM.put(3*sizeof(uint32_t),(uint32_t)radio.sidetone);
  EEPROM.put(4*sizeof(uint32_t),(uint32_t)radio.cw_bfo);
  EEPROM.put(5*sizeof(uint32_t),(uint32_t)radio.cw_phase);
  EEPROM.put(6*sizeof(uint32_t),(uint32_t)radio.ifshift);
  EEPROM.put(7*sizeof(uint32_t),(uint32_t)radio.spectype);
  EEPROM.put(8*sizeof(uint32_t),(uint32_t)radio.jnrlevel);
  EEPROM.put(9*sizeof(uint32_t),(uint32_t)radio.mic);
  EEPROM.end();
}

static void restore_settings(void)
{
  uint32_t key = 0 ;
  EEPROM.begin(256);
  EEPROM.get(0,key);
  if (key==0x12345678)
  {
    uint32_t data32 = 0;
    EEPROM.get(1*sizeof(uint32_t),data32); radio.cw_dit   = data32;
    EEPROM.get(2*sizeof(uint32_t),data32); radio.cw_level = data32;
    EEPROM.get(3*sizeof(uint32_t),data32); radio.sidetone = data32;
    EEPROM.get(4*sizeof(uint32_t),data32); radio.cw_bfo   = data32;
    EEPROM.get(5*sizeof(uint32_t),data32); radio.cw_phase = data32;
    EEPROM.get(6*sizeof(uint32_t),data32); radio.ifshift = (int32_t)data32;
    EEPROM.get(7*sizeof(uint32_t),data32); radio.spectype = data32;
    EEPROM.get(8*sizeof(uint32_t),data32); radio.jnrlevel = data32;
    EEPROM.get(9*sizeof(uint32_t),data32); radio.mic = data32;
  }
  if (radio.mic<50ul || radio.mic>175ul)
  {
    radio.mic = DEFAULT_MICGAIN;
  }
  EEPROM.end();
}

void setup(void)
{
  // run DSP on core 0
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  const uint32_t clksys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
  pinMode(PIN_REG,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(PIN_FILTER1,OUTPUT);
  pinMode(PIN_FILTER2,OUTPUT);
  pinMode(PIN_FILTER3,OUTPUT);
  pinMode(PIN_FILTER4,OUTPUT);
  pinMode(PIN_RX,OUTPUT);
  pinMode(PIN_TX,OUTPUT);
  pinMode(PIN_MUTE,OUTPUT);
  pinMode(PIN_TXN,OUTPUT);
  pinMode(PIN_TXP,OUTPUT);
  pinMode(PIN_CS,OUTPUT);
  pinMode(PIN_SCK,OUTPUT);
  pinMode(PIN_MOSI2,OUTPUT);
  pinMode(PIN_DC,OUTPUT);
  pinMode(PIN_RST,OUTPUT);
  pinMode(PIN_APWM,OUTPUT);
  pinMode(PIN_PTT,INPUT);
  pinMode(PIN_PADB,INPUT);
  pinMode(PIN_PADA,INPUT);
  pinMode(PIN_MISO2,INPUT);
  pinMode(PIN_ENCBUT,INPUT_PULLUP);

  // pin defaults
  // set pico regulator to low noise
  digitalWrite(PIN_REG,HIGH);
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(PIN_MUTE,LOW);
  digitalWrite(PIN_FILTER1,LOW);
  digitalWrite(PIN_FILTER2,LOW);
  digitalWrite(PIN_FILTER3,LOW);
  digitalWrite(PIN_FILTER4,LOW);
  digitalWrite(PIN_RX,HIGH);  // enable RX relay
  digitalWrite(PIN_TX,LOW);   // enable RX
  digitalWrite(PIN_TXN,LOW);  // TX PWM
  digitalWrite(PIN_TXP,LOW);  // TX PWM
  digitalWrite(PIN_APWM,LOW); // Audio PWM
  digitalWrite(PIN_FILTER1,LOW);
  digitalWrite(PIN_FILTER2,LOW);
  digitalWrite(PIN_FILTER3,LOW);
  digitalWrite(PIN_FILTER4,LOW);
  delay(40);

  // set pin function to PWM
  gpio_set_function(PIN_TXP,GPIO_FUNC_PWM);
  gpio_set_function(PIN_TXN,GPIO_FUNC_PWM);
  gpio_set_function(PIN_APWM,GPIO_FUNC_PWM);

  // get PWM slice connected to each pin (pair)
  tx_pwm = pwm_gpio_to_slice_num(PIN_TXP);
  audio_pwm = pwm_gpio_to_slice_num(PIN_APWM);

  // set period of PWM
  pwm_set_wrap(tx_pwm,1023); // 225,000,000 / 1024 = 217,726
  pwm_set_wrap(audio_pwm,4095); // 225,000,000 / 4096 = 54,931

  // initialise to zero (low)
  pwm_set_both_levels(tx_pwm,0UL,0UL);
  pwm_set_chan_level(audio_pwm,PWM_CHAN_A,2048U);

  // set PWM running
  pwm_set_enabled(tx_pwm,true);
  pwm_set_enabled(audio_pwm,true);

  // init rotary
  r.begin();

  // init PLL and set default frequency
  radio.frequency = DEFAULT_FREQUENCY;
  radio.band = DEFAULT_BAND;
  radio.mode = DEFAULT_MODE;
  restore_settings();
  set_filter();

#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<2;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif

  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.setClock(400000ul);
  const bool SI5351_found = SI5351.init(TCXO_FREQ);
  if (!SI5351_found)
  {
    for (;;)
    {
      digitalWrite(LED_BUILTIN,HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN,LOW);
      delay(500);
    }
  }
  SI5351.setPower(0,SIOUT_8mA);
  SI5351.setPower(1,SIOUT_8mA);
  const uint32_t fre = radio.ifshift+radio.frequency+CRYSTAL_CENTRE;
  const uint32_t bfo = radio.ifshift+CRYSTAL_CENTRE+IF_CENTRE;
  SI5351.setFreq(1,fre);
  SI5351.setFreq(0,bfo);
  SI5351.reset();

  fwdADC.begin(0);
  refADC.begin(1);

#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<2;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif

  init_adc();

  // disable Mic in RX mode
  pinMode(PIN_MIC,OUTPUT);
  digitalWrite(PIN_MIC,LOW);

  // init LCD
  char sz_version[16] = "";
  char sz_clksys[16] = "";
  memset(sz_clksys,0,sizeof(sz_clksys));
  memset(sz_version,0,sizeof(sz_version));
  ultoa(clksys,sz_clksys,10);
  sz_clksys[3] = '\0';
  strcpy(sz_version,VERSION_STRING);
  strcat(sz_version,sz_clksys);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(LCD_BLACK);
  lcd.createSprite(LCD_WIDTH, LCD_HEIGHT);
  lcd.fillSprite(LCD_BLACK);
  lcd.pushSprite(0,0);
  for (uint32_t i=0;i<32;i++)
  {
    lcd.fillSprite(LCD_BLACK);
    lcd.setTextSize(3);
    lcd.setTextColor(spectrum::color_map_32[i],LCD_BLACK);
    lcd.setCursor(POS_SPLASH_X,POS_SPLASH_Y);
    lcd.print("uSBITX");
    lcd.setTextSize(1);
    lcd.setTextColor(LCD_WHITE,LCD_BLACK);
    lcd.setCursor(POS_VERSION_X,POS_VERSION_Y);
    lcd.print(sz_version);
    lcd.pushSprite(0,0);
    delay(50);
  }
  lcd.fillSprite(LCD_BLACK);
  lcd.pushSprite(0,0);

  // intro screen
  lcd.fillSprite(LCD_BLACK);
  lcd.setTextColor(LCD_WHITE,LCD_BLACK);
  lcd.setTextSize(2);
  lcd.setCursor(210,120);
  lcd.print(sz_version);
  lcd.setTextSize(3);
  lcd.setCursor(80,40);
#ifdef YOUR_CALL
  lcd.print(YOUR_CALL);
#else
  lcd.print("VK7IAN");
#endif
  lcd.pushSprite(0,0);

  // splash delay
  delay(2000);

  // unmute
  digitalWrite(PIN_MUTE,HIGH);

  setup_complete = true;
}

void setup1(void)
{
  // run UI on core 1
  // only go to loop1 when setup() has completed
  while (!setup_complete)
  {
    tight_loop_contents();
  }
#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<5;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif
}

static void show_frequency(void)
{
  char sz_frequency[16] = "";
  memset(sz_frequency,0,sizeof(sz_frequency));
  ultoa(radio.frequency,sz_frequency,10);
  if (radio.frequency<1000000u)
  {
    // 6 digits
    //            012 345
    // 936000 ->  936.000
    // 012345    01234567
    sz_frequency[7] = sz_frequency[5];
    sz_frequency[6] = sz_frequency[4];
    sz_frequency[5] = sz_frequency[3];
    sz_frequency[4] = '.';
    sz_frequency[3] = sz_frequency[2];
    sz_frequency[2] = sz_frequency[1];
    sz_frequency[1] = sz_frequency[0];
    sz_frequency[0] = ' ';
  }
  else if (radio.frequency<10000000u)
  {
    // 7 digits
    // 3555000 -> 3.555.000
    // 0123456    012345678
    sz_frequency[9] = sz_frequency[6];
    sz_frequency[8] = sz_frequency[5];
    sz_frequency[7] = sz_frequency[4];
    sz_frequency[6] = '.';
    sz_frequency[5] = sz_frequency[3];
    sz_frequency[4] = sz_frequency[2];
    sz_frequency[3] = sz_frequency[1];
    sz_frequency[2] = '.';
    sz_frequency[1] = sz_frequency[0];
    sz_frequency[0] = ' ';
  }
  else
  {
    // 8 digits
    // 14222000 -> 14.222.000
    // 01234567    0123456789
    sz_frequency[9] = sz_frequency[7];
    sz_frequency[8] = sz_frequency[6];
    sz_frequency[7] = sz_frequency[5];
    sz_frequency[6] = '.';
    sz_frequency[5] = sz_frequency[4];
    sz_frequency[4] = sz_frequency[3];
    sz_frequency[3] = sz_frequency[2];
    sz_frequency[2] = '.';
  }
  lcd.setTextSize(3);
  lcd.setTextColor(LCD_WHITE,LCD_BLACK);
  lcd.setCursor(POS_FREQUENCY_X,POS_FREQUENCY_Y);
  lcd.print(sz_frequency);
}

static void show_tuning_step(void)
{
  if (radio.tx_enable)
  {
    return;
  }
  lcd.setTextSize(1);
  lcd.setCursor(POS_TUNING_STEP_X-30,POS_TUNING_STEP_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print("STEP");
  lcd.setCursor(POS_TUNING_STEP_X,POS_TUNING_STEP_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print(radio.step);
}

static void show_swr(void)
{
  static uint32_t max_vswr = 0; 
  static uint32_t max_po = 0; 
  if (!radio.tx_enable)
  {
    max_vswr = 0;
    max_po = 0;
    return;
  }
  const float vfwd = (float)fwdADC.read();
  const float vref = (float)refADC.read();
  uint32_t vswr = 100u;
  if (vfwd>vref)
  {
    vswr = (uint32_t)(100.0f * (vfwd + vref) / (vfwd - vref));
    vswr = min(vswr,999u);
  }
  if (vswr>max_vswr)
  {
    max_vswr = vswr;
  }
  char sz_swr[16] = "";
  memset(sz_swr,0,sizeof(sz_swr));
  ultoa(max_vswr,sz_swr,10);
  sz_swr[3] = sz_swr[2];
  sz_swr[2] = sz_swr[1];
  sz_swr[1] = '.';
  lcd.setTextSize(1);
  lcd.setCursor(POS_SWR_X-25,POS_SWR_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print("SWR");
  lcd.setCursor(POS_SWR_X-5,POS_SWR_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print(sz_swr);

  // power out
  // compensate for diode drop
  static const float diode = 100.0f;
  const float vcomp = vfwd + diode;
  const uint32_t po = (uint32_t)(((vcomp * vcomp * 1e-5f) + 0.05f) * 10.0f);
  if (po>max_po)
  {
    max_po = po;
  }
  char sz_po[16] = "";
  memset(sz_po,0,sizeof(sz_po));
  ultoa(max_po,sz_po,10);
  if (max_po<10)
  {
    sz_po[2] = sz_po[0];
    sz_po[1] = '.';
    sz_po[0] = '0';
  }
  else if (max_po<100)
  {
    sz_po[2] = sz_po[1];
    sz_po[1] = '.';
  }
  else
  {
    sz_po[3] = sz_po[2];
    sz_po[2] = '.';
  }
  lcd.setCursor(POS_SWR_X+25,POS_SWR_Y);
  lcd.print("PO");
  lcd.setCursor(POS_SWR_X+40,POS_SWR_Y);
  lcd.print(sz_po);
}

static void show_tx(void)
{
  lcd.setTextSize(2);
  lcd.setCursor(POS_TX_X,POS_TX_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print("TX");
  lcd.setCursor(POS_RX_X,POS_RX_Y);
  lcd.setTextColor(LCD_BLUE);
  lcd.print("RX");
}

static void show_rx(void)
{
  lcd.setTextSize(2);
  lcd.setCursor(POS_TX_X,POS_TX_Y);
  lcd.setTextColor(LCD_BLUE);
  lcd.print("TX");
  lcd.setCursor(POS_RX_X,POS_RX_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print("RX");
}

static void show_swl(void)
{
  lcd.setTextSize(2);
  lcd.setCursor(POS_TX_X,POS_TX_Y);
  lcd.setTextColor(LCD_RED);
  lcd.print("TX");
  lcd.setCursor(POS_RX_X,POS_RX_Y);
  lcd.setTextColor(LCD_RED);
  lcd.print("RX");
}

static void show_rx_tx(void)
{
  if (radio.band==BAND_SWL)
  {
    show_swl();
  }
  else if (radio.tx_enable)
  {
    show_tx();
  }
  else
  {
    show_rx();
  }
}

static void show_mode(void)
{
  lcd.fillRect(POS_MODE_X-5,POS_MODE_Y-5,45,25,LCD_WHITE);
  lcd.setTextSize(2);
  lcd.setTextColor(LCD_BLACK);
  lcd.setCursor(POS_MODE_X,POS_MODE_Y);
  const char *sz_mode = "XXX";
  if (radio.tx_enable)
  {
    // TX in AM is always narrow
    switch (radio.mode)
    {
      case MODE_LSB: sz_mode = "LSB"; break;
      case MODE_USB: sz_mode = "USB"; break;
      case MODE_CWL: sz_mode = "CWL"; break;
      case MODE_CWU: sz_mode = "CWU"; break;
      case MODE_AMN: sz_mode = "AMN"; break;
      case MODE_AMW: sz_mode = "AMN"; break;
      case MODE_AML: sz_mode = "AMN"; break;
      case MODE_AMU: sz_mode = "AMN"; break;
    }
  }
  else
  {
    switch (radio.mode)
    {
      case MODE_LSB: sz_mode = "LSB"; break;
      case MODE_USB: sz_mode = "USB"; break;
      case MODE_CWL: sz_mode = "CWL"; break;
      case MODE_CWU: sz_mode = "CWU"; break;
      case MODE_AMN: sz_mode = "AMN"; break;
      case MODE_AMW: sz_mode = "AMW"; break;
      case MODE_AML: sz_mode = "AML"; break;
      case MODE_AMU: sz_mode = "AMU"; break;
    }
  }
  lcd.print(sz_mode);
}

static void show_band(void)
{
  const uint32_t background = (radio.band==BAND_SWL)?LCD_RED:LCD_PURPLE;
  lcd.fillRect(POS_BAND_X-5,POS_BAND_Y-5,45,25,background);
  lcd.setTextSize(2);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(POS_BAND_X,POS_BAND_Y);
  const char *sz_band = "";
  switch (radio.band)
  {
    case BAND_80M: sz_band = "80M"; break;
    case BAND_40M: sz_band = "40M"; break;
    case BAND_30M: sz_band = "30M"; break;
    case BAND_20M: sz_band = "20M"; break;
    case BAND_17M: sz_band = "17M"; break;
    case BAND_15M: sz_band = "15M"; break;
    case BAND_12M: sz_band = "12M"; break;
    case BAND_10M: sz_band = "10M"; break;
    case BAND_SWL: sz_band = "SWL"; break;
  }
  lcd.print(sz_band);
}

static void show_cpu_usage(void)
{
  static uint32_t cpu_usage = 0;
  static uint32_t next_update = 0;
  const uint32_t now = millis();
  if (now>next_update)
  {
    next_update = now + 1000ul;
    const uint32_t usage = cpu.usage;
    const uint32_t count = cpu.count;
    cpu.usage = 0;
    cpu.count = 0;
    cpu_usage = (100u * usage / count) >> 5;
  }
  lcd.fillRect(POS_CPU_X-5,POS_CPU_Y-5,45,25,LCD_RED);
  lcd.setTextSize(2);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(POS_CPU_X,POS_CPU_Y);
  lcd.print(cpu_usage);
  if (cpu_usage<100)
  {
    lcd.print("%");
  }
}

static void show_jnr(void)
{
  if (radio.jnrlevel==0)
  {
    return;
  }
  lcd.fillRect(POS_JNR_X-5,POS_JNR_Y-1,45,10,LCD_PURPLE);
  lcd.setTextSize(1);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(POS_JNR_X,POS_JNR_Y);
  switch (radio.jnrlevel)
  {
    case 1u: lcd.print("JNR:1"); break;
    case 2u: lcd.print("JNR:2"); break;
    case 3u: lcd.print("JNR:3"); break;
  }
}

static void show_debug_value(const int32_t v)
{
  if (v==0)
  {
    return;
  }
  lcd.setTextSize(2);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(POS_DEBUG_X,POS_DEBUG_Y);
  lcd.print(v);
}

static void show_meter_dial(const uint8_t sig)
{
  const uint8_t v = min(sig,15);
  lcd.setTextSize(1);
  lcd.setCursor(POS_METER_X,POS_METER_Y);
  lcd.setTextColor(LCD_WHITE);
  lcd.print("1 3 5 7 9 +20");
  for (uint8_t i=0;i<v;i++)
  {
    lcd.fillRect(POS_METER_X+i*5+0,POS_METER_Y+8,4,4,LCD_WHITE);
  }
}

static void show_cw_settings(void)
{
  if (radio.mode==MODE_CWL || radio.mode==MODE_CWU)
  {
    lcd.setTextSize(1);
    lcd.setTextColor(LCD_YELLOW);
    lcd.setCursor(POS_CW_SETTINGS_X,POS_CW_SETTINGS_Y);
    const char *sz_wpm = "";
    switch (radio.cw_dit)
    {
      case 120u: sz_wpm = "10"; break;
      case 80u:  sz_wpm = "15"; break;
      case 60u:  sz_wpm = "20"; break;
      case 48u:  sz_wpm = "25"; break;
      case 40u:  sz_wpm = "30"; break;
    }
    lcd.print("WPM:");
    lcd.print(sz_wpm);
    const char *sz_level = "";
    switch (radio.cw_level)
    {
      case 1u: sz_level = "LOW"; break;
      case 2u: sz_level = "MED"; break;
      case 3u: sz_level = "HI";  break;
    }
    lcd.print(" Level:");
    lcd.print(sz_level);
    lcd.print(" Sidetone:");
    lcd.print(radio.sidetone);
  }
}

static void show_spectrum(void)
{
  // show the frequency
  lcd.setTextSize(1);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(0,POS_WATER_Y+4);
  lcd.print("-8KHz");
  lcd.setCursor(LCD_WIDTH-34,POS_WATER_Y+4);
  lcd.print("+8KHz");

  if (radio.tx_enable &&
    (radio.mode==MODE_AMN || radio.mode==MODE_AMW ||
    radio.mode==MODE_AML || radio.mode==MODE_AMU))
  {
    for (uint32_t x=0;x<40;x++)
    {
      lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
      lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
    }
  }
  else
  {
    switch (radio.mode)
    {
      case MODE_LSB:
      case MODE_AML:
      {
        for (uint32_t x=0;x<40;x++)
        {
          lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
        }
        break;
      }
      case MODE_USB:
      case MODE_AMU:
      {
        for (uint32_t x=0;x<40;x++)
        {
          lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
        }
        break;
      }
      case MODE_CWL:
      case MODE_CWU:
      {
        for (uint32_t x=0;x<5;x++)
        {
          lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
          lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
        }
        break;
      }
      case MODE_AMN:
      {
        for (uint32_t x=0;x<40;x++)
        {
          lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
          lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
        }
        break;
      }
      case MODE_AMW:
      {
        for (uint32_t x=0;x<50;x++)
        {
          lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
          lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
        }
        break;
      }
    }
  }

  // max of two adjacent magnitudes
  for (uint32_t x=0;x<LCD_WIDTH;x++)
  {
    uint8_t droplet = magnitude[x*2+15];
    droplet = max(droplet,magnitude[x*2+16]);
    if (droplet>31) droplet = 31;
    water[wp][x] = droplet;
  }

  // draw the spectrum
  if (radio.spectype==SPECTRUM_WIND)
  {
    for (uint32_t x=0;x<LCD_WIDTH-1;x++)
    {
      const int32_t v0 = water[wp][x];
      const int32_t v1 = water[wp][x+1];
      const int32_t x0 = x;
      const int32_t y0 = POS_WATER_Y+31-v0;
      const int32_t x1 = x+1;
      const int32_t y1 = POS_WATER_Y+31-v1;
      lcd.drawLine(x0,y0,x1,y1,LCD_WHITE);
    }
  }
  else
  {
    // SPECTRUM_GRASS
    lcd.fillRectVGradient(0,POS_WATER_Y,240,32,LCD_RED,LCD_YELLOW);
    for (uint32_t x=0;x<LCD_WIDTH;x++)
    {
      /*
      // single colour grass
      const int32_t x0 = x;
      const int32_t y0 = POS_WATER_Y+31;
      const int32_t x1 = x;
      const int32_t y1 = POS_WATER_Y+31-water[wp][x];
      lcd.drawLine(x0,y0,x1,y1,LCD_WHITE);
      */
      const int32_t x0 = x;
      const int32_t y0 = POS_WATER_Y;
      const int32_t x1 = x;
      const int32_t y1 = POS_WATER_Y+30-water[wp][x];
      lcd.drawLine(x0,y0,x1,y1,LCD_BLACK);
    }
  }

  // draw the waterfall
  int32_t r = wp;
  int32_t y = POS_WATER_Y+32;
  for (uint32_t i=0;i<WATERFALL_ROWS;i++,y++)
  {
    for (uint32_t x=0;x<LCD_WIDTH;x++)
    {
      const uint16_t c = spectrum::color_map_32[water[r][x]];
      lcd.drawPixel(x,y,c);
    }
    r--;
    if (r<0) r = WATERFALL_ROWS-1;
  }
  wp++;
  if (wp>=WATERFALL_ROWS) wp = 0;
}

enum menu_button_state_t {MENU_BUTTON_IDLE,MENU_BUTTON_PRESSED,MENU_WAIT_RELEASE_0,MENU_WAIT_RELEASE_1};
enum menu_button_action_t {MENU_NONE,MENU_TOP_SELECT,MENU_OPTION_SELECT};
static menu_button_state_t menu_button_state = MENU_BUTTON_IDLE;
static menu_button_action_t menu_button_action = MENU_NONE;
static uint8_t menu_window = 0;
static uint8_t menu_current = 0;
static uint8_t option_window = 0;
static uint8_t option_current = 0;

static void show_menu(void)
{
  if (!radio.menu_active)
  {
    return;
  }
  lcd.fillRect(POS_MENU_X,POS_MENU_Y,MENU_WIDTH,MENU_HEIGHT,LCD_BLACK);
  lcd.drawRect(POS_MENU_X,POS_MENU_Y,MENU_WIDTH,MENU_HEIGHT,LCD_WHITE),
  lcd.setTextSize(2);
  if (menu_button_action==MENU_NONE) // MENU_MENU_SELECT
  {
    // display top level menu
    for (uint8_t i=menu_window,j=0;i<NUM_MENU_ITEMS && j<4;i++,j++)
    {
      char sz_menu_name[16] = "";
      memset(sz_menu_name,' ',sizeof(sz_menu_name));
      sz_menu_name[10] = '\0';
      for (int k=0;k<10;k++)
      {
        const char c = menu_options[i].menu_name[k];
        if (c=='\0') break;
        sz_menu_name[k] = c;
      }
      if (i==menu_current)
      {
        lcd.setTextColor(LCD_BLACK);
        lcd.fillRectHGradient(POS_MENU_X+2,POS_MENU_Y+20*j+1,MENU_WIDTH-4,20,LCD_YELLOW,LCD_PINK);
      }
      else
      {
        lcd.setTextColor(LCD_WHITE);
      }
      lcd.setCursor(POS_MENU_X+4,POS_MENU_Y+20*j+4);
      lcd.print(sz_menu_name);
    }
  }
  else if (menu_button_action==MENU_TOP_SELECT) // MENU_OPTION_SELECT
  {
    if (menu_current<NUM_MENU_ITEMS)
    {
      const uint8_t num_options = menu_options[menu_current].num_options;
      if (option_window<num_options && option_current<num_options)
      {
        lcd.setCursor(POS_MENU_X+4,POS_MENU_Y+2);
        lcd.print(menu_options[menu_current].menu_name);
        for (uint8_t i=option_window,j=1;i<num_options && j<4;i++,j++)
        {
          char sz_option_name[16] = "";
          memset(sz_option_name,' ',sizeof(sz_option_name));
          sz_option_name[10] = '\0';
          for (int k=1;k<10;k++)
          {
            const char c = menu_options[menu_current].options[i].option_name[k-1];
            if (c=='\0') break;
            sz_option_name[k] = c;
          }
          if (i==option_current)
          {
            lcd.setTextColor(LCD_BLACK);
            lcd.fillRectHGradient(POS_MENU_X+2,POS_MENU_Y+20*j,MENU_WIDTH-4,20,LCD_YELLOW,LCD_PINK);
          }
          else
          {
            lcd.setTextColor(LCD_WHITE);
          }
          lcd.setCursor(POS_MENU_X+4,POS_MENU_Y+20*j+2);
          lcd.print(sz_option_name);
        }
      }
    }
  }
}

static void update_display(const uint32_t signal_level = 0u,const int32_t debug_value = 0)
{
  display_clear();
  show_rx_tx();
  show_mode();
  show_band();
  show_cpu_usage();
  show_frequency();
  show_tuning_step();
  show_swr();
  show_meter_dial(signal_level);
  show_cw_settings();
  show_jnr();
  show_spectrum();
  show_menu();
  show_debug_value(debug_value);
  display_refresh();
}

static void init_menu(void)
{
  menu_window = 0;
  menu_current = 0;
  option_window = 0;
  option_current = 0;
  menu_button_state = MENU_WAIT_RELEASE_0;
  menu_button_action = MENU_NONE;
}

static const option_value_t process_menu(void)
{
  static uint32_t menu_timeout = millis()+MENU_TIMEOUT;
  option_value_t option = OPTION_NONE;
  switch (menu_button_state)
  {
    case MENU_WAIT_RELEASE_0:
    {
      if (digitalRead(PIN_ENCBUT)==HIGH)
      {
        menu_button_state = MENU_BUTTON_IDLE;
        delay(50);
      }
      menu_timeout = millis()+MENU_TIMEOUT;
      break;
    }
    case MENU_BUTTON_IDLE:
    {
      // has the button been pressed?
      if (digitalRead(PIN_ENCBUT)==LOW)
      {
        menu_button_state = MENU_WAIT_RELEASE_1;
        menu_timeout = millis()+MENU_TIMEOUT;
        delay(50);
      }
      break;
    }
    case MENU_WAIT_RELEASE_1:
    {
      if (digitalRead(PIN_ENCBUT)==HIGH)
      {
        menu_button_state = MENU_BUTTON_IDLE;
        switch (menu_button_action)
        {
          case MENU_NONE:          menu_button_action = MENU_TOP_SELECT;    break;
          case MENU_TOP_SELECT:    menu_button_action = MENU_OPTION_SELECT; break;
          case MENU_OPTION_SELECT: menu_button_action = MENU_NONE;          break;
        }
        delay(50);
      }
      menu_timeout = millis()+MENU_TIMEOUT;
      break;
    }
  }
  // process the button action
  switch (menu_button_action)
  {
    case MENU_NONE:
    {
      mutex_enter_blocking(&rotary_mutex);
      const int32_t rotary_delta = radio.tune;
      radio.tune = 0;
      mutex_exit(&rotary_mutex);
      if (rotary_delta>0)
      {
        menu_timeout = millis()+MENU_TIMEOUT;
        if (menu_current<NUM_MENU_ITEMS-1)
        {
          menu_current++;
          if (menu_current>menu_window+3)
          {
            if (menu_window<NUM_MENU_ITEMS-1)
            {
              menu_window++;
            }
          }
        }
      }
      else if (rotary_delta<0)
      {
        menu_timeout = millis()+MENU_TIMEOUT;
        if (menu_current>0)
        {
          menu_current--;
          if (menu_current<menu_window)
          {
            if (menu_window>0)
            {
              menu_window--;
            }          
          }
        }
      }
      break;
    }
    case MENU_TOP_SELECT:
    {
      if (menu_options[menu_current].menu_value==MENU_EXIT)
      {
        return OPTION_EXIT;
      }
      // process menu options
      const uint8_t num_options = menu_options[menu_current].num_options;
      mutex_enter_blocking(&rotary_mutex);
      const int32_t rotary_delta = radio.tune;
      radio.tune = 0;
      mutex_exit(&rotary_mutex);
      if (rotary_delta>0)
      {
        menu_timeout = millis()+MENU_TIMEOUT;
        if (option_current<num_options-1)
        {
          option_current++;
          if (option_current>option_window+2)
          {
            if (option_window<num_options-1)
            {
              option_window++;
            }
          }
        }
      }
      else if (rotary_delta<0)
      {
        menu_timeout = millis()+MENU_TIMEOUT;
        if (option_current>0)
        {
          option_current--;
          if (option_current<option_window)
          {
            if (option_window>0)
            {
              option_window--;
            }          
          }
        }
      }
      break;
    }
    case MENU_OPTION_SELECT:
    {
      option = menu_options[menu_current].options[option_current].option_value;
      radio.menu_active = false;
      break;
    }
  }
  if (millis()>menu_timeout)
  {
    radio.menu_active = false;
  }
  return option;
}

volatile static bool adc_value_ready = false;
volatile static int16_t adc_value = 0;
volatile static int32_t dac_tx_p = 0;
volatile static int32_t dac_tx_n = 0;
volatile static int32_t dac_audio = 0;
volatile static uint32_t adc_sample_p = 0;
volatile static uint32_t mic_peak_level = 0;
volatile static float mic_gain = 0.0f;
volatile static int16_t adc_data[MAX_ADC_SAMPLES] = {0};

void __not_in_flash_func(adc_interrupt_handler)(void)
{
  volatile static uint32_t counter = 0;
  volatile static uint32_t adc_raw = 0;
  if (adc_fifo_get_level()<4u)
  {
    return;
  }
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  if (counter==4)
  {
    pwm_set_both_levels(tx_pwm,dac_tx_p,dac_tx_n);
    pwm_set_chan_level(audio_pwm,PWM_CHAN_A,dac_audio);
    // 16 times oversampling, 14 bits equiv
    adc_value = (int16_t)(adc_raw>>2)-8192;
    adc_value_ready = true;
    adc_raw = 0;
    counter = 0;
  }
  counter++;
}

void init_adc(void)
{
  adc_init();
  adc_gpio_init(PIN_MIC);
  adc_gpio_init(PIN_IF);
  adc_select_input(IF_MUX);
  adc_fifo_setup(true, false, 4, false, false);
  adc_fifo_drain();
  adc_irq_set_enabled(true);
  irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_interrupt_handler);
  irq_set_priority(ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
  irq_set_enabled(ADC_IRQ_FIFO, true);
  adc_run(true);
}

void __not_in_flash_func(loop)(void)
{
  // run DSP on core 0
  static bool tx = false;
  if (tx)
  {
    // TX, check if changed to RX
    if (radio.tx_enable)
    {
      if (adc_value_ready)
      {
        volatile const uint32_t cpu_start = time_us_32();
        adc_value_ready = false;
        int16_t tx_value = 0;
        if (radio.mode==MODE_CWL || radio.mode==MODE_CWU)
        {
          tx_value = CW::process_cw(radio.keydown,radio.gaussian);
          dac_audio = CW::get_sidetone(radio.keydown,radio.cw_phase,radio.cw_level)+2048;
        }
        else if (radio.mode==MODE_LSB)
        {
          tx_value = DSP::process_ssb_tx(adc_value,true,mic_gain);
          mic_peak_level = DSP::get_mic_peak_level(adc_value);
        }
        else if (radio.mode==MODE_USB)
        {
          tx_value = DSP::process_ssb_tx(adc_value,false,mic_gain);
          mic_peak_level = DSP::get_mic_peak_level(adc_value);
        }
        else
        {
          tx_value = DSP::process_am_tx(adc_value,mic_gain);
          mic_peak_level = DSP::get_mic_peak_level(adc_value);
        }
        tx_value = constrain(tx_value,-512,+511);
        dac_tx_p = 512UL + tx_value;
        dac_tx_n = 512UL - tx_value;
        adc_data[adc_sample_p++] = tx_value;
        adc_sample_p &= (MAX_ADC_SAMPLES-1);
        volatile const uint32_t cpu_end = time_us_32();
        cpu.usage += (cpu_end-cpu_start);
        cpu.count++;
      }
    }
    else
    {
      // switched to RX
      pinMode(PIN_MIC,OUTPUT);
      digitalWrite(PIN_MIC,LOW);
      adc_select_input(IF_MUX);
      dac_tx_p = 0L;
      dac_tx_n = 0;
      tx = false;
    }
  }
  else
  {
    // RX, check if changed to TX
    if (radio.tx_enable)
    {
      // switch to TX
      adc_gpio_init(PIN_MIC);
      adc_select_input(MIC_MUX);
      mic_gain = (float)radio.mic / 100.0f;
      tx = true;
    }
    else
    {
      if (adc_value_ready)
      {
        volatile const uint32_t cpu_start = time_us_32();
        adc_value_ready = false;
        adc_data[adc_sample_p++] = adc_value;
        adc_sample_p &= (MAX_ADC_SAMPLES-1);
        int16_t rx_value = 0;
        switch (radio.mode)
        {
          case MODE_LSB: rx_value = DSP::process_ssb_rx(adc_value,true);        break;
          case MODE_USB: rx_value = DSP::process_ssb_rx(adc_value,false);       break;
          case MODE_CWL: rx_value = DSP::process_cw_rx(adc_value,radio.cw_bfo); break;
          case MODE_CWU: rx_value = DSP::process_cw_rx(adc_value,radio.cw_bfo); break;
          case MODE_AMN: rx_value = DSP::process_amn_rx(adc_value);             break;
          case MODE_AMW: rx_value = DSP::process_amw_rx(adc_value);             break;
          case MODE_AML: rx_value = DSP::process_ssb_rx(adc_value,true);        break;
          case MODE_AMU: rx_value = DSP::process_ssb_rx(adc_value,false);       break;
        }
        rx_value = DSP::jnr(rx_value,radio.jnrlevel);
        dac_audio = constrain(rx_value,-2048,+2047)+2048;

        // only process rotary in receive mode
        static int32_t rotary = 0;
        switch (r.process())
        {
          case DIR_CW:  rotary++; break;
          case DIR_CCW: rotary--; break;
        }
        if (rotary!=0)
        {
          // don't hang around if we can't own the mutex
          if (mutex_try_enter(&rotary_mutex,0))
          {
            radio.tune += rotary;
            rotary = 0;
            mutex_exit(&rotary_mutex);
          }
        }
        volatile const uint32_t cpu_end = time_us_32();
        cpu.usage += (cpu_end-cpu_start);
        cpu.count++;
      }
    }
  }
}

static void process_spectrum(void)
{
  int16_t spectrum_data[1024] = {0};
  const uint32_t sample_p = adc_sample_p;
  if (sample_p<800)
  {
    // first half is in use, get the second half
    for (uint32_t i=0;i<1024;i++)
    {
      spectrum_data[i] = adc_data[i+1024];
    }
    spectrum::process(spectrum_data,magnitude);
  }
  else if (sample_p>1023 && sample_p<1800)
  {
    // second half is in use, get the first half
    for (uint32_t i=0;i<1024;i++)
    {
      spectrum_data[i] = adc_data[i];
    }
    spectrum::process(spectrum_data,magnitude);
  }
}

static void process_ssb_tx(void)
{
  // 1. mute the receiver
  // 2. set TX/RX relay to TX
  // 3. enable MIC (DSP)
  // 4. enable TX bias

  // indicate PTT pressed
  digitalWrite(LED_BUILTIN,HIGH);

  // mute the receiver
  analogWrite(PIN_MUTE,LOW);
  delay(10);

  // disable RX
  digitalWrite(PIN_RX,LOW);
  delay(10);

  // enable MIC processing
  radio.tx_enable = true;
  update_display();
  delay(10);

  // enable TX bias
  digitalWrite(PIN_TX,HIGH);
  delay(50);

  // wait for PTT release
  uint32_t tx_display_update = 0;
  while (digitalRead(PIN_PTT)==LOW)
  {
    // spectrum data is mic input
    process_spectrum();

    // update display
    const uint32_t now = millis();
    if (now>tx_display_update)
    {
      //update_display(mic_peak_level,debug_value);
      update_display(mic_peak_level);
      tx_display_update = now + 50ul;
    }
  }
}

static void cw_delay(const uint32_t ms,const uint32_t level)
{
  const uint32_t delay_time = millis()+ms;
  update_display(level);
  while (delay_time>millis())
  {
    tight_loop_contents();
  }
}

static void process_key(void)
{
  // disable RX
  digitalWrite(PIN_RX,LOW);

  // enable TX
  digitalWrite(PIN_TX,HIGH);
  delay(10);

  // enable TX processing
  radio.keydown = false;
  radio.tx_enable = true;
  delay(10);

  // stay here until timeout after key up (PTT released)
  uint32_t cw_timeout = millis() + CW_TIMEOUT;
  for (;;)
  {
    if (digitalRead(PIN_PTT)==LOW)
    {
      // indicate PTT pressed
      digitalWrite(LED_BUILTIN,HIGH);
      radio.keydown = true;
      update_display(15u);
      while (digitalRead(PIN_PTT)==LOW)
      {
        update_display(15u);
      }
      // indicate PTT released
      digitalWrite(LED_BUILTIN,LOW);
      radio.keydown = false;
      update_display(0u);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (digitalRead(PIN_PADA)==LOW)
    {
      // dit
      cw_delay(radio.cw_dit,0u);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      cw_delay(radio.cw_dit,15u);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (digitalRead(PIN_PADB)==LOW)
    {
      // dah
      cw_delay(radio.cw_dit,0u);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      cw_delay(radio.cw_dit * 3, 15u);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (digitalRead(PIN_PADA)==LOW && digitalRead(PIN_PADB)==LOW)
    {
      // dit
      cw_delay(radio.cw_dit,0u);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      cw_delay(radio.cw_dit,15u);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      // dah
      cw_delay(radio.cw_dit,0u);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      cw_delay(radio.cw_dit * 3,15u);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (millis()>cw_timeout)
    {
      break;
    }
  }

  // mute during transition back to receive
  digitalWrite(PIN_MUTE,LOW);
}

static const radio_mode_t get_mode_auto(void)
{
  if (!radio.mode_auto)
  {
    return radio.mode;
  }
  if (radio.frequency<10000000ul)
  {
    if (radio.frequency==7074000ul)
    {
      return MODE_USB;
    }
    if (radio.frequency==3573000ul)
    {
      return MODE_USB;
    }
    if (radio.frequency<7060000ul && radio.frequency>=7000000ul)
    {
      return MODE_CWL;
    }
    return MODE_LSB;
  }
  else if (radio.frequency<14060000ul && radio.frequency>=14000000ul)
  {
    return MODE_CWU;
  }
  return MODE_USB;
}

static void set_frequency(void)
{
  const uint32_t f = (radio.frequency+CRYSTAL_CENTRE+radio.ifshift);
  SI5351.setFreq(1,f);
}

void loop1(void)
{
  // run UI on core 1
  static uint32_t old_frequency = radio.frequency;
  static uint32_t old_band = radio.band;
  static uint32_t old_sidetone = radio.sidetone;
  static uint32_t old_cw_level = radio.cw_level;
  static uint32_t old_cw_dit = radio.cw_dit;
  static uint32_t old_spectype = radio.spectype;
  static uint32_t old_jnrlevel = radio.jnrlevel;
  static uint32_t old_micgain = radio.mic;
  static int32_t old_ifshift = radio.ifshift;
  static mode_t old_mode = radio.mode;

  // process button press
  // short press: change step
  // long press: menu options
  enum button_state_t {BUTTON_IDLE,BUTTON_TEST_SHORT,BUTTON_WAIT_RELEASE};
  enum button_action_t {BUTTON_NO_PRESS,BUTTON_SHORT_PRESS,BUTTON_LONG_PRESS};
  static button_state_t button_state = BUTTON_IDLE;
  static uint32_t button_timer = 0;
  button_action_t button_action = BUTTON_NO_PRESS;
  if (!radio.tx_enable)
  {
    // receive mode
    if (radio.menu_active)
    {
      const option_value_t option = process_menu();
      switch (option)
      {
        case OPTION_MODE_LSB:       radio.mode = MODE_LSB; radio.mode_auto = false; break;
        case OPTION_MODE_USB:       radio.mode = MODE_USB; radio.mode_auto = false; break;
        case OPTION_MODE_CWL:       radio.mode = MODE_CWL; radio.mode_auto = false; break;
        case OPTION_MODE_CWU:       radio.mode = MODE_CWU; radio.mode_auto = false; break;
        case OPTION_MODE_AMN:       radio.mode = MODE_AMN; radio.mode_auto = false; break;
        case OPTION_MODE_AMW:       radio.mode = MODE_AMW; radio.mode_auto = false; break;
        case OPTION_MODE_AML:       radio.mode = MODE_AML; radio.mode_auto = false; break;
        case OPTION_MODE_AMU:       radio.mode = MODE_AMU; radio.mode_auto = false; break;
        case OPTION_MODE_AUTO:      radio.mode_auto = true;                         break;
        case OPTION_STEP_10:        radio.step = 10U;                               break;
        case OPTION_STEP_100:       radio.step = 100U;                              break;
        case OPTION_STEP_500:       radio.step = 500U;                              break;
        case OPTION_STEP_1000:      radio.step = 1000U;                             break;
        case OPTION_STEP_5000:      radio.step = 5000U;                             break;
        case OPTION_STEP_10000:     radio.step = 10000U;                            break;
        case OPTION_STEP_100000:    radio.step = 100000U;                           break;
        case OPTION_BAND_80M:       radio.band = BAND_80M;                          break;
        case OPTION_BAND_40M:       radio.band = BAND_40M;                          break;
        case OPTION_BAND_30M:       radio.band = BAND_30M;                          break;
        case OPTION_BAND_20M:       radio.band = BAND_20M;                          break;
        case OPTION_BAND_17M:       radio.band = BAND_17M;                          break;
        case OPTION_BAND_15M:       radio.band = BAND_15M;                          break;
        case OPTION_BAND_12M:       radio.band = BAND_12M;                          break;
        case OPTION_BAND_10M:       radio.band = BAND_10M;                          break;
        case OPTION_BAND_SWL:       radio.band = BAND_SWL;                          break;
        case OPTION_SIDETONE_500:   radio.sidetone = 500u;                          break;
        case OPTION_SIDETONE_550:   radio.sidetone = 550u;                          break;
        case OPTION_SIDETONE_600:   radio.sidetone = 600u;                          break;
        case OPTION_SIDETONE_650:   radio.sidetone = 650u;                          break;
        case OPTION_SIDETONE_700:   radio.sidetone = 700u;                          break;
        case OPTION_SIDETONE_750:   radio.sidetone = 750u;                          break;
        case OPTION_SIDETONE_800:   radio.sidetone = 800u;                          break;
        case OPTION_SIDETONE_850:   radio.sidetone = 850u;                          break;
        case OPTION_SIDETONE_LOW:   radio.cw_level = 1u;                            break;
        case OPTION_SIDETONE_MED:   radio.cw_level = 2u;                            break;
        case OPTION_SIDETONE_HI:    radio.cw_level = 3u;                            break;
        case OPTION_CW_SPEED_10:    radio.cw_dit = 120u;                            break;
        case OPTION_CW_SPEED_15:    radio.cw_dit = 80u;                             break;
        case OPTION_CW_SPEED_20:    radio.cw_dit = 60u;                             break;
        case OPTION_CW_SPEED_25:    radio.cw_dit = 48u;                             break;
        case OPTION_CW_SPEED_30:    radio.cw_dit = 40u;                             break;
        case OPTION_IFSHIFT_200N:   radio.ifshift = -200;                           break;
        case OPTION_IFSHIFT_150N:   radio.ifshift = -150;                           break;
        case OPTION_IFSHIFT_100N:   radio.ifshift = -100;                           break;
        case OPTION_IFSHIFT_50N:    radio.ifshift = -50;                            break;
        case OPTION_IFSHIFT_0:      radio.ifshift = 0;                              break;
        case OPTION_IFSHIFT_50P:    radio.ifshift = +50;                            break;
        case OPTION_IFSHIFT_100P:   radio.ifshift = +100;                           break;
        case OPTION_IFSHIFT_150P:   radio.ifshift = +150;                           break;
        case OPTION_IFSHIFT_200P:   radio.ifshift = +200;                           break;
        case OPTION_SPECTRUM_WIND:  radio.spectype = SPECTRUM_WIND;                 break;
        case OPTION_SPECTRUM_GRASS: radio.spectype = SPECTRUM_GRASS;                break;
        case OPTION_JNR_LEVEL1:     radio.jnrlevel = JNR_LEVEL1;                    break;
        case OPTION_JNR_LEVEL2:     radio.jnrlevel = JNR_LEVEL2;                    break;
        case OPTION_JNR_LEVEL3:     radio.jnrlevel = JNR_LEVEL3;                    break;
        case OPTION_JNR_OFF:        radio.jnrlevel = JNR_OFF;                       break;
        case OPTION_MIC_50:         radio.mic = 50;                                 break;
        case OPTION_MIC_60:         radio.mic = 60;                                 break;
        case OPTION_MIC_70:         radio.mic = 70;                                 break;
        case OPTION_MIC_80:         radio.mic = 80;                                 break;
        case OPTION_MIC_90:         radio.mic = 90;                                 break;
        case OPTION_MIC_100:        radio.mic = 100;                                break;
        case OPTION_MIC_125:        radio.mic = 125;                                break;
        case OPTION_MIC_150:        radio.mic = 150;                                break;
        case OPTION_MIC_175:        radio.mic = 175;                                break;
        case OPTION_GAUSSIAN_ON:    radio.gaussian = true;                          break;
        case OPTION_GAUSSIAN_OFF:   radio.gaussian = false;                         break;
        case OPTION_EXIT:           radio.menu_active = false;                      break;
      }

      // when settings change save them
      bool settings_changed = false;

      // update DDS phase if sidetone changed
      if (radio.sidetone != old_sidetone)
      {
        old_sidetone = radio.sidetone;
        settings_changed = true;
        radio.cw_phase = ((uint64_t)radio.sidetone * (1ull << 32)) / SAMPLERATE;
        switch (radio.mode)
        {
          case MODE_CWL: radio.cw_bfo = ((uint64_t)(SAMPLERATE/4u - radio.sidetone) * (1ull << 32)) / SAMPLERATE; break;
          case MODE_CWU: radio.cw_bfo = ((uint64_t)(SAMPLERATE/4u + radio.sidetone) * (1ull << 32)) / SAMPLERATE; break;
        }
      }

      // CW timing
      if (radio.cw_dit != old_cw_dit)
      {
        old_cw_dit = radio.cw_dit;
        settings_changed = true;
      }

      // CW level
      if (radio.cw_level != old_cw_level)
      {
        old_cw_level = radio.cw_level;
        settings_changed = true;
      }

      // IF shift
      if (radio.ifshift != old_ifshift)
      {
        old_ifshift = radio.ifshift;
        settings_changed = true;
        const uint32_t bfo = radio.ifshift+CRYSTAL_CENTRE+IF_CENTRE;
        SI5351.setFreq(0,bfo);
        set_frequency();
      }

      // spectrum type
      if (radio.spectype != old_spectype)
      {
        old_spectype = radio.spectype;
        settings_changed = true;
      }

      // JNR level
      if (radio.jnrlevel != old_jnrlevel)
      {
        old_jnrlevel = radio.jnrlevel;
        settings_changed = true;
      }

      // mic gain
      if (radio.mic != old_micgain)
      {
        old_micgain = radio.mic;
        settings_changed = true;
      }

      // save the settings
      if (settings_changed)
      {
        save_settings();
      }

      // mode may change in auto
      const radio_mode_t auto_mode = get_mode_auto();
      if (radio.mode != auto_mode)
      {
        radio.mode = auto_mode;
      }

      // update frequency if mode changes
      if (radio.mode!=old_mode)
      {
        old_mode = radio.mode;
        set_frequency();
      }

      // set band
      if (radio.band!=old_band)
      {
        save_data[old_band].frequency = radio.frequency;
        radio.frequency = save_data[radio.band].frequency;
        old_frequency = radio.frequency;
        old_band = radio.band;
        // mute during change
        digitalWrite(PIN_MUTE,LOW);
        delay(50);
        set_filter();
        set_frequency();
        delay(50);
      }
    }
    else
    {
      // menu not active
      switch (button_state)
      {
        case BUTTON_IDLE:
        {
          if (digitalRead(PIN_ENCBUT)==LOW)
          {
            button_state = BUTTON_TEST_SHORT;
            button_timer = millis()+BUTTON_LONG_PRESS_TIME;
            delay(50);
          }
          break;
        }
        case BUTTON_TEST_SHORT:
        {
          const uint32_t now = millis();
          if (digitalRead(PIN_ENCBUT)==HIGH)
          {
            button_state = BUTTON_IDLE;
            if (now<button_timer)
            {
              button_action = BUTTON_SHORT_PRESS;
            }
            delay(50);
            break;
          }
          if (now>button_timer)
          {
            button_state = BUTTON_WAIT_RELEASE;
            button_action = BUTTON_LONG_PRESS;
          }
          break;
        }
        case BUTTON_WAIT_RELEASE:
        {
          if (digitalRead(PIN_ENCBUT)==HIGH)
          {
            button_state = BUTTON_IDLE;
            delay(50);
          }
          break;
        }
      }

      // process button action
      switch (button_action)
      {
        case BUTTON_SHORT_PRESS:
        {
          radio.step *= 10u;
          if (radio.step>1000u) radio.step = 10u;
          break;
        }
        case BUTTON_LONG_PRESS:
        {
          init_menu();
          radio.menu_active = true;
          break;
        }
      }

      // set the mode based on frequency if auto
      const radio_mode_t auto_mode = get_mode_auto();
      if (radio.mode != auto_mode)
      {
        radio.mode = auto_mode;
      }

      // process main tuning
      mutex_enter_blocking(&rotary_mutex);
      const int32_t tuning_delta = radio.tune;
      radio.tune = 0;
      mutex_exit(&rotary_mutex);
      uint32_t new_frequency = radio.frequency;
      new_frequency = new_frequency+(tuning_delta * (int32_t)radio.step);
      new_frequency = new_frequency/radio.step;
      new_frequency = new_frequency*radio.step;
      new_frequency = constrain(new_frequency,bands[radio.band].lo,bands[radio.band].hi);
      if (new_frequency!=old_frequency || radio.mode!=old_mode)
      {
        radio.frequency = new_frequency;
        old_frequency = new_frequency;
        old_mode = radio.mode;
        set_frequency();
        if (radio.band==BAND_SWL)
        {
          set_filter();
        }
      } // frequency change
    } // menu active
  } // receive mode
 
  // unmute in case muted
  digitalWrite(PIN_MUTE,HIGH);

  // process spectrum
  process_spectrum();

  // update the display every 50ms
  static uint32_t next_update = 0;
  const uint32_t now = millis();
  if (now>next_update)
  {
    next_update = now + 50ul;
    update_display(DSP::smeter());
  }

  // check for PTT
  if (radio.band != BAND_SWL)
  {
    const bool b_PTT = (digitalRead(PIN_PTT)==LOW);
    const bool b_PADA = (digitalRead(PIN_PADA)==LOW);
    const bool b_PADB = (digitalRead(PIN_PADB)==LOW);
    if (b_PTT || b_PADA || b_PADB)
    {
      const float saved_agc = DSP::agc_peak;
      radio.menu_active = false;
      if (radio.mode==MODE_CWL || radio.mode==MODE_CWU)
      {
        process_key();
      }
      else if (b_PTT)
      {
        process_ssb_tx();
      }
      // back to receive
      digitalWrite(PIN_TX,LOW);
      radio.tx_enable = false;
      delay(10);
      digitalWrite(PIN_RX,HIGH);
      delay(10);
      digitalWrite(LED_BUILTIN,LOW);
      update_display();
      digitalWrite(PIN_MUTE,HIGH);
      DSP::agc_peak = saved_agc;
    }
  }
}