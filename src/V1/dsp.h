#ifndef DSP_H
#define DSP_H

#define SAMPLERATE 31250ul
#define FIR_LENGTH 256
#define __mac_tap(_h) acc += (_h)*x[i++]

static const int16_t __not_in_flash("fast_access_sram") sin_tab[1024] =
{
  (int16_t)32767,
  (int16_t)32766,
  (int16_t)32765,
  (int16_t)32761,
  (int16_t)32757,
  (int16_t)32752,
  (int16_t)32745,
  (int16_t)32737,
  (int16_t)32728,
  (int16_t)32717,
  (int16_t)32705,
  (int16_t)32692,
  (int16_t)32678,
  (int16_t)32663,
  (int16_t)32646,
  (int16_t)32628,
  (int16_t)32609,
  (int16_t)32589,
  (int16_t)32567,
  (int16_t)32545,
  (int16_t)32521,
  (int16_t)32495,
  (int16_t)32469,
  (int16_t)32441,
  (int16_t)32412,
  (int16_t)32382,
  (int16_t)32351,
  (int16_t)32318,
  (int16_t)32285,
  (int16_t)32250,
  (int16_t)32213,
  (int16_t)32176,
  (int16_t)32137,
  (int16_t)32098,
  (int16_t)32057,
  (int16_t)32014,
  (int16_t)31971,
  (int16_t)31926,
  (int16_t)31880,
  (int16_t)31833,
  (int16_t)31785,
  (int16_t)31736,
  (int16_t)31685,
  (int16_t)31633,
  (int16_t)31580,
  (int16_t)31526,
  (int16_t)31470,
  (int16_t)31414,
  (int16_t)31356,
  (int16_t)31297,
  (int16_t)31237,
  (int16_t)31176,
  (int16_t)31113,
  (int16_t)31050,
  (int16_t)30985,
  (int16_t)30919,
  (int16_t)30852,
  (int16_t)30783,
  (int16_t)30714,
  (int16_t)30643,
  (int16_t)30571,
  (int16_t)30498,
  (int16_t)30424,
  (int16_t)30349,
  (int16_t)30273,
  (int16_t)30195,
  (int16_t)30117,
  (int16_t)30037,
  (int16_t)29956,
  (int16_t)29874,
  (int16_t)29791,
  (int16_t)29706,
  (int16_t)29621,
  (int16_t)29534,
  (int16_t)29447,
  (int16_t)29358,
  (int16_t)29268,
  (int16_t)29177,
  (int16_t)29085,
  (int16_t)28992,
  (int16_t)28898,
  (int16_t)28803,
  (int16_t)28706,
  (int16_t)28609,
  (int16_t)28510,
  (int16_t)28411,
  (int16_t)28310,
  (int16_t)28208,
  (int16_t)28105,
  (int16_t)28001,
  (int16_t)27896,
  (int16_t)27790,
  (int16_t)27683,
  (int16_t)27575,
  (int16_t)27466,
  (int16_t)27356,
  (int16_t)27245,
  (int16_t)27133,
  (int16_t)27019,
  (int16_t)26905,
  (int16_t)26790,
  (int16_t)26674,
  (int16_t)26556,
  (int16_t)26438,
  (int16_t)26319,
  (int16_t)26198,
  (int16_t)26077,
  (int16_t)25955,
  (int16_t)25832,
  (int16_t)25708,
  (int16_t)25582,
  (int16_t)25456,
  (int16_t)25329,
  (int16_t)25201,
  (int16_t)25072,
  (int16_t)24942,
  (int16_t)24811,
  (int16_t)24680,
  (int16_t)24547,
  (int16_t)24413,
  (int16_t)24279,
  (int16_t)24143,
  (int16_t)24007,
  (int16_t)23870,
  (int16_t)23731,
  (int16_t)23592,
  (int16_t)23452,
  (int16_t)23311,
  (int16_t)23170,
  (int16_t)23027,
  (int16_t)22884,
  (int16_t)22739,
  (int16_t)22594,
  (int16_t)22448,
  (int16_t)22301,
  (int16_t)22154,
  (int16_t)22005,
  (int16_t)21856,
  (int16_t)21705,
  (int16_t)21554,
  (int16_t)21403,
  (int16_t)21250,
  (int16_t)21096,
  (int16_t)20942,
  (int16_t)20787,
  (int16_t)20631,
  (int16_t)20475,
  (int16_t)20317,
  (int16_t)20159,
  (int16_t)20000,
  (int16_t)19841,
  (int16_t)19680,
  (int16_t)19519,
  (int16_t)19357,
  (int16_t)19195,
  (int16_t)19032,
  (int16_t)18868,
  (int16_t)18703,
  (int16_t)18537,
  (int16_t)18371,
  (int16_t)18204,
  (int16_t)18037,
  (int16_t)17869,
  (int16_t)17700,
  (int16_t)17530,
  (int16_t)17360,
  (int16_t)17189,
  (int16_t)17018,
  (int16_t)16846,
  (int16_t)16673,
  (int16_t)16499,
  (int16_t)16325,
  (int16_t)16151,
  (int16_t)15976,
  (int16_t)15800,
  (int16_t)15623,
  (int16_t)15446,
  (int16_t)15269,
  (int16_t)15090,
  (int16_t)14912,
  (int16_t)14732,
  (int16_t)14553,
  (int16_t)14372,
  (int16_t)14191,
  (int16_t)14010,
  (int16_t)13828,
  (int16_t)13645,
  (int16_t)13462,
  (int16_t)13279,
  (int16_t)13094,
  (int16_t)12910,
  (int16_t)12725,
  (int16_t)12539,
  (int16_t)12353,
  (int16_t)12167,
  (int16_t)11980,
  (int16_t)11793,
  (int16_t)11605,
  (int16_t)11417,
  (int16_t)11228,
  (int16_t)11039,
  (int16_t)10849,
  (int16_t)10659,
  (int16_t)10469,
  (int16_t)10278,
  (int16_t)10087,
  (int16_t)9896,
  (int16_t)9704,
  (int16_t)9512,
  (int16_t)9319,
  (int16_t)9126,
  (int16_t)8933,
  (int16_t)8739,
  (int16_t)8545,
  (int16_t)8351,
  (int16_t)8157,
  (int16_t)7962,
  (int16_t)7767,
  (int16_t)7571,
  (int16_t)7375,
  (int16_t)7179,
  (int16_t)6983,
  (int16_t)6786,
  (int16_t)6590,
  (int16_t)6393,
  (int16_t)6195,
  (int16_t)5998,
  (int16_t)5800,
  (int16_t)5602,
  (int16_t)5404,
  (int16_t)5205,
  (int16_t)5007,
  (int16_t)4808,
  (int16_t)4609,
  (int16_t)4410,
  (int16_t)4210,
  (int16_t)4011,
  (int16_t)3811,
  (int16_t)3612,
  (int16_t)3412,
  (int16_t)3212,
  (int16_t)3012,
  (int16_t)2811,
  (int16_t)2611,
  (int16_t)2410,
  (int16_t)2210,
  (int16_t)2009,
  (int16_t)1809,
  (int16_t)1608,
  (int16_t)1407,
  (int16_t)1206,
  (int16_t)1005,
  (int16_t)804,
  (int16_t)603,
  (int16_t)402,
  (int16_t)201,
  (int16_t)0,
  (int16_t)-201,
  (int16_t)-402,
  (int16_t)-603,
  (int16_t)-804,
  (int16_t)-1005,
  (int16_t)-1206,
  (int16_t)-1407,
  (int16_t)-1608,
  (int16_t)-1809,
  (int16_t)-2009,
  (int16_t)-2210,
  (int16_t)-2410,
  (int16_t)-2611,
  (int16_t)-2811,
  (int16_t)-3012,
  (int16_t)-3212,
  (int16_t)-3412,
  (int16_t)-3612,
  (int16_t)-3811,
  (int16_t)-4011,
  (int16_t)-4210,
  (int16_t)-4410,
  (int16_t)-4609,
  (int16_t)-4808,
  (int16_t)-5007,
  (int16_t)-5205,
  (int16_t)-5404,
  (int16_t)-5602,
  (int16_t)-5800,
  (int16_t)-5998,
  (int16_t)-6195,
  (int16_t)-6393,
  (int16_t)-6590,
  (int16_t)-6786,
  (int16_t)-6983,
  (int16_t)-7179,
  (int16_t)-7375,
  (int16_t)-7571,
  (int16_t)-7767,
  (int16_t)-7962,
  (int16_t)-8157,
  (int16_t)-8351,
  (int16_t)-8545,
  (int16_t)-8739,
  (int16_t)-8933,
  (int16_t)-9126,
  (int16_t)-9319,
  (int16_t)-9512,
  (int16_t)-9704,
  (int16_t)-9896,
  (int16_t)-10087,
  (int16_t)-10278,
  (int16_t)-10469,
  (int16_t)-10659,
  (int16_t)-10849,
  (int16_t)-11039,
  (int16_t)-11228,
  (int16_t)-11417,
  (int16_t)-11605,
  (int16_t)-11793,
  (int16_t)-11980,
  (int16_t)-12167,
  (int16_t)-12353,
  (int16_t)-12539,
  (int16_t)-12725,
  (int16_t)-12910,
  (int16_t)-13094,
  (int16_t)-13279,
  (int16_t)-13462,
  (int16_t)-13645,
  (int16_t)-13828,
  (int16_t)-14010,
  (int16_t)-14191,
  (int16_t)-14372,
  (int16_t)-14553,
  (int16_t)-14732,
  (int16_t)-14912,
  (int16_t)-15090,
  (int16_t)-15269,
  (int16_t)-15446,
  (int16_t)-15623,
  (int16_t)-15800,
  (int16_t)-15976,
  (int16_t)-16151,
  (int16_t)-16325,
  (int16_t)-16499,
  (int16_t)-16673,
  (int16_t)-16846,
  (int16_t)-17018,
  (int16_t)-17189,
  (int16_t)-17360,
  (int16_t)-17530,
  (int16_t)-17700,
  (int16_t)-17869,
  (int16_t)-18037,
  (int16_t)-18204,
  (int16_t)-18371,
  (int16_t)-18537,
  (int16_t)-18703,
  (int16_t)-18868,
  (int16_t)-19032,
  (int16_t)-19195,
  (int16_t)-19357,
  (int16_t)-19519,
  (int16_t)-19680,
  (int16_t)-19841,
  (int16_t)-20000,
  (int16_t)-20159,
  (int16_t)-20317,
  (int16_t)-20475,
  (int16_t)-20631,
  (int16_t)-20787,
  (int16_t)-20942,
  (int16_t)-21096,
  (int16_t)-21250,
  (int16_t)-21403,
  (int16_t)-21554,
  (int16_t)-21705,
  (int16_t)-21856,
  (int16_t)-22005,
  (int16_t)-22154,
  (int16_t)-22301,
  (int16_t)-22448,
  (int16_t)-22594,
  (int16_t)-22739,
  (int16_t)-22884,
  (int16_t)-23027,
  (int16_t)-23170,
  (int16_t)-23311,
  (int16_t)-23452,
  (int16_t)-23592,
  (int16_t)-23731,
  (int16_t)-23870,
  (int16_t)-24007,
  (int16_t)-24143,
  (int16_t)-24279,
  (int16_t)-24413,
  (int16_t)-24547,
  (int16_t)-24680,
  (int16_t)-24811,
  (int16_t)-24942,
  (int16_t)-25072,
  (int16_t)-25201,
  (int16_t)-25329,
  (int16_t)-25456,
  (int16_t)-25582,
  (int16_t)-25708,
  (int16_t)-25832,
  (int16_t)-25955,
  (int16_t)-26077,
  (int16_t)-26198,
  (int16_t)-26319,
  (int16_t)-26438,
  (int16_t)-26556,
  (int16_t)-26674,
  (int16_t)-26790,
  (int16_t)-26905,
  (int16_t)-27019,
  (int16_t)-27133,
  (int16_t)-27245,
  (int16_t)-27356,
  (int16_t)-27466,
  (int16_t)-27575,
  (int16_t)-27683,
  (int16_t)-27790,
  (int16_t)-27896,
  (int16_t)-28001,
  (int16_t)-28105,
  (int16_t)-28208,
  (int16_t)-28310,
  (int16_t)-28411,
  (int16_t)-28510,
  (int16_t)-28609,
  (int16_t)-28706,
  (int16_t)-28803,
  (int16_t)-28898,
  (int16_t)-28992,
  (int16_t)-29085,
  (int16_t)-29177,
  (int16_t)-29268,
  (int16_t)-29358,
  (int16_t)-29447,
  (int16_t)-29534,
  (int16_t)-29621,
  (int16_t)-29706,
  (int16_t)-29791,
  (int16_t)-29874,
  (int16_t)-29956,
  (int16_t)-30037,
  (int16_t)-30117,
  (int16_t)-30195,
  (int16_t)-30273,
  (int16_t)-30349,
  (int16_t)-30424,
  (int16_t)-30498,
  (int16_t)-30571,
  (int16_t)-30643,
  (int16_t)-30714,
  (int16_t)-30783,
  (int16_t)-30852,
  (int16_t)-30919,
  (int16_t)-30985,
  (int16_t)-31050,
  (int16_t)-31113,
  (int16_t)-31176,
  (int16_t)-31237,
  (int16_t)-31297,
  (int16_t)-31356,
  (int16_t)-31414,
  (int16_t)-31470,
  (int16_t)-31526,
  (int16_t)-31580,
  (int16_t)-31633,
  (int16_t)-31685,
  (int16_t)-31736,
  (int16_t)-31785,
  (int16_t)-31833,
  (int16_t)-31880,
  (int16_t)-31926,
  (int16_t)-31971,
  (int16_t)-32014,
  (int16_t)-32057,
  (int16_t)-32098,
  (int16_t)-32137,
  (int16_t)-32176,
  (int16_t)-32213,
  (int16_t)-32250,
  (int16_t)-32285,
  (int16_t)-32318,
  (int16_t)-32351,
  (int16_t)-32382,
  (int16_t)-32412,
  (int16_t)-32441,
  (int16_t)-32469,
  (int16_t)-32495,
  (int16_t)-32521,
  (int16_t)-32545,
  (int16_t)-32567,
  (int16_t)-32589,
  (int16_t)-32609,
  (int16_t)-32628,
  (int16_t)-32646,
  (int16_t)-32663,
  (int16_t)-32678,
  (int16_t)-32692,
  (int16_t)-32705,
  (int16_t)-32717,
  (int16_t)-32728,
  (int16_t)-32737,
  (int16_t)-32745,
  (int16_t)-32752,
  (int16_t)-32757,
  (int16_t)-32761,
  (int16_t)-32765,
  (int16_t)-32766,
  (int16_t)-32767,
  (int16_t)-32766,
  (int16_t)-32765,
  (int16_t)-32761,
  (int16_t)-32757,
  (int16_t)-32752,
  (int16_t)-32745,
  (int16_t)-32737,
  (int16_t)-32728,
  (int16_t)-32717,
  (int16_t)-32705,
  (int16_t)-32692,
  (int16_t)-32678,
  (int16_t)-32663,
  (int16_t)-32646,
  (int16_t)-32628,
  (int16_t)-32609,
  (int16_t)-32589,
  (int16_t)-32567,
  (int16_t)-32545,
  (int16_t)-32521,
  (int16_t)-32495,
  (int16_t)-32469,
  (int16_t)-32441,
  (int16_t)-32412,
  (int16_t)-32382,
  (int16_t)-32351,
  (int16_t)-32318,
  (int16_t)-32285,
  (int16_t)-32250,
  (int16_t)-32213,
  (int16_t)-32176,
  (int16_t)-32137,
  (int16_t)-32098,
  (int16_t)-32057,
  (int16_t)-32014,
  (int16_t)-31971,
  (int16_t)-31926,
  (int16_t)-31880,
  (int16_t)-31833,
  (int16_t)-31785,
  (int16_t)-31736,
  (int16_t)-31685,
  (int16_t)-31633,
  (int16_t)-31580,
  (int16_t)-31526,
  (int16_t)-31470,
  (int16_t)-31414,
  (int16_t)-31356,
  (int16_t)-31297,
  (int16_t)-31237,
  (int16_t)-31176,
  (int16_t)-31113,
  (int16_t)-31050,
  (int16_t)-30985,
  (int16_t)-30919,
  (int16_t)-30852,
  (int16_t)-30783,
  (int16_t)-30714,
  (int16_t)-30643,
  (int16_t)-30571,
  (int16_t)-30498,
  (int16_t)-30424,
  (int16_t)-30349,
  (int16_t)-30273,
  (int16_t)-30195,
  (int16_t)-30117,
  (int16_t)-30037,
  (int16_t)-29956,
  (int16_t)-29874,
  (int16_t)-29791,
  (int16_t)-29706,
  (int16_t)-29621,
  (int16_t)-29534,
  (int16_t)-29447,
  (int16_t)-29358,
  (int16_t)-29268,
  (int16_t)-29177,
  (int16_t)-29085,
  (int16_t)-28992,
  (int16_t)-28898,
  (int16_t)-28803,
  (int16_t)-28706,
  (int16_t)-28609,
  (int16_t)-28510,
  (int16_t)-28411,
  (int16_t)-28310,
  (int16_t)-28208,
  (int16_t)-28105,
  (int16_t)-28001,
  (int16_t)-27896,
  (int16_t)-27790,
  (int16_t)-27683,
  (int16_t)-27575,
  (int16_t)-27466,
  (int16_t)-27356,
  (int16_t)-27245,
  (int16_t)-27133,
  (int16_t)-27019,
  (int16_t)-26905,
  (int16_t)-26790,
  (int16_t)-26674,
  (int16_t)-26556,
  (int16_t)-26438,
  (int16_t)-26319,
  (int16_t)-26198,
  (int16_t)-26077,
  (int16_t)-25955,
  (int16_t)-25832,
  (int16_t)-25708,
  (int16_t)-25582,
  (int16_t)-25456,
  (int16_t)-25329,
  (int16_t)-25201,
  (int16_t)-25072,
  (int16_t)-24942,
  (int16_t)-24811,
  (int16_t)-24680,
  (int16_t)-24547,
  (int16_t)-24413,
  (int16_t)-24279,
  (int16_t)-24143,
  (int16_t)-24007,
  (int16_t)-23870,
  (int16_t)-23731,
  (int16_t)-23592,
  (int16_t)-23452,
  (int16_t)-23311,
  (int16_t)-23170,
  (int16_t)-23027,
  (int16_t)-22884,
  (int16_t)-22739,
  (int16_t)-22594,
  (int16_t)-22448,
  (int16_t)-22301,
  (int16_t)-22154,
  (int16_t)-22005,
  (int16_t)-21856,
  (int16_t)-21705,
  (int16_t)-21554,
  (int16_t)-21403,
  (int16_t)-21250,
  (int16_t)-21096,
  (int16_t)-20942,
  (int16_t)-20787,
  (int16_t)-20631,
  (int16_t)-20475,
  (int16_t)-20317,
  (int16_t)-20159,
  (int16_t)-20000,
  (int16_t)-19841,
  (int16_t)-19680,
  (int16_t)-19519,
  (int16_t)-19357,
  (int16_t)-19195,
  (int16_t)-19032,
  (int16_t)-18868,
  (int16_t)-18703,
  (int16_t)-18537,
  (int16_t)-18371,
  (int16_t)-18204,
  (int16_t)-18037,
  (int16_t)-17869,
  (int16_t)-17700,
  (int16_t)-17530,
  (int16_t)-17360,
  (int16_t)-17189,
  (int16_t)-17018,
  (int16_t)-16846,
  (int16_t)-16673,
  (int16_t)-16499,
  (int16_t)-16325,
  (int16_t)-16151,
  (int16_t)-15976,
  (int16_t)-15800,
  (int16_t)-15623,
  (int16_t)-15446,
  (int16_t)-15269,
  (int16_t)-15090,
  (int16_t)-14912,
  (int16_t)-14732,
  (int16_t)-14553,
  (int16_t)-14372,
  (int16_t)-14191,
  (int16_t)-14010,
  (int16_t)-13828,
  (int16_t)-13645,
  (int16_t)-13462,
  (int16_t)-13279,
  (int16_t)-13094,
  (int16_t)-12910,
  (int16_t)-12725,
  (int16_t)-12539,
  (int16_t)-12353,
  (int16_t)-12167,
  (int16_t)-11980,
  (int16_t)-11793,
  (int16_t)-11605,
  (int16_t)-11417,
  (int16_t)-11228,
  (int16_t)-11039,
  (int16_t)-10849,
  (int16_t)-10659,
  (int16_t)-10469,
  (int16_t)-10278,
  (int16_t)-10087,
  (int16_t)-9896,
  (int16_t)-9704,
  (int16_t)-9512,
  (int16_t)-9319,
  (int16_t)-9126,
  (int16_t)-8933,
  (int16_t)-8739,
  (int16_t)-8545,
  (int16_t)-8351,
  (int16_t)-8157,
  (int16_t)-7962,
  (int16_t)-7767,
  (int16_t)-7571,
  (int16_t)-7375,
  (int16_t)-7179,
  (int16_t)-6983,
  (int16_t)-6786,
  (int16_t)-6590,
  (int16_t)-6393,
  (int16_t)-6195,
  (int16_t)-5998,
  (int16_t)-5800,
  (int16_t)-5602,
  (int16_t)-5404,
  (int16_t)-5205,
  (int16_t)-5007,
  (int16_t)-4808,
  (int16_t)-4609,
  (int16_t)-4410,
  (int16_t)-4210,
  (int16_t)-4011,
  (int16_t)-3811,
  (int16_t)-3612,
  (int16_t)-3412,
  (int16_t)-3212,
  (int16_t)-3012,
  (int16_t)-2811,
  (int16_t)-2611,
  (int16_t)-2410,
  (int16_t)-2210,
  (int16_t)-2009,
  (int16_t)-1809,
  (int16_t)-1608,
  (int16_t)-1407,
  (int16_t)-1206,
  (int16_t)-1005,
  (int16_t)-804,
  (int16_t)-603,
  (int16_t)-402,
  (int16_t)-201,
  (int16_t)0,
  (int16_t)201,
  (int16_t)402,
  (int16_t)603,
  (int16_t)804,
  (int16_t)1005,
  (int16_t)1206,
  (int16_t)1407,
  (int16_t)1608,
  (int16_t)1809,
  (int16_t)2009,
  (int16_t)2210,
  (int16_t)2410,
  (int16_t)2611,
  (int16_t)2811,
  (int16_t)3012,
  (int16_t)3212,
  (int16_t)3412,
  (int16_t)3612,
  (int16_t)3811,
  (int16_t)4011,
  (int16_t)4210,
  (int16_t)4410,
  (int16_t)4609,
  (int16_t)4808,
  (int16_t)5007,
  (int16_t)5205,
  (int16_t)5404,
  (int16_t)5602,
  (int16_t)5800,
  (int16_t)5998,
  (int16_t)6195,
  (int16_t)6393,
  (int16_t)6590,
  (int16_t)6786,
  (int16_t)6983,
  (int16_t)7179,
  (int16_t)7375,
  (int16_t)7571,
  (int16_t)7767,
  (int16_t)7962,
  (int16_t)8157,
  (int16_t)8351,
  (int16_t)8545,
  (int16_t)8739,
  (int16_t)8933,
  (int16_t)9126,
  (int16_t)9319,
  (int16_t)9512,
  (int16_t)9704,
  (int16_t)9896,
  (int16_t)10087,
  (int16_t)10278,
  (int16_t)10469,
  (int16_t)10659,
  (int16_t)10849,
  (int16_t)11039,
  (int16_t)11228,
  (int16_t)11417,
  (int16_t)11605,
  (int16_t)11793,
  (int16_t)11980,
  (int16_t)12167,
  (int16_t)12353,
  (int16_t)12539,
  (int16_t)12725,
  (int16_t)12910,
  (int16_t)13094,
  (int16_t)13279,
  (int16_t)13462,
  (int16_t)13645,
  (int16_t)13828,
  (int16_t)14010,
  (int16_t)14191,
  (int16_t)14372,
  (int16_t)14553,
  (int16_t)14732,
  (int16_t)14912,
  (int16_t)15090,
  (int16_t)15269,
  (int16_t)15446,
  (int16_t)15623,
  (int16_t)15800,
  (int16_t)15976,
  (int16_t)16151,
  (int16_t)16325,
  (int16_t)16499,
  (int16_t)16673,
  (int16_t)16846,
  (int16_t)17018,
  (int16_t)17189,
  (int16_t)17360,
  (int16_t)17530,
  (int16_t)17700,
  (int16_t)17869,
  (int16_t)18037,
  (int16_t)18204,
  (int16_t)18371,
  (int16_t)18537,
  (int16_t)18703,
  (int16_t)18868,
  (int16_t)19032,
  (int16_t)19195,
  (int16_t)19357,
  (int16_t)19519,
  (int16_t)19680,
  (int16_t)19841,
  (int16_t)20000,
  (int16_t)20159,
  (int16_t)20317,
  (int16_t)20475,
  (int16_t)20631,
  (int16_t)20787,
  (int16_t)20942,
  (int16_t)21096,
  (int16_t)21250,
  (int16_t)21403,
  (int16_t)21554,
  (int16_t)21705,
  (int16_t)21856,
  (int16_t)22005,
  (int16_t)22154,
  (int16_t)22301,
  (int16_t)22448,
  (int16_t)22594,
  (int16_t)22739,
  (int16_t)22884,
  (int16_t)23027,
  (int16_t)23170,
  (int16_t)23311,
  (int16_t)23452,
  (int16_t)23592,
  (int16_t)23731,
  (int16_t)23870,
  (int16_t)24007,
  (int16_t)24143,
  (int16_t)24279,
  (int16_t)24413,
  (int16_t)24547,
  (int16_t)24680,
  (int16_t)24811,
  (int16_t)24942,
  (int16_t)25072,
  (int16_t)25201,
  (int16_t)25329,
  (int16_t)25456,
  (int16_t)25582,
  (int16_t)25708,
  (int16_t)25832,
  (int16_t)25955,
  (int16_t)26077,
  (int16_t)26198,
  (int16_t)26319,
  (int16_t)26438,
  (int16_t)26556,
  (int16_t)26674,
  (int16_t)26790,
  (int16_t)26905,
  (int16_t)27019,
  (int16_t)27133,
  (int16_t)27245,
  (int16_t)27356,
  (int16_t)27466,
  (int16_t)27575,
  (int16_t)27683,
  (int16_t)27790,
  (int16_t)27896,
  (int16_t)28001,
  (int16_t)28105,
  (int16_t)28208,
  (int16_t)28310,
  (int16_t)28411,
  (int16_t)28510,
  (int16_t)28609,
  (int16_t)28706,
  (int16_t)28803,
  (int16_t)28898,
  (int16_t)28992,
  (int16_t)29085,
  (int16_t)29177,
  (int16_t)29268,
  (int16_t)29358,
  (int16_t)29447,
  (int16_t)29534,
  (int16_t)29621,
  (int16_t)29706,
  (int16_t)29791,
  (int16_t)29874,
  (int16_t)29956,
  (int16_t)30037,
  (int16_t)30117,
  (int16_t)30195,
  (int16_t)30273,
  (int16_t)30349,
  (int16_t)30424,
  (int16_t)30498,
  (int16_t)30571,
  (int16_t)30643,
  (int16_t)30714,
  (int16_t)30783,
  (int16_t)30852,
  (int16_t)30919,
  (int16_t)30985,
  (int16_t)31050,
  (int16_t)31113,
  (int16_t)31176,
  (int16_t)31237,
  (int16_t)31297,
  (int16_t)31356,
  (int16_t)31414,
  (int16_t)31470,
  (int16_t)31526,
  (int16_t)31580,
  (int16_t)31633,
  (int16_t)31685,
  (int16_t)31736,
  (int16_t)31785,
  (int16_t)31833,
  (int16_t)31880,
  (int16_t)31926,
  (int16_t)31971,
  (int16_t)32014,
  (int16_t)32057,
  (int16_t)32098,
  (int16_t)32137,
  (int16_t)32176,
  (int16_t)32213,
  (int16_t)32250,
  (int16_t)32285,
  (int16_t)32318,
  (int16_t)32351,
  (int16_t)32382,
  (int16_t)32412,
  (int16_t)32441,
  (int16_t)32469,
  (int16_t)32495,
  (int16_t)32521,
  (int16_t)32545,
  (int16_t)32567,
  (int16_t)32589,
  (int16_t)32609,
  (int16_t)32628,
  (int16_t)32646,
  (int16_t)32663,
  (int16_t)32678,
  (int16_t)32692,
  (int16_t)32705,
  (int16_t)32717,
  (int16_t)32728,
  (int16_t)32737,
  (int16_t)32745,
  (int16_t)32752,
  (int16_t)32757,
  (int16_t)32761,
  (int16_t)32765,
  (int16_t)32766
};

