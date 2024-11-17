#ifndef MENU_H
#define MENU_H

/*

 Step
  10
  100
  500
  1000
  10000
  Exit

 Mode
   LSB
   USB
   CWL
   CWU
   Auto
   Exit

  Band
    80M
    40M
    ...
    Exit

  Exit
    Exit

*/

#define NUM_MENU_ITEMS 5U
#define NUM_MENU_OPTIONS 9U

enum menu_top_t
{
  MENU_BAND,
  MENU_STEP,
  MENU_MODE,
  MENU_GAUSSIAN,
  MENU_EXIT
};

enum option_value_t
{
  OPTION_STEP_10,
  OPTION_STEP_100,
  OPTION_STEP_500,
  OPTION_STEP_1000,
  OPTION_STEP_10000,
  OPTION_MODE_USB,
  OPTION_MODE_LSB,
  OPTION_MODE_CWL,
  OPTION_MODE_CWU,
  OPTION_MODE_LCW,
  OPTION_MODE_UCW,
  OPTION_MODE_AUTO,
  OPTION_BAND_80M,
  OPTION_BAND_40M,
  OPTION_BAND_30M,
  OPTION_BAND_20M,
  OPTION_BAND_17M,
  OPTION_BAND_15M,
  OPTION_BAND_12M,
  OPTION_BAND_10M,
  OPTION_GAUSSIAN_ON,
  OPTION_GAUSSIAN_OFF,
  OPTION_NONE,
  OPTION_EXIT
};

struct options_t
{
  option_value_t option_value;
  const char* option_name;
};

volatile static struct
{
  const menu_top_t menu_value;
  const char *menu_name;
  const uint8_t num_options;
  const options_t options[NUM_MENU_OPTIONS];
}
menu_options[NUM_MENU_ITEMS] =
{
  {
    MENU_BAND,
    "Band",
    9U,
    {
      {OPTION_BAND_80M,"80M"},
      {OPTION_BAND_40M,"40M"},
      {OPTION_BAND_30M,"30M"},
      {OPTION_BAND_20M,"20M"},
      {OPTION_BAND_17M,"17M"},
      {OPTION_BAND_15M,"15M"},
      {OPTION_BAND_12M,"12M"},
      {OPTION_BAND_10M,"10M"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_STEP,
    "Step",
    6U,
    {
      {OPTION_STEP_10,"10"},
      {OPTION_STEP_100,"100"},
      {OPTION_STEP_500,"500"},
      {OPTION_STEP_1000,"1000"},
      {OPTION_STEP_10000,"10000"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_MODE,
    "Mode",
    8U,
    {
      {OPTION_MODE_LSB,"LSB"},
      {OPTION_MODE_USB,"USB"},
      {OPTION_MODE_CWL,"CWL"},
      {OPTION_MODE_CWU,"CWU"},
      {OPTION_MODE_LCW,"LCW"},
      {OPTION_MODE_UCW,"UCW"},
      {OPTION_MODE_AUTO,"AUTO"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_GAUSSIAN,
    "Gaussian",
    3U,
    {
      {OPTION_GAUSSIAN_ON,"On"},
      {OPTION_GAUSSIAN_OFF,"Off"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_EXIT,
    "Exit",
    1U,
    {
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  }
};

#endif