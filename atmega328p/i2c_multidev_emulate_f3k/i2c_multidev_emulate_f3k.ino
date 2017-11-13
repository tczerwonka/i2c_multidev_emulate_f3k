#include <Wire.h>

void setup() {
  Serial.begin(115200);              
  Wire.begin(0x27 | 0x26 | 0x2E | 0x2D);       
  Wire.onRequest(requestEvent);  // register callback function
  TWAMR = ( 0x27 | 0x26 | 0x2E | 0x2D  ) << 1;    // set filter for given adr

  Serial.println("i2c_multidev_emulate_f3k");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}



void requestEvent() {
  //Serial.println("re");
  int adr = TWDR >> 1;  // move 1 bit to align I2C adr 

  Serial.println(adr, HEX);

  //PAError reading PA100 IC16 in (I2C 0x4E).  Val read was: 0.  (Should have been 0xAB) Error: 0
  if (adr == 0x27) {     // check for request from 0x4E
    Wire.write(0xAB); // send buffer
    Serial.println("PA100-IC16");
  }
  //PAError reading PA100 IC13 in (I2C 0x4C).  Val read was: 0.  (Should have been 0xAB) Error: 0
  if (adr == 0x26) {     // check for request from 0x4E
    Wire.write(0xAB); // send buffer
    Serial.println("PA100-IC13");
  }
  //Error reading PA100 IC3 (I2C 0x5C).  Val read was: 0.  (Should have been: 0xAB) Error: 0
  if (adr == 0x2E) {      
    Wire.write(0xAB); 
    Serial.println("PA100-IC3");
  }
  //Error reading PA100 IC4 (I2C 0x5A).  Val read was: 0.  (Should have been: 0xAB) Error: 0
  if (adr == 0x2D) {    
    Wire.write(0xAB); 
    Serial.println("PA100-IC4");
  }



  if (adr == 0x20) {    
    Wire.write(0xAB); 
    Serial.println("20?");
  }
  if (adr == 0x22) {    
    Wire.write(0xAB); 
    Serial.println("22?");
  }
  if (adr == 0x2c) {    
    Wire.write(0xAB); 
    Serial.println("2c?");
  }

}