static const int16_t __not_in_flash_func(bpf_fs4_cw)(const int16_t sample)
{
  // 31250, 60dB, 400Hz, 201 taps
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(4);
  __mac_tap(0);
  __mac_tap(-5);
  __mac_tap(0);
  __mac_tap(6);
  __mac_tap(0);
  __mac_tap(-7);
  __mac_tap(0);
  __mac_tap(7);
  __mac_tap(0);
  __mac_tap(-7);
  __mac_tap(0);
  __mac_tap(7);
  __mac_tap(0);
  __mac_tap(-6);
  __mac_tap(0);
  __mac_tap(5);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(0);
  __mac_tap(0);
  __mac_tap(4);
  __mac_tap(0);
  __mac_tap(-9);
  __mac_tap(0);
  __mac_tap(15);
  __mac_tap(0);
  __mac_tap(-23);
  __mac_tap(0);
  __mac_tap(32);
  __mac_tap(0);
  __mac_tap(-42);
  __mac_tap(0);
  __mac_tap(54);
  __mac_tap(0);
  __mac_tap(-68);
  __mac_tap(0);
  __mac_tap(84);
  __mac_tap(0);
  __mac_tap(-102);
  __mac_tap(0);
  __mac_tap(121);
  __mac_tap(0);
  __mac_tap(-143);
  __mac_tap(0);
  __mac_tap(166);
  __mac_tap(0);
  __mac_tap(-191);
  __mac_tap(0);
  __mac_tap(218);
  __mac_tap(0);
  __mac_tap(-246);
  __mac_tap(0);
  __mac_tap(276);
  __mac_tap(0);
  __mac_tap(-308);
  __mac_tap(0);
  __mac_tap(340);
  __mac_tap(0);
  __mac_tap(-374);
  __mac_tap(0);
  __mac_tap(408);
  __mac_tap(0);
  __mac_tap(-443);
  __mac_tap(0);
  __mac_tap(478);
  __mac_tap(0);
  __mac_tap(-513);
  __mac_tap(0);
  __mac_tap(548);
  __mac_tap(0);
  __mac_tap(-582);
  __mac_tap(0);
  __mac_tap(615);
  __mac_tap(0);
  __mac_tap(-647);
  __mac_tap(0);
  __mac_tap(678);
  __mac_tap(0);
  __mac_tap(-706);
  __mac_tap(0);
  __mac_tap(732);
  __mac_tap(0);
  __mac_tap(-756);
  __mac_tap(0);
  __mac_tap(777);
  __mac_tap(0);
  __mac_tap(-796);
  __mac_tap(0);
  __mac_tap(811);
  __mac_tap(0);
  __mac_tap(-823);
  __mac_tap(0);
  __mac_tap(832);
  __mac_tap(0);
  __mac_tap(-837);
  __mac_tap(0);
  __mac_tap(839);
  __mac_tap(0);
  __mac_tap(-837);
  __mac_tap(0);
  __mac_tap(832);
  __mac_tap(0);
  __mac_tap(-823);
  __mac_tap(0);
  __mac_tap(811);
  __mac_tap(0);
  __mac_tap(-796);
  __mac_tap(0);
  __mac_tap(777);
  __mac_tap(0);
  __mac_tap(-756);
  __mac_tap(0);
  __mac_tap(732);
  __mac_tap(0);
  __mac_tap(-706);
  __mac_tap(0);
  __mac_tap(678);
  __mac_tap(0);
  __mac_tap(-647);
  __mac_tap(0);
  __mac_tap(615);
  __mac_tap(0);
  __mac_tap(-582);
  __mac_tap(0);
  __mac_tap(548);
  __mac_tap(0);
  __mac_tap(-513);
  __mac_tap(0);
  __mac_tap(478);
  __mac_tap(0);
  __mac_tap(-443);
  __mac_tap(0);
  __mac_tap(408);
  __mac_tap(0);
  __mac_tap(-374);
  __mac_tap(0);
  __mac_tap(340);
  __mac_tap(0);
  __mac_tap(-308);
  __mac_tap(0);
  __mac_tap(276);
  __mac_tap(0);
  __mac_tap(-246);
  __mac_tap(0);
  __mac_tap(218);
  __mac_tap(0);
  __mac_tap(-191);
  __mac_tap(0);
  __mac_tap(166);
  __mac_tap(0);
  __mac_tap(-143);
  __mac_tap(0);
  __mac_tap(121);
  __mac_tap(0);
  __mac_tap(-102);
  __mac_tap(0);
  __mac_tap(84);
  __mac_tap(0);
  __mac_tap(-68);
  __mac_tap(0);
  __mac_tap(54);
  __mac_tap(0);
  __mac_tap(-42);
  __mac_tap(0);
  __mac_tap(32);
  __mac_tap(0);
  __mac_tap(-23);
  __mac_tap(0);
  __mac_tap(15);
  __mac_tap(0);
  __mac_tap(-9);
  __mac_tap(0);
  __mac_tap(4);
  __mac_tap(0);
  __mac_tap(0);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(5);
  __mac_tap(0);
  __mac_tap(-6);
  __mac_tap(0);
  __mac_tap(7);
  __mac_tap(0);
  __mac_tap(-7);
  __mac_tap(0);
  __mac_tap(7);
  __mac_tap(0);
  __mac_tap(-7);
  __mac_tap(0);
  __mac_tap(6);
  __mac_tap(0);
  __mac_tap(-5);
  __mac_tap(0);
  __mac_tap(4);
  __mac_tap(0);
  __mac_tap(-3);
  return (int16_t)(acc >> 15);
}

