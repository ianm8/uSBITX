/*
 * uSBITX Version 0.8.225
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
 *  CPU Speed: 225Mhz
 *  Optimize: -O2
 *  USB Stack: No USB
 *
 * Some history
 *  0.7.255 fixed bug in auto mode
 *  0.8.255 fixed bug in spectrum dynamic range
 *
 */

#include <SPI.h>
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

#define VERSION_STRING "  V0.8."
//#define CRYSTAL_CENTRE 40000000UL
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
#define BAND_MIN BAND_80M
#define BAND_MAX BAND_10M
#define DEFAULT_FREQUENCY 14200000ul
#define DEFAULT_BAND BAND_20M
#define DEFAULT_MODE MODE_USB
#define DEFAULT_STEP 1000ul
#define DEFAULT_CW_SPEED 60ul
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
#define POS_CENTER_LEFT   119
#define POS_CENTER_RIGHT  120
#define POS_MENU_X         40
#define POS_MENU_Y         30
#define MENU_WIDTH        160
#define MENU_HEIGHT        82

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
  MODE_LCW,
  MODE_UCW
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
  uint32_t step;
  uint32_t frequency;
  uint32_t band;
  uint32_t cw_dit;
  radio_mode_t mode;
  bool tx_enable;
  bool keydown;
  bool gaussian;
  bool higain;
  bool menu_active;
  bool mode_auto;
}
radio =
{
  0l,
  DEFAULT_STEP,
  DEFAULT_FREQUENCY,
  DEFAULT_BAND,
  DEFAULT_CW_SPEED,
  DEFAULT_MODE,
  false,
  false,
  true,
  false,
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
  {28000000UL, 29700000UL, 28500000UL}
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
  {28500000UL}
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

static void set_filter(void)
{
  digitalWrite(PIN_FILTER1,LOW);
  digitalWrite(PIN_FILTER2,LOW);
  digitalWrite(PIN_FILTER3,LOW);
  digitalWrite(PIN_FILTER4,LOW);
  if (radio.frequency<6000000UL)
  {
    digitalWrite(PIN_FILTER1,HIGH);
  }
  else if (radio.frequency<11000000UL)
  {
    digitalWrite(PIN_FILTER2,HIGH);
  }
  else if (radio.frequency<20000000UL)
  {
    digitalWrite(PIN_FILTER3,HIGH);
  }
  else
  {
    digitalWrite(PIN_FILTER4,HIGH);
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
  const uint32_t fre = radio.frequency+CRYSTAL_CENTRE;
  const uint32_t bfo = CRYSTAL_CENTRE+IF_CENTRE;
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

////
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
  if (radio.frequency<10000000u)
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
  uint32_t vswr = 100;
  if (vfwd>vref)
  {
    vswr = (uint32_t)(100.0f * (vfwd + vref) / (vfwd - vref));
    vswr = min(vswr,999);
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
  const uint32_t po = (uint32_t)(((vfwd * vfwd * 1e-5f) + 0.05f) * 10.0f);
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

static void show_rx_tx(void)
{
  if (radio.tx_enable)
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
  switch (radio.mode)
  {
    case MODE_LSB: sz_mode = "LSB"; break;
    case MODE_USB: sz_mode = "USB"; break;
    case MODE_CWL: sz_mode = "CWL"; break;
    case MODE_CWU: sz_mode = "CWU"; break;
    case MODE_LCW: sz_mode = "LCW"; break;
    case MODE_UCW: sz_mode = "UCW"; break;
  }
  lcd.print(sz_mode);
}

static void show_band(void)
{
  lcd.fillRect(POS_BAND_X-5,POS_BAND_Y-5,45,25,LCD_PURPLE);
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

static void show_spectrum(void)
{
  // show the frequency
  lcd.setTextSize(1);
  lcd.setTextColor(LCD_WHITE);
  lcd.setCursor(0,POS_WATER_Y+4);
  lcd.print("-8KHz");
  lcd.setCursor(LCD_WIDTH-34,POS_WATER_Y+4);
  lcd.print("+8KHz");

  // highlight received bandwidth
  switch (radio.mode)
  {
    case MODE_LSB:
    {
      for (uint32_t x=0;x<50;x++)
      {
        lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
      }
      break;
    }
    case MODE_USB:
    {
      for (uint32_t x=0;x<50;x++)
      {
        lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
      }
      break;
    }
    case MODE_CWL:
    {
      for (uint32_t x=0;x<20;x++)
      {
        lcd.drawLine(POS_CENTER_LEFT-10-x,POS_WATER_Y,POS_CENTER_LEFT-10-x,POS_WATER_Y+31,LCD_MODE);
      }
      break;
    }
    case MODE_CWU:
    {
      for (uint32_t x=0;x<20;x++)
      {
        lcd.drawLine(POS_CENTER_RIGHT+10+x,POS_WATER_Y,POS_CENTER_RIGHT+10+x,POS_WATER_Y+31,LCD_MODE);
      }
      break;
    }
    case MODE_LCW:
    case MODE_UCW:
    {
      for (uint32_t x=0;x<10;x++)
      {
        lcd.drawLine(POS_CENTER_LEFT-x,POS_WATER_Y,POS_CENTER_LEFT-x,POS_WATER_Y+31,LCD_MODE);
        lcd.drawLine(POS_CENTER_RIGHT+x,POS_WATER_Y,POS_CENTER_RIGHT+x,POS_WATER_Y+31,LCD_MODE);
      }
      break;
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
  if (menu_button_action==MENU_NONE) //// MENU_MENU_SELECT
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
  else if (menu_button_action==MENU_TOP_SELECT) //// MENU_OPTION_SELECT
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
volatile static int16_t adc_data[MAX_ADC_SAMPLES] = {0};

void adc_interrupt_handler(void)
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

void loop(void)
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
        if (radio.mode==MODE_CWL ||
          radio.mode==MODE_CWU ||
          radio.mode==MODE_LCW ||
          radio.mode==MODE_UCW)
        {
          tx_value = CW::process_cw(radio.keydown,radio.gaussian);
          dac_audio = CW::get_sidetone(radio.keydown);
        }
        else
        {
          tx_value = process_mic(adc_value,(radio.mode==MODE_LSB)?true:false);
          mic_peak_level = get_mic_peak_level(adc_value);
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
          case MODE_LSB: rx_value = process_ssb_rx(adc_value,true,radio.higain);  break;
          case MODE_USB: rx_value = process_ssb_rx(adc_value,false,radio.higain); break;
          case MODE_CWL: rx_value = process_cw_rx(adc_value,true,radio.higain);   break;
          case MODE_CWU: rx_value = process_cw_rx(adc_value,false,radio.higain);  break;
          case MODE_LCW: rx_value = process_lu_cw(adc_value,true,radio.higain);   break;
          case MODE_UCW: rx_value = process_lu_cw(adc_value,false,radio.higain);  break;
        }
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

static void process_key(void)
{
  // mute the receiver
////
  //analogWrite(PIN_MUTE,LOW);

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
        delay(20);
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
      delay(radio.cw_dit);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      delay(radio.cw_dit);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (digitalRead(PIN_PADB)==LOW)
    {
      // dah
      delay(radio.cw_dit);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      delay(radio.cw_dit * 3);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (digitalRead(PIN_PADA)==LOW && digitalRead(PIN_PADB)==LOW)
    {
      // dit
      delay(radio.cw_dit);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      delay(radio.cw_dit);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      // dah
      delay(radio.cw_dit);
      radio.keydown = true;
      digitalWrite(LED_BUILTIN,HIGH);
      delay(radio.cw_dit * 3);
      radio.keydown = false;
      digitalWrite(LED_BUILTIN,LOW);
      cw_timeout = millis() + CW_TIMEOUT;
    }
    if (millis()>cw_timeout)
    {
      break;
    }
  }
}

static radio_mode_t get_mode_auto(void)
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
      return MODE_LCW;
    }
    return MODE_LSB;
  }
  else if (radio.frequency<14060000ul && radio.frequency>=14000000ul)
  {
    return MODE_UCW;
  }
  return MODE_USB;
}

static void set_frequency(void)
{
  const uint32_t correct4cw = radio.mode==MODE_CWL?+CW_SIDETONE:radio.mode==MODE_CWU?-CW_SIDETONE:0u;
  const uint32_t f = (radio.frequency+CRYSTAL_CENTRE+correct4cw);
  SI5351.setFreq(1,f);
}

void loop1(void)
{
  // run UI on core 1
  static uint32_t old_frequency = radio.frequency;
  static uint32_t old_band = radio.band;
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
        case OPTION_MODE_LSB:     radio.mode = MODE_LSB; radio.mode_auto = false; break;
        case OPTION_MODE_USB:     radio.mode = MODE_USB; radio.mode_auto = false; break;
        case OPTION_MODE_CWL:     radio.mode = MODE_CWL; radio.mode_auto = false; break;
        case OPTION_MODE_CWU:     radio.mode = MODE_CWU; radio.mode_auto = false; break;
        case OPTION_MODE_LCW:     radio.mode = MODE_LCW; radio.mode_auto = false; break;
        case OPTION_MODE_UCW:     radio.mode = MODE_UCW; radio.mode_auto = false; break;
        case OPTION_MODE_AUTO:    radio.mode_auto = true;                         break;
        case OPTION_STEP_10:      radio.step = 10U;                               break;
        case OPTION_STEP_100:     radio.step = 100U;                              break;
        case OPTION_STEP_500:     radio.step = 500U;                              break;
        case OPTION_STEP_1000:    radio.step = 1000U;                             break;
        case OPTION_STEP_10000:   radio.step = 10000U;                            break;
        case OPTION_BAND_80M:     radio.band = BAND_80M;                          break;
        case OPTION_BAND_40M:     radio.band = BAND_40M;                          break;
        case OPTION_BAND_30M:     radio.band = BAND_30M;                          break;
        case OPTION_BAND_20M:     radio.band = BAND_20M;                          break;
        case OPTION_BAND_17M:     radio.band = BAND_17M;                          break;
        case OPTION_BAND_15M:     radio.band = BAND_15M;                          break;
        case OPTION_BAND_12M:     radio.band = BAND_12M;                          break;
        case OPTION_BAND_10M:     radio.band = BAND_10M;                          break;
        case OPTION_GAUSSIAN_ON:  radio.gaussian = true;                          break; 
        case OPTION_GAUSSIAN_OFF: radio.gaussian = false;                         break; 
        case OPTION_EXIT:         radio.menu_active = false;                      break; 
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
      radio.frequency = radio.frequency+(tuning_delta * (int32_t)radio.step);
      radio.frequency = radio.frequency/radio.step;
      radio.frequency = radio.frequency*radio.step;
      radio.frequency = constrain(radio.frequency,bands[radio.band].lo,bands[radio.band].hi);
      radio.higain = (radio.frequency>15000000ul);
      if (radio.frequency!=old_frequency || radio.mode!=old_mode)
      {
        old_frequency = radio.frequency;
        old_mode = radio.mode;
        set_frequency();
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
    update_display(smeter());
  }

  // check for PTT
  const bool b_PTT = (digitalRead(PIN_PTT)==LOW);
  const bool b_PADA = (digitalRead(PIN_PADA)==LOW);
  const bool b_PADB = (digitalRead(PIN_PADB)==LOW);
  if (b_PTT || b_PADA || b_PADB)
  {
    radio.menu_active = false;
    if (radio.mode==MODE_CWL ||
      radio.mode==MODE_CWU ||
      radio.mode==MODE_LCW ||
      radio.mode==MODE_UCW)
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
    delay(50);
    digitalWrite(PIN_RX,HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
    update_display();
    digitalWrite(PIN_MUTE,HIGH);
  }
}