A stable version with minimal features and options.

Build:
 *  CPU Speed: 225Mhz
 *  Optimize: -O2
 *  USB Stack: No USB
 *  Flash Size: 4MB (Sketch: 4032KB, FS: 64KB)

Some history
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
 *  1.5.225 move IRQ to SRAM fixes DSP issues
