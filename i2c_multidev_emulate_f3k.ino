#include <Wire.h>

void setup() {
    Wire.begin(0x4E | 0x4C | 0x5C | 0x5A );       
    Wire.onRequest(requestEvent);  // register callback function
    TWAMR = (0x4E | 0x4C | 0x5C | 0x5A ) << 1;    // set filter for given adr
}

void loop() {
  // put your main code here, to run repeatedly:

}

void requestEvent() {
    int adr = TWDR >> 1;  // move 1 bit to align I2C adr
    if (adr == 0x4E)      // check for request from 0x4E
        Wire.write(0xAB); // send buffer
    if (adr == 0x4C)      
        Wire.write(0xAB); 
    if (adr == 0x5C)      
        Wire.write(0xAB); 
    if (adr == 0x5A)      
        Wire.write(0xAB); 
        
}