// float versions of FIR are experimental and not in use in this code
static const int16_t __not_in_flash_func(bpf_fs4_cw_f)(const int16_t sample)
{
  // 31250, 60dB, 400Hz, 201 taps
  static float x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = (float)sample/32768.0f;
  float acc = 0.0f;
  __mac_tap(-0.0001f);
  __mac_tap(0.0f);
  __mac_tap(0.000127f);
  __mac_tap(0.0f);
  __mac_tap(-0.000154f);
  __mac_tap(0.0f);
  __mac_tap(0.000179f);
  __mac_tap(0.0f);
  __mac_tap(-0.000199f);
  __mac_tap(0.0f);
  __mac_tap(0.000212f);
  __mac_tap(0.0f);
  __mac_tap(-0.000217f);
  __mac_tap(0.0f);
  __mac_tap(0.000209f);
  __mac_tap(0.0f);
  __mac_tap(-0.000187f);
  __mac_tap(0.0f);
  __mac_tap(0.000146f);
  __mac_tap(0.0f);
  __mac_tap(-0.000083f);
  __mac_tap(0.0f);
  __mac_tap(-0.000006f);
  __mac_tap(0.0f);
  __mac_tap(0.000124f);
  __mac_tap(0.0f);
  __mac_tap(-0.000276f);
  __mac_tap(0.0f);
  __mac_tap(0.000465f);
  __mac_tap(0.0f);
  __mac_tap(-0.000694f);
  __mac_tap(0.0f);
  __mac_tap(0.000968f);
  __mac_tap(0.0f);
  __mac_tap(-0.00129f);
  __mac_tap(0.0f);
  __mac_tap(0.001662f);
  __mac_tap(0.0f);
  __mac_tap(-0.002088f);
  __mac_tap(0.0f);
  __mac_tap(0.002569f);
  __mac_tap(0.0f);
  __mac_tap(-0.003106f);
  __mac_tap(0.0f);
  __mac_tap(0.003701f);
  __mac_tap(0.0f);
  __mac_tap(-0.004354f);
  __mac_tap(0.0f);
  __mac_tap(0.005064f);
  __mac_tap(0.0f);
  __mac_tap(-0.00583f);
  __mac_tap(0.0f);
  __mac_tap(0.00665f);
  __mac_tap(0.0f);
  __mac_tap(-0.007519f);
  __mac_tap(0.0f);
  __mac_tap(0.008436f);
  __mac_tap(0.0f);
  __mac_tap(-0.009394f);
  __mac_tap(0.0f);
  __mac_tap(0.010389f);
  __mac_tap(0.0f);
  __mac_tap(-0.011415f);
  __mac_tap(0.0f);
  __mac_tap(0.012463f);
  __mac_tap(0.0f);
  __mac_tap(-0.013527f);
  __mac_tap(0.0f);
  __mac_tap(0.014598f);
  __mac_tap(0.0f);
  __mac_tap(-0.015668f);
  __mac_tap(0.0f);
  __mac_tap(0.016728f);
  __mac_tap(0.0f);
  __mac_tap(-0.017768f);
  __mac_tap(0.0f);
  __mac_tap(0.018779f);
  __mac_tap(0.0f);
  __mac_tap(-0.019751f);
  __mac_tap(0.0f);
  __mac_tap(0.020676f);
  __mac_tap(0.0f);
  __mac_tap(-0.021544f);
  __mac_tap(0.0f);
  __mac_tap(0.022347f);
  __mac_tap(0.0f);
  __mac_tap(-0.023076f);
  __mac_tap(0.0f);
  __mac_tap(0.023725f);
  __mac_tap(0.0f);
  __mac_tap(-0.024285f);
  __mac_tap(0.0f);
  __mac_tap(0.024752f);
  __mac_tap(0.0f);
  __mac_tap(-0.025121f);
  __mac_tap(0.0f);
  __mac_tap(0.025387f);
  __mac_tap(0.0f);
  __mac_tap(-0.025548f);
  __mac_tap(0.0f);
  __mac_tap(0.025602f);
  __mac_tap(0.0f);
  __mac_tap(-0.025548f);
  __mac_tap(0.0f);
  __mac_tap(0.025387f);
  __mac_tap(0.0f);
  __mac_tap(-0.025121f);
  __mac_tap(0.0f);
  __mac_tap(0.024752f);
  __mac_tap(0.0f);
  __mac_tap(-0.024285f);
  __mac_tap(0.0f);
  __mac_tap(0.023725f);
  __mac_tap(0.0f);
  __mac_tap(-0.023076f);
  __mac_tap(0.0f);
  __mac_tap(0.022347f);
  __mac_tap(0.0f);
  __mac_tap(-0.021544f);
  __mac_tap(0.0f);
  __mac_tap(0.020676f);
  __mac_tap(0.0f);
  __mac_tap(-0.019751f);
  __mac_tap(0.0f);
  __mac_tap(0.018779f);
  __mac_tap(0.0f);
  __mac_tap(-0.017768f);
  __mac_tap(0.0f);
  __mac_tap(0.016728f);
  __mac_tap(0.0f);
  __mac_tap(-0.015668f);
  __mac_tap(0.0f);
  __mac_tap(0.014598f);
  __mac_tap(0.0f);
  __mac_tap(-0.013527f);
  __mac_tap(0.0f);
  __mac_tap(0.012463f);
  __mac_tap(0.0f);
  __mac_tap(-0.011415f);
  __mac_tap(0.0f);
  __mac_tap(0.010389f);
  __mac_tap(0.0f);
  __mac_tap(-0.009394f);
  __mac_tap(0.0f);
  __mac_tap(0.008436f);
  __mac_tap(0.0f);
  __mac_tap(-0.007519f);
  __mac_tap(0.0f);
  __mac_tap(0.00665f);
  __mac_tap(0.0f);
  __mac_tap(-0.00583f);
  __mac_tap(0.0f);
  __mac_tap(0.005064f);
  __mac_tap(0.0f);
  __mac_tap(-0.004354f);
  __mac_tap(0.0f);
  __mac_tap(0.003701f);
  __mac_tap(0.0f);
  __mac_tap(-0.003106f);
  __mac_tap(0.0f);
  __mac_tap(0.002569f);
  __mac_tap(0.0f);
  __mac_tap(-0.002088f);
  __mac_tap(0.0f);
  __mac_tap(0.001662f);
  __mac_tap(0.0f);
  __mac_tap(-0.00129f);
  __mac_tap(0.0f);
  __mac_tap(0.000968f);
  __mac_tap(0.0f);
  __mac_tap(-0.000694f);
  __mac_tap(0.0f);
  __mac_tap(0.000465f);
  __mac_tap(0.0f);
  __mac_tap(-0.000276f);
  __mac_tap(0.0f);
  __mac_tap(0.000124f);
  __mac_tap(0.0f);
  __mac_tap(-0.000006f);
  __mac_tap(0.0f);
  __mac_tap(-0.000083f);
  __mac_tap(0.0f);
  __mac_tap(0.000146f);
  __mac_tap(0.0f);
  __mac_tap(-0.000187f);
  __mac_tap(0.0f);
  __mac_tap(0.000209f);
  __mac_tap(0.0f);
  __mac_tap(-0.000217f);
  __mac_tap(0.0f);
  __mac_tap(0.000212f);
  __mac_tap(0.0f);
  __mac_tap(-0.000199f);
  __mac_tap(0.0f);
  __mac_tap(0.000179f);
  __mac_tap(0.0f);
  __mac_tap(-0.000154f);
  __mac_tap(0.0f);
  __mac_tap(0.000127f);
  __mac_tap(0.0f);
  __mac_tap(-0.0001f);
  return (int16_t)(acc * 32768.0f);
}

