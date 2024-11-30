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

  ...

  Exit
    Exit

*/

#define NUM_MENU_ITEMS 11U
#define NUM_MENU_OPTIONS 9U

enum menu_top_t
{
  MENU_BAND,
  MENU_STEP,
  MENU_MODE,
  MENU_CW_SPEED,
  MENU_SIDETONE,
  MENU_SIDETONE_LEVEL,
  MENU_IFSHIFT,
  MENU_SPECTRUM_TYPE,
  MENU_JNR,
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
  OPTION_MODE_AMN,
  OPTION_MODE_AMW,
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
  OPTION_CW_SPEED_10,
  OPTION_CW_SPEED_15,
  OPTION_CW_SPEED_20,
  OPTION_CW_SPEED_25,
  OPTION_CW_SPEED_30,
  OPTION_SIDETONE_500,
  OPTION_SIDETONE_550,
  OPTION_SIDETONE_600,
  OPTION_SIDETONE_650,
  OPTION_SIDETONE_700,
  OPTION_SIDETONE_750,
  OPTION_SIDETONE_800,
  OPTION_SIDETONE_850,
  OPTION_SIDETONE_LOW,
  OPTION_SIDETONE_MED,
  OPTION_SIDETONE_HI,
  OPTION_IFSHIFT_200N,
  OPTION_IFSHIFT_100N,
  OPTION_IFSHIFT_50N,
  OPTION_IFSHIFT_0,
  OPTION_IFSHIFT_50P,
  OPTION_IFSHIFT_100P,
  OPTION_IFSHIFT_150P,
  OPTION_IFSHIFT_200P,
  OPTION_SPECTRUM_WIND,
  OPTION_SPECTRUM_GRASS,
  OPTION_JNR_OFF,
  OPTION_JNR_LEVEL1,
  OPTION_JNR_LEVEL2,
  OPTION_JNR_LEVEL3,
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
      {OPTION_MODE_AMN,"AMN"},
      {OPTION_MODE_AMW,"AMW"},
      {OPTION_MODE_AUTO,"AUTO"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_MODE,
    "JNR",
    4U,
    {
      {OPTION_JNR_LEVEL1,"Level 1"},
      {OPTION_JNR_LEVEL2,"Level 2"},
      {OPTION_JNR_LEVEL3,"Level 3"},
      {OPTION_JNR_OFF,"Off"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_CW_SPEED,
    "CW Speed",
    6U,
    {
      {OPTION_CW_SPEED_10,"10 WPM"},
      {OPTION_CW_SPEED_15,"15 WPM"},
      {OPTION_CW_SPEED_20,"20 WPM"},
      {OPTION_CW_SPEED_25,"25 WPM"},
      {OPTION_CW_SPEED_30,"30 WPM"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_SIDETONE,
    "CW Tone",
    9U,
    {
      {OPTION_SIDETONE_500,"500 Hz"},
      {OPTION_SIDETONE_550,"550 Hz"},
      {OPTION_SIDETONE_600,"600 Hz"},
      {OPTION_SIDETONE_650,"650 Hz"},
      {OPTION_SIDETONE_700,"700 Hz"},
      {OPTION_SIDETONE_750,"750 Hz"},
      {OPTION_SIDETONE_800,"800 Hz"},
      {OPTION_SIDETONE_850,"850 Hz"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_SIDETONE_LEVEL,
    "CW Level",
    4U,
    {
      {OPTION_SIDETONE_LOW,"Low"},
      {OPTION_SIDETONE_MED,"Medium"},
      {OPTION_SIDETONE_HI,"High"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_IFSHIFT,
    "IF Shift",
    9U,
    {
      {OPTION_IFSHIFT_200N,"-200Hz"},
      {OPTION_IFSHIFT_100N,"-100Hz"},
      {OPTION_IFSHIFT_50N,"-50Hz"},
      {OPTION_IFSHIFT_0,"0Hz"},
      {OPTION_IFSHIFT_50P,"+50Hz"},
      {OPTION_IFSHIFT_100P,"+100Hz"},
      {OPTION_IFSHIFT_150P,"+150Hz"},
      {OPTION_IFSHIFT_200P,"+200Hz"},
      {OPTION_EXIT,"Exit"}
    }
  },
  {
    MENU_SPECTRUM_TYPE,
    "Spectrum",
    3U,
    {
      {OPTION_SPECTRUM_WIND,"Wind"},
      {OPTION_SPECTRUM_GRASS,"Grass"},
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