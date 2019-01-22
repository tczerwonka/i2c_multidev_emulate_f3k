


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
