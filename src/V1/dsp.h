#ifndef DSP_H
#define DSP_H

#include "util.h"

#define MOVING_AVERAGE_LENGTH 16u
#define JNR_FILTER_LENGTH 8u
#define FIR_LENGTH 256
#define __mac_tap(_h) acc += (_h)*x[i++]
#define __mac_zap(_h) i++

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
  __mac_zap(0.0f);
  __mac_tap(0.000127f);
  __mac_zap(0.0f);
  __mac_tap(-0.000154f);
  __mac_zap(0.0f);
  __mac_tap(0.000179f);
  __mac_zap(0.0f);
  __mac_tap(-0.000199f);
  __mac_zap(0.0f);
  __mac_tap(0.000212f);
  __mac_zap(0.0f);
  __mac_tap(-0.000217f);
  __mac_zap(0.0f);
  __mac_tap(0.000209f);
  __mac_zap(0.0f);
  __mac_tap(-0.000187f);
  __mac_zap(0.0f);
  __mac_tap(0.000146f);
  __mac_zap(0.0f);
  __mac_tap(-0.000083f);
  __mac_zap(0.0f);
  __mac_tap(-0.000006f);
  __mac_zap(0.0f);
  __mac_tap(0.000124f);
  __mac_zap(0.0f);
  __mac_tap(-0.000276f);
  __mac_zap(0.0f);
  __mac_tap(0.000465f);
  __mac_zap(0.0f);
  __mac_tap(-0.000694f);
  __mac_zap(0.0f);
  __mac_tap(0.000968f);
  __mac_zap(0.0f);
  __mac_tap(-0.00129f);
  __mac_zap(0.0f);
  __mac_tap(0.001662f);
  __mac_zap(0.0f);
  __mac_tap(-0.002088f);
  __mac_zap(0.0f);
  __mac_tap(0.002569f);
  __mac_zap(0.0f);
  __mac_tap(-0.003106f);
  __mac_zap(0.0f);
  __mac_tap(0.003701f);
  __mac_zap(0.0f);
  __mac_tap(-0.004354f);
  __mac_zap(0.0f);
  __mac_tap(0.005064f);
  __mac_zap(0.0f);
  __mac_tap(-0.00583f);
  __mac_zap(0.0f);
  __mac_tap(0.00665f);
  __mac_zap(0.0f);
  __mac_tap(-0.007519f);
  __mac_zap(0.0f);
  __mac_tap(0.008436f);
  __mac_zap(0.0f);
  __mac_tap(-0.009394f);
  __mac_zap(0.0f);
  __mac_tap(0.010389f);
  __mac_zap(0.0f);
  __mac_tap(-0.011415f);
  __mac_zap(0.0f);
  __mac_tap(0.012463f);
  __mac_zap(0.0f);
  __mac_tap(-0.013527f);
  __mac_zap(0.0f);
  __mac_tap(0.014598f);
  __mac_zap(0.0f);
  __mac_tap(-0.015668f);
  __mac_zap(0.0f);
  __mac_tap(0.016728f);
  __mac_zap(0.0f);
  __mac_tap(-0.017768f);
  __mac_zap(0.0f);
  __mac_tap(0.018779f);
  __mac_zap(0.0f);
  __mac_tap(-0.019751f);
  __mac_zap(0.0f);
  __mac_tap(0.020676f);
  __mac_zap(0.0f);
  __mac_tap(-0.021544f);
  __mac_zap(0.0f);
  __mac_tap(0.022347f);
  __mac_zap(0.0f);
  __mac_tap(-0.023076f);
  __mac_zap(0.0f);
  __mac_tap(0.023725f);
  __mac_zap(0.0f);
  __mac_tap(-0.024285f);
  __mac_zap(0.0f);
  __mac_tap(0.024752f);
  __mac_zap(0.0f);
  __mac_tap(-0.025121f);
  __mac_zap(0.0f);
  __mac_tap(0.025387f);
  __mac_zap(0.0f);
  __mac_tap(-0.025548f);
  __mac_zap(0.0f);
  __mac_tap(0.025602f);
  __mac_zap(0.0f);
  __mac_tap(-0.025548f);
  __mac_zap(0.0f);
  __mac_tap(0.025387f);
  __mac_zap(0.0f);
  __mac_tap(-0.025121f);
  __mac_zap(0.0f);
  __mac_tap(0.024752f);
  __mac_zap(0.0f);
  __mac_tap(-0.024285f);
  __mac_zap(0.0f);
  __mac_tap(0.023725f);
  __mac_zap(0.0f);
  __mac_tap(-0.023076f);
  __mac_zap(0.0f);
  __mac_tap(0.022347f);
  __mac_zap(0.0f);
  __mac_tap(-0.021544f);
  __mac_zap(0.0f);
  __mac_tap(0.020676f);
  __mac_zap(0.0f);
  __mac_tap(-0.019751f);
  __mac_zap(0.0f);
  __mac_tap(0.018779f);
  __mac_zap(0.0f);
  __mac_tap(-0.017768f);
  __mac_zap(0.0f);
  __mac_tap(0.016728f);
  __mac_zap(0.0f);
  __mac_tap(-0.015668f);
  __mac_zap(0.0f);
  __mac_tap(0.014598f);
  __mac_zap(0.0f);
  __mac_tap(-0.013527f);
  __mac_zap(0.0f);
  __mac_tap(0.012463f);
  __mac_zap(0.0f);
  __mac_tap(-0.011415f);
  __mac_zap(0.0f);
  __mac_tap(0.010389f);
  __mac_zap(0.0f);
  __mac_tap(-0.009394f);
  __mac_zap(0.0f);
  __mac_tap(0.008436f);
  __mac_zap(0.0f);
  __mac_tap(-0.007519f);
  __mac_zap(0.0f);
  __mac_tap(0.00665f);
  __mac_zap(0.0f);
  __mac_tap(-0.00583f);
  __mac_zap(0.0f);
  __mac_tap(0.005064f);
  __mac_zap(0.0f);
  __mac_tap(-0.004354f);
  __mac_zap(0.0f);
  __mac_tap(0.003701f);
  __mac_zap(0.0f);
  __mac_tap(-0.003106f);
  __mac_zap(0.0f);
  __mac_tap(0.002569f);
  __mac_zap(0.0f);
  __mac_tap(-0.002088f);
  __mac_zap(0.0f);
  __mac_tap(0.001662f);
  __mac_zap(0.0f);
  __mac_tap(-0.00129f);
  __mac_zap(0.0f);
  __mac_tap(0.000968f);
  __mac_zap(0.0f);
  __mac_tap(-0.000694f);
  __mac_zap(0.0f);
  __mac_tap(0.000465f);
  __mac_zap(0.0f);
  __mac_tap(-0.000276f);
  __mac_zap(0.0f);
  __mac_tap(0.000124f);
  __mac_zap(0.0f);
  __mac_tap(-0.000006f);
  __mac_zap(0.0f);
  __mac_tap(-0.000083f);
  __mac_zap(0.0f);
  __mac_tap(0.000146f);
  __mac_zap(0.0f);
  __mac_tap(-0.000187f);
  __mac_zap(0.0f);
  __mac_tap(0.000209f);
  __mac_zap(0.0f);
  __mac_tap(-0.000217f);
  __mac_zap(0.0f);
  __mac_tap(0.000212f);
  __mac_zap(0.0f);
  __mac_tap(-0.000199f);
  __mac_zap(0.0f);
  __mac_tap(0.000179f);
  __mac_zap(0.0f);
  __mac_tap(-0.000154f);
  __mac_zap(0.0f);
  __mac_tap(0.000127f);
  __mac_zap(0.0f);
  __mac_tap(-0.0001f);
  return (int16_t)(acc * 32768.0f);
}

