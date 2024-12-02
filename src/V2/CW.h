#ifndef CW_H
#define CW_H

#include "util.h"

#define SIG_TAB 4

namespace CW
{
  // 511+512    = 1023  512 - 511  = 0
  // 0 + 512    = 512   512 - 0    = 512
  // -512 + 512 = 0     512 - -512 = 1023
  // 0 + 512    = 512   512 - 0    = 512
  static const int16_t __not_in_flash("fast_access_sram") fs4tab[SIG_TAB] =
  {
    511,
    0,
    -512,
    0
  };

  static const uint16_t __not_in_flash("fast_access_sram") gaussian_tab[312] =
  {
    32767,
    32765,
    32759,
    32748,
    32733,
    32714,
    32691,
    32664,
    32633,
    32597,
    32557,
    32513,
    32465,
    32413,
    32357,
    32297,
    32233,
    32165,
    32092,
    32016,
    31936,
    31852,
    31764,
    31673,
    31577,
    31478,
    31375,
    31269,
    31158,
    31045,
    30927,
    30806,
    30682,
    30554,
    30423,
    30289,
    30151,
    30010,
    29866,
    29718,
    29568,
    29415,
    29258,
    29099,
    28937,
    28772,
    28604,
    28434,
    28261,
    28086,
    27908,
    27727,
    27545,
    27360,
    27172,
    26983,
    26791,
    26598,
    26402,
    26204,
    26005,
    25804,
    25601,
    25396,
    25190,
    24982,
    24773,
    24562,
    24350,
    24137,
    23922,
    23707,
    23490,
    23272,
    23054,
    22834,
    22614,
    22393,
    22171,
    21949,
    21726,
    21503,
    21279,
    21054,
    20830,
    20605,
    20380,
    20155,
    19930,
    19705,
    19479,
    19254,
    19029,
    18805,
    18580,
    18356,
    18133,
    17909,
    17686,
    17464,
    17242,
    17021,
    16801,
    16581,
    16362,
    16144,
    15927,
    15711,
    15495,
    15281,
    15067,
    14855,
    14644,
    14434,
    14225,
    14018,
    13811,
    13606,
    13402,
    13200,
    12999,
    12799,
    12601,
    12405,
    12209,
    12016,
    11824,
    11633,
    11444,
    11257,
    11071,
    10887,
    10705,
    10524,
    10346,
    10168,
    9993,
    9819,
    9647,
    9477,
    9309,
    9143,
    8978,
    8815,
    8654,
    8495,
    8338,
    8183,
    8029,
    7877,
    7728,
    7580,
    7434,
    7290,
    7147,
    7007,
    6868,
    6732,
    6597,
    6464,
    6333,
    6204,
    6076,
    5951,
    5827,
    5706,
    5586,
    5467,
    5351,
    5237,
    5124,
    5013,
    4904,
    4796,
    4691,
    4587,
    4484,
    4384,
    4285,
    4188,
    4093,
    3999,
    3907,
    3816,
    3727,
    3640,
    3554,
    3470,
    3388,
    3307,
    3227,
    3149,
    3073,
    2998,
    2924,
    2852,
    2781,
    2712,
    2644,
    2578,
    2512,
    2448,
    2386,
    2325,
    2265,
    2206,
    2149,
    2092,
    2037,
    1984,
    1931,
    1879,
    1829,
    1780,
    1732,
    1685,
    1639,
    1594,
    1550,
    1507,
    1465,
    1424,
    1384,
    1345,
    1307,
    1270,
    1234,
    1198,
    1164,
    1130,
    1097,
    1065,
    1034,
    1004,
    974,
    945,
    917,
    890,
    863,
    837,
    812,
    787,
    763,
    739,
    717,
    695,
    673,
    652,
    632,
    612,
    592,
    574,
    556,
    538,
    521,
    504,
    488,
    472,
    456,
    442,
    427,
    413,
    399,
    386,
    373,
    361,
    349,
    337,
    326,
    315,
    304,
    293,
    283,
    274,
    264,
    255,
    246,
    238,
    229,
    221,
    213,
    206,
    199,
    192,
    185,
    178,
    172,
    165,
    159,
    154,
    148,
    143,
    137,
    132,
    127,
    123,
    118,
    114,
    109,
    105,
    101,
    98,
    94,
    90,
    87,
    83,
    80,
    77,
    74,
    71,
    69,
    66
  };

  static const int16_t __not_in_flash_func(process_cw)(const bool keydown,const bool gaussian)
  {
    volatile static uint32_t phase = 0;
    volatile static uint32_t gaussian_phase = 0;
    int16_t sig = 0;
    if (gaussian)
    {
      volatile static enum cw_state_t
      {
        CW_STATE_KEYUP,
        CW_STATE_KEYDOWN,
        CW_STATE_KEY_TRANSITION_TO_DOWN,
        CW_STATE_KEY_TRANSITION_TO_UP
      }
      cw_state = CW_STATE_KEYUP;
      switch (cw_state)
      {
        case CW_STATE_KEYUP:
        {
          // if keydown then transition to key down
          if (keydown)
          {
            gaussian_phase = 311;
            cw_state = CW_STATE_KEY_TRANSITION_TO_DOWN;
          }
          break;
        }
        case CW_STATE_KEY_TRANSITION_TO_DOWN:
        {
          // stay here until gaussian done
          const int32_t gaussian = gaussian_tab[gaussian_phase];
          const int32_t bfo = fs4tab[phase & 0x03];
          sig = (bfo * gaussian) >> 15;
          phase++;
          gaussian_phase--;
          if (gaussian_phase==0)
          {
            cw_state = CW_STATE_KEYDOWN;
          }
          break;
        }
        case CW_STATE_KEYDOWN:
        {
          // stay here while key down
          sig = fs4tab[phase & 0x03];
          phase++;
          if (keydown)
          {
            break;
          }
          gaussian_phase = 0;
          cw_state = CW_STATE_KEY_TRANSITION_TO_UP;
          break;
        }
        case CW_STATE_KEY_TRANSITION_TO_UP:
        {
          // stay here until gaussian done
          const int32_t gaussian = gaussian_tab[gaussian_phase];
          const int32_t bfo = fs4tab[phase & 0x03];
          sig = (bfo * gaussian) >> 15;
          phase++;
          gaussian_phase++;
          if (gaussian_phase>=312)
          {
            cw_state = CW_STATE_KEYUP;
          }
          break;
        }
      }
    }
    else
    {
      // gaussian off
      if (keydown)
      {
        sig = fs4tab[phase & 0x03];
        phase++;
      }
    }
    return sig;
  }

  static const int16_t __not_in_flash_func(get_sidetone)(const bool keydown,const uint32_t phase,const uint32_t level)
  {
    volatile static uint32_t dds = 0;
    int16_t s = 0;
    const uint32_t shift = 8 - level;
    if (keydown)
    {
      s = sin_tab[dds>>22]>>shift;
    }
    dds += phase;
    return s;
  }
}

#endif