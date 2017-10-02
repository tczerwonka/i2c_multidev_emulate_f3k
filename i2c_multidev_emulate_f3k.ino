#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(78);                // join i2c bus with address #8
  //Wire.begin(0x4E | 0x4C | 0x5C | 0x5A | 0xA0 );       
  Wire.onRequest(requestEvent2);  // register callback function
  //TWAMR = (0x4E | 0x4C | 0x5C | 0x5A ) << 1;    // set filter for given adr
  Serial.println("i2c_multidev_emulate_f3k");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}



void requestEvent() {
  Serial.println("re");
  //int adr = TWDR >> 1;  // move 1 bit to align I2C adr
  int adr = TWDR;  
  
  Serial.println(adr, HEX);
  
  //PAError reading PA100 IC16 in (I2C 0x4E).  Val read was: 0.  (Should have been 0xAB) Error: 0
  if (adr == 0x4E) {     // check for request from 0x4E
    Wire.write(0xAB); // send buffer
  }
  //Error reading PA100 IC13 in (I2C 0x4C).  Val read was: 0.  (Should have been 0xAB) Error: 0
  if (adr == 0x4C) {   
    Wire.write(0xAB); 
  }
  //Error reading PA100 IC3 (I2C 0x5C).  Val read was: 0.  (Should have been: 0xAB) Error: 0
  if (adr == 0x5C) {      
    Wire.write(0xAB); 
  }
  //Error reading PA100 IC4 (I2C 0x5A).  Val read was: 0.  (Should have been: 0xAB) Error: 0
  if (adr == 0x5A) {    
    Wire.write(0xAB); 
  }
  //TRX IC24 -- I2C 0xA0
  //Initializing Hardware.TRX.Error reading TRX IC24 (I2C 0xA0).  Val: 0 Error: 0
  if (adr == 0xA0) {    
    Wire.write(0xFE); 
  }
}




void requestEvent2() {
  Serial.println("re2");
  //int adr = TWDR >> 1;  // move 1 bit to align I2C adr
  int adr = TWDR;  
  Serial.println(adr, HEX);
  Wire.write(0xAB); 

}
