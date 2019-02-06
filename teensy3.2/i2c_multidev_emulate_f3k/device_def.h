//on NTRX:
//0x2e is IC3 -- AD5263 -- final bias -- address 2 on schematic
//0x2d is IC4 -- AD5263 -- driver bias -- address 1 on schematic
//0x26 is IC13 PCA9555 on sheet 3 -- LPF and atu/attn/fan/tx -- address 6 on schematic
//0x27 is IC16 PCA9555 on sheet 6 -- tuner, output 0 is L, output 1 is C -- address 7 on schematic
//0x49 is IC11 ADS8728 on sheet 3 -- 8ch ADC - 610uV/bit
//caution -- is there an 0x48?

// not NTRX:
// TRX IC24 I2C 0xA0


// device_def.h
// header file for information about the four chips to emulate
//
// 20 jan 2019 T. Czerwonka
//

#ifndef device_def_h
  #define device_dev_h

  #define IC16  0x27
  #define IC13  0x26
  #define IC3   0x2e
  #define IC4   0x2d
  #define IC11  0x49

  #define CLEAR 0

  //PCA9555 outputs
  #define OUTPUT0 2
  #define LPF0  1
  #define LPF1  2
  #define LPF2  4
  #define LPF3  8
  #define LPF4  16
  #define LPF5  32
  #define LPF6  64
  #define LOWZ  128
  
  #define OUTPUT1 3
  #define ATU     1
  #define ATTN    2
  #define FANON   4
  #define FANONATU  5


  //AS5263
  //instruction
  #define DIGOUT2   2
  #define DIGOUT1   4
  #define SHUTDN    8
  #define RESETWPR  16
  #define A0RDAC    32
  #define A1RDAC    64
  


  //data
  


#endif