static const int16_t __not_in_flash_func(bpf_500_1500_cw)(const int16_t sample)
{
  // 31250, 201 taps, 50db
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-2);
  __mac_tap(-3);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-2);
  __mac_tap(-1);
  __mac_tap(2);
  __mac_tap(4);
  __mac_tap(6);
  __mac_tap(8);
  __mac_tap(8);
  __mac_tap(7);
  __mac_tap(5);
  __mac_tap(0);
  __mac_tap(-6);
  __mac_tap(-14);
  __mac_tap(-23);
  __mac_tap(-33);
  __mac_tap(-43);
  __mac_tap(-52);
  __mac_tap(-59);
  __mac_tap(-64);
  __mac_tap(-65);
  __mac_tap(-63);
  __mac_tap(-58);
  __mac_tap(-49);
  __mac_tap(-38);
  __mac_tap(-24);
  __mac_tap(-10);
  __mac_tap(4);
  __mac_tap(16);
  __mac_tap(26);
  __mac_tap(31);
  __mac_tap(31);
  __mac_tap(27);
  __mac_tap(19);
  __mac_tap(7);
  __mac_tap(-7);
  __mac_tap(-22);
  __mac_tap(-35);
  __mac_tap(-44);
  __mac_tap(-47);
  __mac_tap(-43);
  __mac_tap(-30);
  __mac_tap(-9);
  __mac_tap(21);
  __mac_tap(59);
  __mac_tap(101);
  __mac_tap(146);
  __mac_tap(189);
  __mac_tap(228);
  __mac_tap(259);
  __mac_tap(279);
  __mac_tap(285);
  __mac_tap(277);
  __mac_tap(254);
  __mac_tap(217);
  __mac_tap(169);
  __mac_tap(113);
  __mac_tap(54);
  __mac_tap(-3);
  __mac_tap(-54);
  __mac_tap(-94);
  __mac_tap(-118);
  __mac_tap(-124);
  __mac_tap(-112);
  __mac_tap(-83);
  __mac_tap(-39);
  __mac_tap(14);
  __mac_tap(70);
  __mac_tap(122);
  __mac_tap(162);
  __mac_tap(181);
  __mac_tap(174);
  __mac_tap(134);
  __mac_tap(58);
  __mac_tap(-53);
  __mac_tap(-196);
  __mac_tap(-367);
  __mac_tap(-555);
  __mac_tap(-749);
  __mac_tap(-937);
  __mac_tap(-1103);
  __mac_tap(-1234);
  __mac_tap(-1316);
  __mac_tap(-1339);
  __mac_tap(-1294);
  __mac_tap(-1177);
  __mac_tap(-989);
  __mac_tap(-735);
  __mac_tap(-424);
  __mac_tap(-70);
  __mac_tap(311);
  __mac_tap(698);
  __mac_tap(1072);
  __mac_tap(1411);
  __mac_tap(1698);
  __mac_tap(1915);
  __mac_tap(2051);
  __mac_tap(2097);
  __mac_tap(2051);
  __mac_tap(1915);
  __mac_tap(1698);
  __mac_tap(1411);
  __mac_tap(1072);
  __mac_tap(698);
  __mac_tap(311);
  __mac_tap(-70);
  __mac_tap(-424);
  __mac_tap(-735);
  __mac_tap(-989);
  __mac_tap(-1177);
  __mac_tap(-1294);
  __mac_tap(-1339);
  __mac_tap(-1316);
  __mac_tap(-1234);
  __mac_tap(-1103);
  __mac_tap(-937);
  __mac_tap(-749);
  __mac_tap(-555);
  __mac_tap(-367);
  __mac_tap(-196);
  __mac_tap(-53);
  __mac_tap(58);
  __mac_tap(134);
  __mac_tap(174);
  __mac_tap(181);
  __mac_tap(162);
  __mac_tap(122);
  __mac_tap(70);
  __mac_tap(14);
  __mac_tap(-39);
  __mac_tap(-83);
  __mac_tap(-112);
  __mac_tap(-124);
  __mac_tap(-118);
  __mac_tap(-94);
  __mac_tap(-54);
  __mac_tap(-3);
  __mac_tap(54);
  __mac_tap(113);
  __mac_tap(169);
  __mac_tap(217);
  __mac_tap(254);
  __mac_tap(277);
  __mac_tap(285);
  __mac_tap(279);
  __mac_tap(259);
  __mac_tap(228);
  __mac_tap(189);
  __mac_tap(146);
  __mac_tap(101);
  __mac_tap(59);
  __mac_tap(21);
  __mac_tap(-9);
  __mac_tap(-30);
  __mac_tap(-43);
  __mac_tap(-47);
  __mac_tap(-44);
  __mac_tap(-35);
  __mac_tap(-22);
  __mac_tap(-7);
  __mac_tap(7);
  __mac_tap(19);
  __mac_tap(27);
  __mac_tap(31);
  __mac_tap(31);
  __mac_tap(26);
  __mac_tap(16);
  __mac_tap(4);
  __mac_tap(-10);
  __mac_tap(-24);
  __mac_tap(-38);
  __mac_tap(-49);
  __mac_tap(-58);
  __mac_tap(-63);
  __mac_tap(-65);
  __mac_tap(-64);
  __mac_tap(-59);
  __mac_tap(-52);
  __mac_tap(-43);
  __mac_tap(-33);
  __mac_tap(-23);
  __mac_tap(-14);
  __mac_tap(-6);
  __mac_tap(0);
  __mac_tap(5);
  __mac_tap(7);
  __mac_tap(8);
  __mac_tap(8);
  __mac_tap(6);
  __mac_tap(4);
  __mac_tap(2);
  __mac_tap(-1);
  __mac_tap(-2);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-3);
  __mac_tap(-2);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(bpf_fs4_am)(const int16_t sample)
{
  // 31248, 60dB, 6KHz @ FS/4, 201 taps
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(8);
  __mac_tap(0);
  __mac_tap(-2);
  __mac_tap(0);
  __mac_tap(-11);
  __mac_tap(0);
  __mac_tap(12);
  __mac_tap(0);
  __mac_tap(6);
  __mac_tap(0);
  __mac_tap(-22);
  __mac_tap(0);
  __mac_tap(10);
  __mac_tap(0);
  __mac_tap(22);
  __mac_tap(0);
  __mac_tap(-32);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(46);
  __mac_tap(0);
  __mac_tap(-33);
  __mac_tap(0);
  __mac_tap(-33);
  __mac_tap(0);
  __mac_tap(70);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(-77);
  __mac_tap(0);
  __mac_tap(80);
  __mac_tap(0);
  __mac_tap(33);
  __mac_tap(0);
  __mac_tap(-126);
  __mac_tap(0);
  __mac_tap(59);
  __mac_tap(0);
  __mac_tap(109);
  __mac_tap(0);
  __mac_tap(-158);
  __mac_tap(0);
  __mac_tap(-9);
  __mac_tap(0);
  __mac_tap(201);
  __mac_tap(0);
  __mac_tap(-146);
  __mac_tap(0);
  __mac_tap(-129);
  __mac_tap(0);
  __mac_tap(278);
  __mac_tap(0);
  __mac_tap(-62);
  __mac_tap(0);
  __mac_tap(-287);
  __mac_tap(0);
  __mac_tap(300);
  __mac_tap(0);
  __mac_tap(112);
  __mac_tap(0);
  __mac_tap(-451);
  __mac_tap(0);
  __mac_tap(218);
  __mac_tap(0);
  __mac_tap(376);
  __mac_tap(0);
  __mac_tap(-562);
  __mac_tap(0);
  __mac_tap(-16);
  __mac_tap(0);
  __mac_tap(706);
  __mac_tap(0);
  __mac_tap(-542);
  __mac_tap(0);
  __mac_tap(-452);
  __mac_tap(0);
  __mac_tap(1056);
  __mac_tap(0);
  __mac_tap(-274);
  __mac_tap(0);
  __mac_tap(-1176);
  __mac_tap(0);
  __mac_tap(1368);
  __mac_tap(0);
  __mac_tap(505);
  __mac_tap(0);
  __mac_tap(-2549);
  __mac_tap(0);
  __mac_tap(1584);
  __mac_tap(0);
  __mac_tap(3459);
  __mac_tap(0);
  __mac_tap(-9736);
  __mac_tap(0);
  __mac_tap(12584);
  __mac_tap(0);
  __mac_tap(-9736);
  __mac_tap(0);
  __mac_tap(3459);
  __mac_tap(0);
  __mac_tap(1584);
  __mac_tap(0);
  __mac_tap(-2549);
  __mac_tap(0);
  __mac_tap(505);
  __mac_tap(0);
  __mac_tap(1368);
  __mac_tap(0);
  __mac_tap(-1176);
  __mac_tap(0);
  __mac_tap(-274);
  __mac_tap(0);
  __mac_tap(1056);
  __mac_tap(0);
  __mac_tap(-452);
  __mac_tap(0);
  __mac_tap(-542);
  __mac_tap(0);
  __mac_tap(706);
  __mac_tap(0);
  __mac_tap(-16);
  __mac_tap(0);
  __mac_tap(-562);
  __mac_tap(0);
  __mac_tap(376);
  __mac_tap(0);
  __mac_tap(218);
  __mac_tap(0);
  __mac_tap(-451);
  __mac_tap(0);
  __mac_tap(112);
  __mac_tap(0);
  __mac_tap(300);
  __mac_tap(0);
  __mac_tap(-287);
  __mac_tap(0);
  __mac_tap(-62);
  __mac_tap(0);
  __mac_tap(278);
  __mac_tap(0);
  __mac_tap(-129);
  __mac_tap(0);
  __mac_tap(-146);
  __mac_tap(0);
  __mac_tap(201);
  __mac_tap(0);
  __mac_tap(-9);
  __mac_tap(0);
  __mac_tap(-158);
  __mac_tap(0);
  __mac_tap(109);
  __mac_tap(0);
  __mac_tap(59);
  __mac_tap(0);
  __mac_tap(-126);
  __mac_tap(0);
  __mac_tap(33);
  __mac_tap(0);
  __mac_tap(80);
  __mac_tap(0);
  __mac_tap(-77);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(70);
  __mac_tap(0);
  __mac_tap(-33);
  __mac_tap(0);
  __mac_tap(-33);
  __mac_tap(0);
  __mac_tap(46);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(-32);
  __mac_tap(0);
  __mac_tap(22);
  __mac_tap(0);
  __mac_tap(10);
  __mac_tap(0);
  __mac_tap(-22);
  __mac_tap(0);
  __mac_tap(6);
  __mac_tap(0);
  __mac_tap(12);
  __mac_tap(0);
  __mac_tap(-11);
  __mac_tap(0);
  __mac_tap(-2);
  __mac_tap(0);
  __mac_tap(8);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(-3);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_fs8_rx)(const int16_t sample)
{
  // nominal 31250 sample rate
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(2);
  __mac_tap(3);
  __mac_tap(2);
  __mac_tap(0);
  __mac_tap(-3);
  __mac_tap(-5);
  __mac_tap(-4);
  __mac_tap(0);
  __mac_tap(5);
  __mac_tap(8);
  __mac_tap(6);
  __mac_tap(0);
  __mac_tap(-7);
  __mac_tap(-11);
  __mac_tap(-8);
  __mac_tap(0);
  __mac_tap(10);
  __mac_tap(15);
  __mac_tap(12);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(-21);
  __mac_tap(-16);
  __mac_tap(0);
  __mac_tap(18);
  __mac_tap(27);
  __mac_tap(21);
  __mac_tap(0);
  __mac_tap(-24);
  __mac_tap(-35);
  __mac_tap(-27);
  __mac_tap(0);
  __mac_tap(30);
  __mac_tap(45);
  __mac_tap(34);
  __mac_tap(0);
  __mac_tap(-38);
  __mac_tap(-57);
  __mac_tap(-42);
  __mac_tap(0);
  __mac_tap(47);
  __mac_tap(70);
  __mac_tap(52);
  __mac_tap(0);
  __mac_tap(-58);
  __mac_tap(-86);
  __mac_tap(-64);
  __mac_tap(0);
  __mac_tap(71);
  __mac_tap(106);
  __mac_tap(78);
  __mac_tap(0);
  __mac_tap(-86);
  __mac_tap(-128);
  __mac_tap(-95);
  __mac_tap(0);
  __mac_tap(105);
  __mac_tap(155);
  __mac_tap(115);
  __mac_tap(0);
  __mac_tap(-126);
  __mac_tap(-187);
  __mac_tap(-139);
  __mac_tap(0);
  __mac_tap(153);
  __mac_tap(226);
  __mac_tap(168);
  __mac_tap(0);
  __mac_tap(-185);
  __mac_tap(-275);
  __mac_tap(-204);
  __mac_tap(0);
  __mac_tap(226);
  __mac_tap(336);
  __mac_tap(251);
  __mac_tap(0);
  __mac_tap(-280);
  __mac_tap(-418);
  __mac_tap(-313);
  __mac_tap(0);
  __mac_tap(354);
  __mac_tap(533);
  __mac_tap(403);
  __mac_tap(0);
  __mac_tap(-464);
  __mac_tap(-708);
  __mac_tap(-543);
  __mac_tap(0);
  __mac_tap(650);
  __mac_tap(1017);
  __mac_tap(803);
  __mac_tap(0);
  __mac_tap(-1040);
  __mac_tap(-1722);
  __mac_tap(-1466);
  __mac_tap(0);
  __mac_tap(2453);
  __mac_tap(5210);
  __mac_tap(7373);
  __mac_tap(8192);
  __mac_tap(7373);
  __mac_tap(5210);
  __mac_tap(2453);
  __mac_tap(0);
  __mac_tap(-1466);
  __mac_tap(-1722);
  __mac_tap(-1040);
  __mac_tap(0);
  __mac_tap(803);
  __mac_tap(1017);
  __mac_tap(650);
  __mac_tap(0);
  __mac_tap(-543);
  __mac_tap(-708);
  __mac_tap(-464);
  __mac_tap(0);
  __mac_tap(403);
  __mac_tap(533);
  __mac_tap(354);
  __mac_tap(0);
  __mac_tap(-313);
  __mac_tap(-418);
  __mac_tap(-280);
  __mac_tap(0);
  __mac_tap(251);
  __mac_tap(336);
  __mac_tap(226);
  __mac_tap(0);
  __mac_tap(-204);
  __mac_tap(-275);
  __mac_tap(-185);
  __mac_tap(0);
  __mac_tap(168);
  __mac_tap(226);
  __mac_tap(153);
  __mac_tap(0);
  __mac_tap(-139);
  __mac_tap(-187);
  __mac_tap(-126);
  __mac_tap(0);
  __mac_tap(115);
  __mac_tap(155);
  __mac_tap(105);
  __mac_tap(0);
  __mac_tap(-95);
  __mac_tap(-128);
  __mac_tap(-86);
  __mac_tap(0);
  __mac_tap(78);
  __mac_tap(106);
  __mac_tap(71);
  __mac_tap(0);
  __mac_tap(-64);
  __mac_tap(-86);
  __mac_tap(-58);
  __mac_tap(0);
  __mac_tap(52);
  __mac_tap(70);
  __mac_tap(47);
  __mac_tap(0);
  __mac_tap(-42);
  __mac_tap(-57);
  __mac_tap(-38);
  __mac_tap(0);
  __mac_tap(34);
  __mac_tap(45);
  __mac_tap(30);
  __mac_tap(0);
  __mac_tap(-27);
  __mac_tap(-35);
  __mac_tap(-24);
  __mac_tap(0);
  __mac_tap(21);
  __mac_tap(27);
  __mac_tap(18);
  __mac_tap(0);
  __mac_tap(-16);
  __mac_tap(-21);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(12);
  __mac_tap(15);
  __mac_tap(10);
  __mac_tap(0);
  __mac_tap(-8);
  __mac_tap(-11);
  __mac_tap(-7);
  __mac_tap(0);
  __mac_tap(6);
  __mac_tap(8);
  __mac_tap(5);
  __mac_tap(0);
  __mac_tap(-4);
  __mac_tap(-5);
  __mac_tap(-3);
  __mac_tap(0);
  __mac_tap(2);
  __mac_tap(3);
  __mac_tap(2);
  __mac_tap(0);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(bpf_300_2400_rx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(bpf_300_2400_tx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(lpf_fs4_rx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(lpf_fs4_tx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(hpf_fs4_rx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(hpf_fs4_tx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(hpf_fs8_rx)(const int16_t sample)
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

static const int16_t __not_in_flash_func(maf1)(const int16_t v)
{
  static int16_t element[MOVING_AVERAGE_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (MOVING_AVERAGE_LENGTH-1);
  return sum/MOVING_AVERAGE_LENGTH;
}

static const int16_t __not_in_flash_func(maf2)(const int16_t v)
{
  static int16_t element[MOVING_AVERAGE_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (MOVING_AVERAGE_LENGTH-1);
  return sum/MOVING_AVERAGE_LENGTH;
}

static const int16_t __not_in_flash_func(maf3)(const int16_t v)
{
  static int16_t element[MOVING_AVERAGE_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (MOVING_AVERAGE_LENGTH-1);
  return sum/MOVING_AVERAGE_LENGTH;
}

static const int16_t __not_in_flash_func(maf4)(const int16_t v)
{
  static int16_t element[MOVING_AVERAGE_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (MOVING_AVERAGE_LENGTH-1);
  return sum/MOVING_AVERAGE_LENGTH;
}

static const int16_t __not_in_flash_func(ma_order_2)(const int16_t v)
{
  return maf2(maf1(v));
}

static const int16_t __not_in_flash_func(ma_order_4)(const int16_t v)
{
  return maf4(maf3(maf2(maf1(v))));
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

const int16_t __not_in_flash_func(process_ssb_tx)(const int16_t s,const bool mode_LSB)
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
  const int16_t bpf2400 = bpf_300_2400_tx(s);

  // up convert to FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t v = 0;
  switch (phase)
  {
    case 0: v = +bpf2400; break;
    case 2: v = -bpf2400; break;
  }

  // remove the unwanted sideband
  v = mode_LSB?lpf_fs4_tx(v):hpf_fs4_tx(v);

  // ALC
  v = (int16_t)(((int32_t)v * alc) >> 8);
  if (abs(v)>511) alc--;

  return v;
}

const int16_t __not_in_flash_func(process_am_tx)(const int16_t s)
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
  const int16_t bpf2400 = bpf_300_2400_tx(s>>5) + DC;

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
  const int32_t m = (int32_t)bpf_fs4_cw(s);

  // mix with BFO
  const int32_t bfo = (int32_t)sin_tab[dds>>22];
  int16_t v = (int16_t)((m * bfo)>>15);

  // recover 6dB loss and remove image after mixing
  v = bpf_500_1500_cw(v<<1);

  // extra gain for CW
  v <<= 1;

  // noise reduction
  v = ma_order_4(v<<1);
  
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
  int16_t v = hpf_fs8_rx(s);

  // remove the unwanted sideband
  v = mode_LSB?lpf_fs4_rx(v):hpf_fs4_rx(v);

  // down convert from FS/4
  // note LO signal reduces to 0, 1 and -1 at FS/4
  int16_t m = 0;
  switch (phase)
  {
    case 0: m = +v; break;
    case 2: m = -v; break;
  }

  // 300Hz - 2400Hz BPF
  v = bpf_300_2400_rx(m<<1);

  if (higain) v <<= 1;
  v = agc(v);
  return v;
}

static const int16_t __not_in_flash_func(process_am_rx)(const int16_t s,const bool higain)
{
  // demodulate an AM signal at FS/4 (7812 Hz)
  // 1. bandpass filter AM signal (6KHz)
  // 2. down-convert to baseband (mix with BFO at FS/4 - note, this reduces to ABS()!)
  // 3. get magnitude of IQ signal (AM)
  // 4. remove DC bias
  // 5. filter out carrier

  // bandpass AM signal
  int16_t v = bpf_fs4_am(s);

  // quadrature mixer and magnitude (rectify)!
  v = abs(v);

  // remove DC and filter
  v = lpf_fs8_rx(dc(v));

  // more gain on higher bands
  if (higain) v <<= 1;
  v = agc(v);
  return v;
}

static const int16_t __not_in_flash_func(jnr_maf1)(const int16_t v)
{
  static int16_t element[JNR_FILTER_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (JNR_FILTER_LENGTH-1);
  return sum/JNR_FILTER_LENGTH;
}

static const int16_t __not_in_flash_func(jnr_maf2)(const int16_t v)
{
  static int16_t element[JNR_FILTER_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (JNR_FILTER_LENGTH-1);
  return sum/JNR_FILTER_LENGTH;
}

static const int16_t __not_in_flash_func(jnr_maf3)(const int16_t v)
{
  static int16_t element[JNR_FILTER_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (JNR_FILTER_LENGTH-1);
  return sum/JNR_FILTER_LENGTH;
}

static const int16_t __not_in_flash_func(jnr_maf4)(const int16_t v)
{
  static int16_t element[JNR_FILTER_LENGTH] = {0};
  static uint8_t p = 0;
  static int32_t sum = 0;
  sum = sum - element[p] + v;
  element[p++] = v;
  p &= (JNR_FILTER_LENGTH-1);
  return sum/JNR_FILTER_LENGTH;
}

static const int16_t __not_in_flash_func(jnr)(const int16_t s,const uint32_t level)
{
  // just noise reduction (not dynamic)
  switch (level)
  {
    case 1: return jnr_maf1(s);
    case 2: return jnr_maf2(jnr_maf1(s));
    case 3: return jnr_maf4(jnr_maf3(jnr_maf2(jnr_maf1(s))));
  }
  return s;
}

#endif