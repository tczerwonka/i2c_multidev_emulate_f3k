#include <Wire.h>

void setup() {
    Wire.begin(0x11 | 0x12);       // Adr 11 and 12 are used for Alt and Speed by Spectrum DX
    Wire.onRequest(requestEvent);  // register callback function
    TWAMR = (0x11 | 0x12) << 1;    // set filter for given adr
}

void loop() {
  // put your main code here, to run repeatedly:

}

void requestEvent() {
    int adr = TWDR >> 1;  // move 1 bit to align I2C adr
    if (adr == 0x12)      // check for altitude request at adr 12
        Wire.write(16); // send buffer
    if (adr == 0x11)      // check for speed request at adr 11
        Wire.write(16); // send buffer
}