static const int16_t __not_in_flash_func(lpf_fs4_cw)(const int16_t sample)
{
  // 31250, 31 taps, 7812, 60db
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(69);
  __mac_tap(0);
  __mac_tap(-191);
  __mac_tap(0);
  __mac_tap(421);
  __mac_tap(0);
  __mac_tap(-827);
  __mac_tap(0);
  __mac_tap(1558);
  __mac_tap(0);
  __mac_tap(-3135);
  __mac_tap(0);
  __mac_tap(10312);
  __mac_tap(16384);
  __mac_tap(10312);
  __mac_tap(0);
  __mac_tap(-3135);
  __mac_tap(0);
  __mac_tap(1558);
  __mac_tap(0);
  __mac_tap(-827);
  __mac_tap(0);
  __mac_tap(421);
  __mac_tap(0);
  __mac_tap(-191);
  __mac_tap(0);
  __mac_tap(69);
  __mac_tap(0);
  __mac_tap(-14);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(bpf_300_2400)(const int16_t sample)
{
  // nominal 31250 sample rate
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-1);
  __mac_tap(-1);
  __mac_tap(1);
  __mac_tap(2);
  __mac_tap(5);
  __mac_tap(6);
  __mac_tap(8);
  __mac_tap(8);
  __mac_tap(7);
  __mac_tap(4);
  __mac_tap(2);
  __mac_tap(-1);
  __mac_tap(-2);
  __mac_tap(0);
  __mac_tap(3);
  __mac_tap(9);
  __mac_tap(16);
  __mac_tap(24);
  __mac_tap(30);
  __mac_tap(33);
  __mac_tap(32);
  __mac_tap(27);
  __mac_tap(19);
  __mac_tap(11);
  __mac_tap(3);
  __mac_tap(0);
  __mac_tap(2);
  __mac_tap(10);
  __mac_tap(23);
  __mac_tap(40);
  __mac_tap(56);
  __mac_tap(68);
  __mac_tap(72);
  __mac_tap(67);
  __mac_tap(52);
  __mac_tap(31);
  __mac_tap(8);
  __mac_tap(-13);
  __mac_tap(-25);
  __mac_tap(-24);
  __mac_tap(-11);
  __mac_tap(14);
  __mac_tap(44);
  __mac_tap(73);
  __mac_tap(92);
  __mac_tap(95);
  __mac_tap(79);
  __mac_tap(44);
  __mac_tap(-4);
  __mac_tap(-57);
  __mac_tap(-102);
  __mac_tap(-131);
  __mac_tap(-136);
  __mac_tap(-114);
  __mac_tap(-72);
  __mac_tap(-19);
  __mac_tap(31);
  __mac_tap(63);
  __mac_tap(65);
  __mac_tap(30);
  __mac_tap(-39);
  __mac_tap(-132);
  __mac_tap(-232);
  __mac_tap(-320);
  __mac_tap(-375);
  __mac_tap(-385);
  __mac_tap(-346);
  __mac_tap(-268);
  __mac_tap(-168);
  __mac_tap(-72);
  __mac_tap(-8);
  __mac_tap(2);
  __mac_tap(-55);
  __mac_tap(-176);
  __mac_tap(-343);
  __mac_tap(-525);
  __mac_tap(-683);
  __mac_tap(-782);
  __mac_tap(-794);
  __mac_tap(-711);
  __mac_tap(-545);
  __mac_tap(-329);
  __mac_tap(-113);
  __mac_tap(48);
  __mac_tap(103);
  __mac_tap(20);
  __mac_tap(-207);
  __mac_tap(-550);
  __mac_tap(-951);
  __mac_tap(-1327);
  __mac_tap(-1587);
  __mac_tap(-1645);
  __mac_tap(-1440);
  __mac_tap(-947);
  __mac_tap(-190);
  __mac_tap(765);
  __mac_tap(1810);
  __mac_tap(2818);
  __mac_tap(3656);
  __mac_tap(4210);
  __mac_tap(4404);
  __mac_tap(4210);
  __mac_tap(3656);
  __mac_tap(2818);
  __mac_tap(1810);
  __mac_tap(765);
  __mac_tap(-190);
  __mac_tap(-947);
  __mac_tap(-1440);
  __mac_tap(-1645);
  __mac_tap(-1587);
  __mac_tap(-1327);
  __mac_tap(-951);
  __mac_tap(-550);
  __mac_tap(-207);
  __mac_tap(20);
  __mac_tap(103);
  __mac_tap(48);
  __mac_tap(-113);
  __mac_tap(-329);
  __mac_tap(-545);
  __mac_tap(-711);
  __mac_tap(-794);
  __mac_tap(-782);
  __mac_tap(-683);
  __mac_tap(-525);
  __mac_tap(-343);
  __mac_tap(-176);
  __mac_tap(-55);
  __mac_tap(2);
  __mac_tap(-8);
  __mac_tap(-72);
  __mac_tap(-168);
  __mac_tap(-268);
  __mac_tap(-346);
  __mac_tap(-385);
  __mac_tap(-375);
  __mac_tap(-320);
  __mac_tap(-232);
  __mac_tap(-132);
  __mac_tap(-39);
  __mac_tap(30);
  __mac_tap(65);
  __mac_tap(63);
  __mac_tap(31);
  __mac_tap(-19);
  __mac_tap(-72);
  __mac_tap(-114);
  __mac_tap(-136);
  __mac_tap(-131);
  __mac_tap(-102);
  __mac_tap(-57);
  __mac_tap(-4);
  __mac_tap(44);
  __mac_tap(79);
  __mac_tap(95);
  __mac_tap(92);
  __mac_tap(73);
  __mac_tap(44);
  __mac_tap(14);
  __mac_tap(-11);
  __mac_tap(-24);
  __mac_tap(-25);
  __mac_tap(-13);
  __mac_tap(8);
  __mac_tap(31);
  __mac_tap(52);
  __mac_tap(67);
  __mac_tap(72);
  __mac_tap(68);
  __mac_tap(56);
  __mac_tap(40);
  __mac_tap(23);
  __mac_tap(10);
  __mac_tap(2);
  __mac_tap(0);
  __mac_tap(3);
  __mac_tap(11);
  __mac_tap(19);
  __mac_tap(27);
  __mac_tap(32);
  __mac_tap(33);
  __mac_tap(30);
  __mac_tap(24);
  __mac_tap(16);
  __mac_tap(9);
  __mac_tap(3);
  __mac_tap(0);
  __mac_tap(-2);
  __mac_tap(-1);
  __mac_tap(2);
  __mac_tap(4);
  __mac_tap(7);
  __mac_tap(8);
  __mac_tap(8);
  __mac_tap(6);
  __mac_tap(5);
  __mac_tap(2);
  __mac_tap(1);
  __mac_tap(-1);
  __mac_tap(-1);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(bpf_600_800_org)(const int16_t sample)
{
  // nominal 31250 sample rate
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(1);
  __mac_tap(2);
  __mac_tap(3);
  __mac_tap(4);
  __mac_tap(6);
  __mac_tap(7);
  __mac_tap(9);
  __mac_tap(11);
  __mac_tap(13);
  __mac_tap(15);
  __mac_tap(16);
  __mac_tap(18);
  __mac_tap(19);
  __mac_tap(19);
  __mac_tap(20);
  __mac_tap(19);
  __mac_tap(18);
  __mac_tap(16);
  __mac_tap(13);
  __mac_tap(9);
  __mac_tap(5);
  __mac_tap(-1);
  __mac_tap(-7);
  __mac_tap(-14);
  __mac_tap(-22);
  __mac_tap(-30);
  __mac_tap(-38);
  __mac_tap(-47);
  __mac_tap(-56);
  __mac_tap(-64);
  __mac_tap(-71);
  __mac_tap(-78);
  __mac_tap(-83);
  __mac_tap(-87);
  __mac_tap(-89);
  __mac_tap(-89);
  __mac_tap(-87);
  __mac_tap(-82);
  __mac_tap(-75);
  __mac_tap(-66);
  __mac_tap(-54);
  __mac_tap(-39);
  __mac_tap(-23);
  __mac_tap(-4);
  __mac_tap(17);
  __mac_tap(38);
  __mac_tap(61);
  __mac_tap(84);
  __mac_tap(107);
  __mac_tap(130);
  __mac_tap(151);
  __mac_tap(170);
  __mac_tap(187);
  __mac_tap(201);
  __mac_tap(211);
  __mac_tap(217);
  __mac_tap(219);
  __mac_tap(216);
  __mac_tap(208);
  __mac_tap(195);
  __mac_tap(177);
  __mac_tap(154);
  __mac_tap(126);
  __mac_tap(95);
  __mac_tap(59);
  __mac_tap(21);
  __mac_tap(-20);
  __mac_tap(-62);
  __mac_tap(-104);
  __mac_tap(-147);
  __mac_tap(-187);
  __mac_tap(-226);
  __mac_tap(-261);
  __mac_tap(-292);
  __mac_tap(-318);
  __mac_tap(-338);
  __mac_tap(-351);
  __mac_tap(-358);
  __mac_tap(-357);
  __mac_tap(-349);
  __mac_tap(-333);
  __mac_tap(-310);
  __mac_tap(-280);
  __mac_tap(-243);
  __mac_tap(-201);
  __mac_tap(-153);
  __mac_tap(-102);
  __mac_tap(-47);
  __mac_tap(9);
  __mac_tap(66);
  __mac_tap(122);
  __mac_tap(177);
  __mac_tap(228);
  __mac_tap(275);
  __mac_tap(317);
  __mac_tap(353);
  __mac_tap(382);
  __mac_tap(402);
  __mac_tap(415);
  __mac_tap(419);
  __mac_tap(415);
  __mac_tap(402);
  __mac_tap(382);
  __mac_tap(353);
  __mac_tap(317);
  __mac_tap(275);
  __mac_tap(228);
  __mac_tap(177);
  __mac_tap(122);
  __mac_tap(66);
  __mac_tap(9);
  __mac_tap(-47);
  __mac_tap(-102);
  __mac_tap(-153);
  __mac_tap(-201);
  __mac_tap(-243);
  __mac_tap(-280);
  __mac_tap(-310);
  __mac_tap(-333);
  __mac_tap(-349);
  __mac_tap(-357);
  __mac_tap(-358);
  __mac_tap(-351);
  __mac_tap(-338);
  __mac_tap(-318);
  __mac_tap(-292);
  __mac_tap(-261);
  __mac_tap(-226);
  __mac_tap(-187);
  __mac_tap(-147);
  __mac_tap(-104);
  __mac_tap(-62);
  __mac_tap(-20);
  __mac_tap(21);
  __mac_tap(59);
  __mac_tap(95);
  __mac_tap(126);
  __mac_tap(154);
  __mac_tap(177);
  __mac_tap(195);
  __mac_tap(208);
  __mac_tap(216);
  __mac_tap(219);
  __mac_tap(217);
  __mac_tap(211);
  __mac_tap(201);
  __mac_tap(187);
  __mac_tap(170);
  __mac_tap(151);
  __mac_tap(130);
  __mac_tap(107);
  __mac_tap(84);
  __mac_tap(61);
  __mac_tap(38);
  __mac_tap(17);
  __mac_tap(-4);
  __mac_tap(-23);
  __mac_tap(-39);
  __mac_tap(-54);
  __mac_tap(-66);
  __mac_tap(-75);
  __mac_tap(-82);
  __mac_tap(-87);
  __mac_tap(-89);
  __mac_tap(-89);
  __mac_tap(-87);
  __mac_tap(-83);
  __mac_tap(-78);
  __mac_tap(-71);
  __mac_tap(-64);
  __mac_tap(-56);
  __mac_tap(-47);
  __mac_tap(-38);
  __mac_tap(-30);
  __mac_tap(-22);
  __mac_tap(-14);
  __mac_tap(-7);
  __mac_tap(-1);
  __mac_tap(5);
  __mac_tap(9);
  __mac_tap(13);
  __mac_tap(16);
  __mac_tap(18);
  __mac_tap(19);
  __mac_tap(20);
  __mac_tap(19);
  __mac_tap(19);
  __mac_tap(18);
  __mac_tap(16);
  __mac_tap(15);
  __mac_tap(13);
  __mac_tap(11);
  __mac_tap(9);
  __mac_tap(7);
  __mac_tap(6);
  __mac_tap(4);
  __mac_tap(3);
  __mac_tap(2);
  __mac_tap(1);
  __mac_tap(0);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(bpf_600_800)(const int16_t sample)
{
  // 31250 sample rate
  // 600 - 800
  // 45dB
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(1);
  __mac_tap(4);
  __mac_tap(7);
  __mac_tap(10);
  __mac_tap(14);
  __mac_tap(18);
  __mac_tap(23);
  __mac_tap(27);
  __mac_tap(31);
  __mac_tap(35);
  __mac_tap(39);
  __mac_tap(41);
  __mac_tap(44);
  __mac_tap(45);
  __mac_tap(45);
  __mac_tap(44);
  __mac_tap(42);
  __mac_tap(38);
  __mac_tap(33);
  __mac_tap(27);
  __mac_tap(19);
  __mac_tap(9);
  __mac_tap(-1);
  __mac_tap(-13);
  __mac_tap(-26);
  __mac_tap(-39);
  __mac_tap(-52);
  __mac_tap(-66);
  __mac_tap(-79);
  __mac_tap(-92);
  __mac_tap(-104);
  __mac_tap(-114);
  __mac_tap(-122);
  __mac_tap(-129);
  __mac_tap(-133);
  __mac_tap(-134);
  __mac_tap(-132);
  __mac_tap(-127);
  __mac_tap(-119);
  __mac_tap(-107);
  __mac_tap(-92);
  __mac_tap(-75);
  __mac_tap(-54);
  __mac_tap(-31);
  __mac_tap(-5);
  __mac_tap(22);
  __mac_tap(50);
  __mac_tap(79);
  __mac_tap(108);
  __mac_tap(136);
  __mac_tap(163);
  __mac_tap(188);
  __mac_tap(210);
  __mac_tap(229);
  __mac_tap(243);
  __mac_tap(253);
  __mac_tap(258);
  __mac_tap(258);
  __mac_tap(253);
  __mac_tap(241);
  __mac_tap(225);
  __mac_tap(202);
  __mac_tap(175);
  __mac_tap(142);
  __mac_tap(106);
  __mac_tap(66);
  __mac_tap(23);
  __mac_tap(-22);
  __mac_tap(-68);
  __mac_tap(-114);
  __mac_tap(-159);
  __mac_tap(-202);
  __mac_tap(-242);
  __mac_tap(-278);
  __mac_tap(-309);
  __mac_tap(-335);
  __mac_tap(-355);
  __mac_tap(-367);
  __mac_tap(-373);
  __mac_tap(-371);
  __mac_tap(-361);
  __mac_tap(-343);
  __mac_tap(-318);
  __mac_tap(-287);
  __mac_tap(-248);
  __mac_tap(-204);
  __mac_tap(-156);
  __mac_tap(-103);
  __mac_tap(-48);
  __mac_tap(9);
  __mac_tap(67);
  __mac_tap(123);
  __mac_tap(178);
  __mac_tap(229);
  __mac_tap(276);
  __mac_tap(318);
  __mac_tap(353);
  __mac_tap(382);
  __mac_tap(403);
  __mac_tap(415);
  __mac_tap(419);
  __mac_tap(415);
  __mac_tap(403);
  __mac_tap(382);
  __mac_tap(353);
  __mac_tap(318);
  __mac_tap(276);
  __mac_tap(229);
  __mac_tap(178);
  __mac_tap(123);
  __mac_tap(67);
  __mac_tap(9);
  __mac_tap(-48);
  __mac_tap(-103);
  __mac_tap(-156);
  __mac_tap(-204);
  __mac_tap(-248);
  __mac_tap(-287);
  __mac_tap(-318);
  __mac_tap(-343);
  __mac_tap(-361);
  __mac_tap(-371);
  __mac_tap(-373);
  __mac_tap(-367);
  __mac_tap(-355);
  __mac_tap(-335);
  __mac_tap(-309);
  __mac_tap(-278);
  __mac_tap(-242);
  __mac_tap(-202);
  __mac_tap(-159);
  __mac_tap(-114);
  __mac_tap(-68);
  __mac_tap(-22);
  __mac_tap(23);
  __mac_tap(66);
  __mac_tap(106);
  __mac_tap(142);
  __mac_tap(175);
  __mac_tap(202);
  __mac_tap(225);
  __mac_tap(241);
  __mac_tap(253);
  __mac_tap(258);
  __mac_tap(258);
  __mac_tap(253);
  __mac_tap(243);
  __mac_tap(229);
  __mac_tap(210);
  __mac_tap(188);
  __mac_tap(163);
  __mac_tap(136);
  __mac_tap(108);
  __mac_tap(79);
  __mac_tap(50);
  __mac_tap(22);
  __mac_tap(-5);
  __mac_tap(-31);
  __mac_tap(-54);
  __mac_tap(-75);
  __mac_tap(-92);
  __mac_tap(-107);
  __mac_tap(-119);
  __mac_tap(-127);
  __mac_tap(-132);
  __mac_tap(-134);
  __mac_tap(-133);
  __mac_tap(-129);
  __mac_tap(-122);
  __mac_tap(-114);
  __mac_tap(-104);
  __mac_tap(-92);
  __mac_tap(-79);
  __mac_tap(-66);
  __mac_tap(-52);
  __mac_tap(-39);
  __mac_tap(-26);
  __mac_tap(-13);
  __mac_tap(-1);
  __mac_tap(9);
  __mac_tap(19);
  __mac_tap(27);
  __mac_tap(33);
  __mac_tap(38);
  __mac_tap(42);
  __mac_tap(44);
  __mac_tap(45);
  __mac_tap(45);
  __mac_tap(44);
  __mac_tap(41);
  __mac_tap(39);
  __mac_tap(35);
  __mac_tap(31);
  __mac_tap(27);
  __mac_tap(23);
  __mac_tap(18);
  __mac_tap(14);
  __mac_tap(10);
  __mac_tap(7);
  __mac_tap(4);
  __mac_tap(1);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_fs4)(const int16_t sample)
{
  // 31250
  // Taps: 199 (computationally 100 since cutoff is Fs/4)
  // Att: 45 (60dB+)
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(-10);
  __mac_tap(0);
  __mac_tap(12);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(16);
  __mac_tap(0);
  __mac_tap(-19);
  __mac_tap(0);
  __mac_tap(21);
  __mac_tap(0);
  __mac_tap(-24);
  __mac_tap(0);
  __mac_tap(27);
  __mac_tap(0);
  __mac_tap(-30);
  __mac_tap(0);
  __mac_tap(34);
  __mac_tap(0);
  __mac_tap(-37);
  __mac_tap(0);
  __mac_tap(41);
  __mac_tap(0);
  __mac_tap(-46);
  __mac_tap(0);
  __mac_tap(50);
  __mac_tap(0);
  __mac_tap(-55);
  __mac_tap(0);
  __mac_tap(60);
  __mac_tap(0);
  __mac_tap(-66);
  __mac_tap(0);
  __mac_tap(72);
  __mac_tap(0);
  __mac_tap(-78);
  __mac_tap(0);
  __mac_tap(85);
  __mac_tap(0);
  __mac_tap(-93);
  __mac_tap(0);
  __mac_tap(100);
  __mac_tap(0);
  __mac_tap(-109);
  __mac_tap(0);
  __mac_tap(118);
  __mac_tap(0);
  __mac_tap(-127);
  __mac_tap(0);
  __mac_tap(138);
  __mac_tap(0);
  __mac_tap(-149);
  __mac_tap(0);
  __mac_tap(161);
  __mac_tap(0);
  __mac_tap(-174);
  __mac_tap(0);
  __mac_tap(189);
  __mac_tap(0);
  __mac_tap(-204);
  __mac_tap(0);
  __mac_tap(221);
  __mac_tap(0);
  __mac_tap(-240);
  __mac_tap(0);
  __mac_tap(261);
  __mac_tap(0);
  __mac_tap(-284);
  __mac_tap(0);
  __mac_tap(311);
  __mac_tap(0);
  __mac_tap(-340);
  __mac_tap(0);
  __mac_tap(374);
  __mac_tap(0);
  __mac_tap(-414);
  __mac_tap(0);
  __mac_tap(460);
  __mac_tap(0);
  __mac_tap(-516);
  __mac_tap(0);
  __mac_tap(584);
  __mac_tap(0);
  __mac_tap(-669);
  __mac_tap(0);
  __mac_tap(779);
  __mac_tap(0);
  __mac_tap(-929);
  __mac_tap(0);
  __mac_tap(1143);
  __mac_tap(0);
  __mac_tap(-1478);
  __mac_tap(0);
  __mac_tap(2077);
  __mac_tap(0);
  __mac_tap(-3471);
  __mac_tap(0);
  __mac_tap(10429);
  __mac_tap(16384);
  __mac_tap(10429);
  __mac_tap(0);
  __mac_tap(-3471);
  __mac_tap(0);
  __mac_tap(2077);
  __mac_tap(0);
  __mac_tap(-1478);
  __mac_tap(0);
  __mac_tap(1143);
  __mac_tap(0);
  __mac_tap(-929);
  __mac_tap(0);
  __mac_tap(779);
  __mac_tap(0);
  __mac_tap(-669);
  __mac_tap(0);
  __mac_tap(584);
  __mac_tap(0);
  __mac_tap(-516);
  __mac_tap(0);
  __mac_tap(460);
  __mac_tap(0);
  __mac_tap(-414);
  __mac_tap(0);
  __mac_tap(374);
  __mac_tap(0);
  __mac_tap(-340);
  __mac_tap(0);
  __mac_tap(311);
  __mac_tap(0);
  __mac_tap(-284);
  __mac_tap(0);
  __mac_tap(261);
  __mac_tap(0);
  __mac_tap(-240);
  __mac_tap(0);
  __mac_tap(221);
  __mac_tap(0);
  __mac_tap(-204);
  __mac_tap(0);
  __mac_tap(189);
  __mac_tap(0);
  __mac_tap(-174);
  __mac_tap(0);
  __mac_tap(161);
  __mac_tap(0);
  __mac_tap(-149);
  __mac_tap(0);
  __mac_tap(138);
  __mac_tap(0);
  __mac_tap(-127);
  __mac_tap(0);
  __mac_tap(118);
  __mac_tap(0);
  __mac_tap(-109);
  __mac_tap(0);
  __mac_tap(100);
  __mac_tap(0);
  __mac_tap(-93);
  __mac_tap(0);
  __mac_tap(85);
  __mac_tap(0);
  __mac_tap(-78);
  __mac_tap(0);
  __mac_tap(72);
  __mac_tap(0);
  __mac_tap(-66);
  __mac_tap(0);
  __mac_tap(60);
  __mac_tap(0);
  __mac_tap(-55);
  __mac_tap(0);
  __mac_tap(50);
  __mac_tap(0);
  __mac_tap(-46);
  __mac_tap(0);
  __mac_tap(41);
  __mac_tap(0);
  __mac_tap(-37);
  __mac_tap(0);
  __mac_tap(34);
  __mac_tap(0);
  __mac_tap(-30);
  __mac_tap(0);
  __mac_tap(27);
  __mac_tap(0);
  __mac_tap(-24);
  __mac_tap(0);
  __mac_tap(21);
  __mac_tap(0);
  __mac_tap(-19);
  __mac_tap(0);
  __mac_tap(16);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(12);
  __mac_tap(0);
  __mac_tap(-10);
  __mac_tap(0);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(hpf_fs4)(const int16_t sample)
{
  // 31250
  // Taps: 199 (computationally 100 since cutoff is Fs/4)
  // Att: 45 (60dB+)
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(10);
  __mac_tap(0);
  __mac_tap(-12);
  __mac_tap(0);
  __mac_tap(14);
  __mac_tap(0);
  __mac_tap(-16);
  __mac_tap(0);
  __mac_tap(19);
  __mac_tap(0);
  __mac_tap(-21);
  __mac_tap(0);
  __mac_tap(24);
  __mac_tap(0);
  __mac_tap(-27);
  __mac_tap(0);
  __mac_tap(30);
  __mac_tap(0);
  __mac_tap(-34);
  __mac_tap(0);
  __mac_tap(37);
  __mac_tap(0);
  __mac_tap(-41);
  __mac_tap(0);
  __mac_tap(46);
  __mac_tap(0);
  __mac_tap(-50);
  __mac_tap(0);
  __mac_tap(55);
  __mac_tap(0);
  __mac_tap(-60);
  __mac_tap(0);
  __mac_tap(66);
  __mac_tap(0);
  __mac_tap(-72);
  __mac_tap(0);
  __mac_tap(78);
  __mac_tap(0);
  __mac_tap(-85);
  __mac_tap(0);
  __mac_tap(93);
  __mac_tap(0);
  __mac_tap(-100);
  __mac_tap(0);
  __mac_tap(109);
  __mac_tap(0);
  __mac_tap(-118);
  __mac_tap(0);
  __mac_tap(127);
  __mac_tap(0);
  __mac_tap(-138);
  __mac_tap(0);
  __mac_tap(149);
  __mac_tap(0);
  __mac_tap(-161);
  __mac_tap(0);
  __mac_tap(174);
  __mac_tap(0);
  __mac_tap(-189);
  __mac_tap(0);
  __mac_tap(204);
  __mac_tap(0);
  __mac_tap(-221);
  __mac_tap(0);
  __mac_tap(240);
  __mac_tap(0);
  __mac_tap(-261);
  __mac_tap(0);
  __mac_tap(284);
  __mac_tap(0);
  __mac_tap(-311);
  __mac_tap(0);
  __mac_tap(340);
  __mac_tap(0);
  __mac_tap(-374);
  __mac_tap(0);
  __mac_tap(414);
  __mac_tap(0);
  __mac_tap(-460);
  __mac_tap(0);
  __mac_tap(516);
  __mac_tap(0);
  __mac_tap(-584);
  __mac_tap(0);
  __mac_tap(669);
  __mac_tap(0);
  __mac_tap(-779);
  __mac_tap(0);
  __mac_tap(929);
  __mac_tap(0);
  __mac_tap(-1143);
  __mac_tap(0);
  __mac_tap(1478);
  __mac_tap(0);
  __mac_tap(-2077);
  __mac_tap(0);
  __mac_tap(3471);
  __mac_tap(0);
  __mac_tap(-10429);
  __mac_tap(16384);
  __mac_tap(-10429);
  __mac_tap(0);
  __mac_tap(3471);
  __mac_tap(0);
  __mac_tap(-2077);
  __mac_tap(0);
  __mac_tap(1478);
  __mac_tap(0);
  __mac_tap(-1143);
  __mac_tap(0);
  __mac_tap(929);
  __mac_tap(0);
  __mac_tap(-779);
  __mac_tap(0);
  __mac_tap(669);
  __mac_tap(0);
  __mac_tap(-584);
  __mac_tap(0);
  __mac_tap(516);
  __mac_tap(0);
  __mac_tap(-460);
  __mac_tap(0);
  __mac_tap(414);
  __mac_tap(0);
  __mac_tap(-374);
  __mac_tap(0);
  __mac_tap(340);
  __mac_tap(0);
  __mac_tap(-311);
  __mac_tap(0);
  __mac_tap(284);
  __mac_tap(0);
  __mac_tap(-261);
  __mac_tap(0);
  __mac_tap(240);
  __mac_tap(0);
  __mac_tap(-221);
  __mac_tap(0);
  __mac_tap(204);
  __mac_tap(0);
  __mac_tap(-189);
  __mac_tap(0);
  __mac_tap(174);
  __mac_tap(0);
  __mac_tap(-161);
  __mac_tap(0);
  __mac_tap(149);
  __mac_tap(0);
  __mac_tap(-138);
  __mac_tap(0);
  __mac_tap(127);
  __mac_tap(0);
  __mac_tap(-118);
  __mac_tap(0);
  __mac_tap(109);
  __mac_tap(0);
  __mac_tap(-100);
  __mac_tap(0);
  __mac_tap(93);
  __mac_tap(0);
  __mac_tap(-85);
  __mac_tap(0);
  __mac_tap(78);
  __mac_tap(0);
  __mac_tap(-72);
  __mac_tap(0);
  __mac_tap(66);
  __mac_tap(0);
  __mac_tap(-60);
  __mac_tap(0);
  __mac_tap(55);
  __mac_tap(0);
  __mac_tap(-50);
  __mac_tap(0);
  __mac_tap(46);
  __mac_tap(0);
  __mac_tap(-41);
  __mac_tap(0);
  __mac_tap(37);
  __mac_tap(0);
  __mac_tap(-34);
  __mac_tap(0);
  __mac_tap(30);
  __mac_tap(0);
  __mac_tap(-27);
  __mac_tap(0);
  __mac_tap(24);
  __mac_tap(0);
  __mac_tap(-21);
  __mac_tap(0);
  __mac_tap(19);
  __mac_tap(0);
  __mac_tap(-16);
  __mac_tap(0);
  __mac_tap(14);
  __mac_tap(0);
  __mac_tap(-12);
  __mac_tap(0);
  __mac_tap(10);
  __mac_tap(0);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(hpf_fs8)(const int16_t sample)
{
  // 31250
  // Taps: 57 (computationally 42 since cutoff is Fs/8)
  // Att: 60dB
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(-9);
  __mac_tap(-20);
  __mac_tap(-21);
  __mac_tap(0);
  __mac_tap(38);
  __mac_tap(71);
  __mac_tap(65);
  __mac_tap(0);
  __mac_tap(-102);
  __mac_tap(-178);
  __mac_tap(-154);
  __mac_tap(0);
  __mac_tap(223);
  __mac_tap(377);
  __mac_tap(317);
  __mac_tap(0);
  __mac_tap(-445);
  __mac_tap(-745);
  __mac_tap(-625);
  __mac_tap(0);
  __mac_tap(896);
  __mac_tap(1544);
  __mac_tap(1359);
  __mac_tap(0);
  __mac_tap(-2387);
  __mac_tap(-5147);
  __mac_tap(-7351);
  __mac_tap(24576);
  __mac_tap(-7351);
  __mac_tap(-5147);
  __mac_tap(-2387);
  __mac_tap(0);
  __mac_tap(1359);
  __mac_tap(1544);
  __mac_tap(896);
  __mac_tap(0);
  __mac_tap(-625);
  __mac_tap(-745);
  __mac_tap(-445);
  __mac_tap(0);
  __mac_tap(317);
  __mac_tap(377);
  __mac_tap(223);
  __mac_tap(0);
  __mac_tap(-154);
  __mac_tap(-178);
  __mac_tap(-102);
  __mac_tap(0);
  __mac_tap(65);
  __mac_tap(71);
  __mac_tap(38);
  __mac_tap(0);
  __mac_tap(-21);
  __mac_tap(-20);
  __mac_tap(-9);
  __mac_tap(0);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(hpf_4800)(const int16_t sample)
{
  // 31250
  // Taps: 101
  // Att: 60dB
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(4);
  __mac_tap(1);
  __mac_tap(-5);
  __mac_tap(-10);
  __mac_tap(-5);
  __mac_tap(8);
  __mac_tap(18);
  __mac_tap(14);
  __mac_tap(-8);
  __mac_tap(-29);
  __mac_tap(-28);
  __mac_tap(2);
  __mac_tap(41);
  __mac_tap(50);
  __mac_tap(12);
  __mac_tap(-50);
  __mac_tap(-79);
  __mac_tap(-38);
  __mac_tap(51);
  __mac_tap(113);
  __mac_tap(80);
  __mac_tap(-40);
  __mac_tap(-148);
  __mac_tap(-138);
  __mac_tap(7);
  __mac_tap(178);
  __mac_tap(215);
  __mac_tap(53);
  __mac_tap(-194);
  __mac_tap(-306);
  __mac_tap(-149);
  __mac_tap(183);
  __mac_tap(410);
  __mac_tap(291);
  __mac_tap(-131);
  __mac_tap(-518);
  __mac_tap(-492);
  __mac_tap(13);
  __mac_tap(623);
  __mac_tap(777);
  __mac_tap(212);
  __mac_tap(-717);
  __mac_tap(-1210);
  __mac_tap(-645);
  __mac_tap(792);
  __mac_tap(2020);
  __mac_tap(1690);
  __mac_tap(-839);
  __mac_tap(-4862);
  __mac_tap(-8566);
  __mac_tap(22701);
  __mac_tap(-8566);
  __mac_tap(-4862);
  __mac_tap(-839);
  __mac_tap(1690);
  __mac_tap(2020);
  __mac_tap(792);
  __mac_tap(-645);
  __mac_tap(-1210);
  __mac_tap(-717);
  __mac_tap(212);
  __mac_tap(777);
  __mac_tap(623);
  __mac_tap(13);
  __mac_tap(-492);
  __mac_tap(-518);
  __mac_tap(-131);
  __mac_tap(291);
  __mac_tap(410);
  __mac_tap(183);
  __mac_tap(-149);
  __mac_tap(-306);
  __mac_tap(-194);
  __mac_tap(53);
  __mac_tap(215);
  __mac_tap(178);
  __mac_tap(7);
  __mac_tap(-138);
  __mac_tap(-148);
  __mac_tap(-40);
  __mac_tap(80);
  __mac_tap(113);
  __mac_tap(51);
  __mac_tap(-38);
  __mac_tap(-79);
  __mac_tap(-50);
  __mac_tap(12);
  __mac_tap(50);
  __mac_tap(41);
  __mac_tap(2);
  __mac_tap(-28);
  __mac_tap(-29);
  __mac_tap(-8);
  __mac_tap(14);
  __mac_tap(18);
  __mac_tap(8);
  __mac_tap(-5);
  __mac_tap(-10);
  __mac_tap(-5);
  __mac_tap(1);
  __mac_tap(4);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(dc)(const int16_t in)
{
  static int32_t s = 0;
  static int32_t x1 = 0;
  static int16_t y1 = 0;
  s -= x1;
  x1 = (int32_t)in << 16;
  s += x1 - ((int32_t)y1 << 8);
  return (y1 = s >> 16);
}

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

const int16_t __not_in_flash_func(process_mic)(const int16_t s,const bool mode_LSB)
{
  // generate an SSB signal at FS/4 (7812 Hz)
  // 1. remove DC (IIR)
  // 2. bandpass filter (300 - 2400)
  // 3. upconvert to FS/4 (mix with BFO at FS/4)
  // 4. remove unwanted sideband (LPF/HPF at FS/4)
  volatile static int32_t alc = 256L;

  // BFO oscillates
  static uint8_t bfo = 0;
  const uint8_t phase = bfo & 0x03;
  bfo++;

  // 2400Hz LPF ( s>>3 = 5 Watts)
  // 2400Hz LPF ( s>>2 = 10 Watts)
  const int16_t lpf2400 = bpf_300_2400(dc(s>>1));

  // up convert to FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t v = 0;
  switch (phase)
  {
    case 0: v = +lpf2400; break;
    case 2: v = -lpf2400; break;
  }

  // remove the unwanted sideband
  v = mode_LSB?lpf_fs4(v):hpf_fs4(v);

  // ALC
  v = (int16_t)(((int32_t)v * alc) >> 8);
  if (abs(v)>511) alc--;

  return v;
}

volatile static float peak = 0.0f;

static const int16_t __not_in_flash_func(agc)(const int16_t in,const bool higain)
{
  const float magnitude = (float)abs(in);
  if (magnitude>peak)
  {
    peak = magnitude;
  }
  else
  {
    // 0.99996 is about 10dB per second
    peak *= 0.99996f;
  }

  // set maximum gain possible for 12 bits DAC
  const float m = 2047.0f/peak;

  // limit gain to max of 40 (32db) or 100 (40db)
  const float max_gain = higain?100.0f:40.0f;
  return (int16_t)((float)in*min(m,max_gain));
}

static const uint8_t __not_in_flash_func(smeter)(void)
{
  // S9 = peak of 50 (measured)
  uint8_t s = 0;
  if (peak<5.0f) return s;
  if (peak<50)
  {
    s = (uint8_t)roundf((log10f(peak-4.0f)*5.4f));
  }
  else
  {
    s = (uint8_t)roundf((log10f(peak-4.0f)*4.5f));
    if (s<9) s = 9;
  }
  return s;
}

static const int16_t __not_in_flash_func(process_cw_rx)(const int16_t s,const bool mode_CWL,const bool higain)
{
  // demodulate a CW signal at FS/4 (7812 Hz)
  // 1. remove DC (IIR)
  // 2. remove unwanted sideband (LPF/HPF at FS/4)
  // 3. downconvert to baseband (mix with BFO at FS/4)
  // 4. bandpass filter (600 - 800)

  // BFO oscillates
  volatile static uint8_t bfo = 0;
  const uint8_t phase = bfo & 0x03;
  bfo++;

  // remove DC
  int16_t v = dc(s);

  // remove the unwanted sideband
  v = mode_CWL?lpf_fs4(v):hpf_fs4(v);

  // down convert from FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t m = 0;
  switch (phase)
  {
    case 0: m = +v; break;
    case 2: m = -v; break;
  }

  // recover 6dB loss and 600 - 800 BPF
  v = bpf_600_800(m<<1);

  // extra gain for CW
  v <<= 1;

  // AGC will fix it
  if (higain) v <<= 1;
  v = agc(v,higain);
  return v;
}

static const int16_t __not_in_flash_func(process_lu_cw)(const int16_t s,const bool mode_LCW,const bool higain)
{
  // demodulate a CW signal at FS/4 (7812 Hz)
  // 1. remove DC (IIR) - //// needed?
  // 2. narrow bandpass at FS/4
  // 3. downconvert to baseband (mix with BFO at FS/4 +/- sidetone)
  // 4. lowpass at FS/4 remove mixing image

  // set up DDS BFO
  volatile static uint32_t dds = 0;
  static const uint32_t sidetone = CW_SIDETONE;
  static const uint32_t LCW_BFO = ((uint64_t)(SAMPLERATE/4u - sidetone) * (1ull << 32)) / SAMPLERATE;
  static const uint32_t UCW_BFO = ((uint64_t)(SAMPLERATE/4u + sidetone) * (1ull << 32)) / SAMPLERATE;

  // remove DC
  //int16_t v = dc(s);

  // narrow bandpass (also removes DC)
  const int32_t m = (int32_t)bpf_fs4_cw(s);

  // mix with BFO
  const int32_t bfo = (int32_t)sin_tab[dds>>22];
  int16_t v = (int16_t)((m * bfo)>>15);

  // recover 6dB loss and remove image after mixing
  v = lpf_fs4_cw(v<<1);

  // extra gain for CW
  v <<= 1;
  
  // AGC will fix it
  if (higain) v <<= 1;
  v = agc(v,higain);

  // update DDS
  dds += mode_LCW?LCW_BFO:UCW_BFO;
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
  int16_t v = hpf_fs8(s);

  // remove the unwanted sideband
  v = mode_LSB?lpf_fs4(v):hpf_fs4(v);

  // down convert from FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t m = 0;
  switch (phase)
  {
    case 0: m = +v; break;
    case 2: m = -v; break;
  }

  // 300Hz - 2400Hz BPF
  v = bpf_300_2400(m);

  if (higain) v <<= 1;
  v = agc(v,higain);
  return v;
}

#endif