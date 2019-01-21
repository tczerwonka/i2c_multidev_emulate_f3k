// -------------------------------------------------------------------------------------------
// i2c_multidev_emulate_f3k
// -------------------------------------------------------------------------------------------
//
// This is the teensy 3.2 version of a multi-target i2c emulator to replace the functionality
// found on the Flex3000 PA and ATU boards.
//
// This code lives here: https://github.com/tczerwonka/i2c_multidev_emulate_f3k
// See: http://pages.cs.wisc.edu/~timc/e/f3k/ for additional details.
//
// The target will respond to a range of I2C addresses.  It demonstrates use of the getRxAddr()
// function which can be used to obtain the target address.  This allows a single device to
// act as multiple different targets.
//
// -------------------------------------------------------------------------------------------
// Notes:
// Initializing Hardware.TRX......Error reading TRX IC2 (I2C 0x58).  Val read was: 0.  (Should have been: 0xAB) Error: 0
// .PAError reading PA100 IC16 in (I2C 0x4E).  Val read was: 0.  (Should have been 0xAB) Error: 0
// .Error reading PA100 IC13 in (I2C 0x4C).  Val read was: 0.  (Should have been 0xAB) Error: 0
// .Error reading PA100 IC3 (I2C 0x5C).  Val read was: 0.  (Should have been: 0xAB) Error: 0
// .Error reading PA100 IC4 (I2C 0x5A).  Val read was: 0.  (Should have been: 0xAB) Error: 0
// ..setupPA error: 4Error detecting PA
//
// to
//
//
//  -and-
//Target 0x27 received: '1FFF99AC'
//Target 0x27 received: '1FFF99AC'
//Target 0x27 received: '1FFF99AC'
//IC16 0x27 received: '1FFF99AC'
//Target 0x27 received: '1FFF99AC'
//Target 0x27 received: '1FFF99AC'
//Target 0x27 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//IC13 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x26 received: '1FFF99AC'
//Target 0x2E received: '1FFF99AC'
//IC3 0x2E received: '1FFF99AC'
//Target 0x2E received: '1FFF99AC'
//Target 0x2E received: '1FFF99AC'
//Target 0x2E received: '1FFF99AC'
//Target 0x2E received: '1FFF99AC'
//Target 0x2D received: '1FFF99AC'
//IC4 0x2D received: '1FFF99AC'
//Target 0x2D received: '1FFF99AC'Target 0x27 received: '1FFF98A0' count: '02'
Target 0x27 received: '1FFF98A0' count: '02'
Target 0x27 received: '1FFF98A0' count: '01'
IC16 0x27 received: '1FFF98A0' sent 0xAB
Target 0x27 received: '1FFF98A0' count: '02'
Target 0x27 received: '1FFF98A0' count: '02'
Target 0x27 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '01'
asdf
IC13 0x26 received: '1FFF98A0' sent 0xAB
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x26 received: '1FFF98A0' count: '02'
Target 0x2E received: '1FFF98A0' count: '02'
IC3 0x2E received: '1FFF98A0' sent 0xAB
Target 0x2E received: '1FFF98A0' count: '02'
Target 0x2E received: '1FFF98A0' count: '02'
Target 0x2E received: '1FFF98A0' count: '02'
Target 0x2E received: '1FFF98A0' count: '02'
Target 0x2D received: '1FFF98A0' count: '02'
IC4 0x2D received: '1FFF98A0' sent 0xAB
Target 0x2D received: '1FFF98A0' count: '02'
Target 0x2D received: '1FFF98A0' count: '02'
Target 0x2D received: '1FFF98A0' count: '02'
Target 0x2D received: '1FFF98A0' count: '02'
//Target 0x2D received: '1FFF99AC'
//Target 0x2D received: '1FFF99AC'
//Target 0x2D received: '1FFF99AC'

//20jan2019
//Target 0x27 received: '1FFF98A0' count: '02'
//Target 0x27 received: '1FFF98A0' count: '02'
//Target 0x27 received: '1FFF98A0' count: '01'
//IC16 0x27 received: '1FFF98A0' sent 0xAB
//Target 0x27 received: '1FFF98A0' count: '02'
//Target 0x27 received: '1FFF98A0' count: '02'
//Target 0x27 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '01'
//asdf
//IC13 0x26 received: '1FFF98A0' sent 0xAB
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x26 received: '1FFF98A0' count: '02'
//Target 0x2E received: '1FFF98A0' count: '02'
//IC3 0x2E received: '1FFF98A0' sent 0xAB
//Target 0x2E received: '1FFF98A0' count: '02'
//Target 0x2E received: '1FFF98A0' count: '02'
//Target 0x2E received: '1FFF98A0' count: '02'
//Target 0x2E received: '1FFF98A0' count: '02'
//Target 0x2D received: '1FFF98A0' count: '02'
//IC4 0x2D received: '1FFF98A0' sent 0xAB
//Target 0x2D received: '1FFF98A0' count: '02'
//Target 0x2D received: '1FFF98A0' count: '02'
//Target 0x2D received: '1FFF98A0' count: '02'
//Target 0x2D received: '1FFF98A0' count: '02'
//following continuous during receive
//Target 0x26 received: '1FFF98A0' count: '02'




//
// 12nov2017
// Teensy code kinda works.
// issue is that when I put the teensy3.2 on the i2c bus it screws with the
// communication for the NTRX i2c devices, have external 2.7k pull-up on
// SDA and SCL...solution is to specify tightly the range for listening from
// 0x26 to 0x2E -- unfortunately 0x2C is in there...assigned wire1 to the other
// i2c pins and soldered in parallel.
//
// Problem: don't ever see a reply for Wire1, even if using separate sets of pins


#include <i2c_t3.h>
#include "device_def.h"

// Function prototypes
void receiveEvent(size_t len);
void requestEvent(void);

// address of requested device
int caller, request;

// Memory
#define MEM_LEN 256
uint8_t databuf[MEM_LEN];
volatile uint8_t target;
volatile uint8_t received;

//
// Setup
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // LED

  Wire.begin(I2C_SLAVE, 0x26, 0x27, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire1.begin(I2C_SLAVE, 0x2D, 0x2E, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);

  // Data init
  received = 0;
  target = 0;
  memset(databuf, 0, sizeof(databuf));


  // register events
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Wire1.onReceive(receiveEvent1);
  Wire1.onRequest(requestEvent1);

  Serial.begin(115200);
  Serial.printf("starting\n");
}

void loop()
{
    // print received data
    if(received) {
        digitalWrite(LED_BUILTIN,HIGH);
        Serial.printf("Target 0x%02X received: '%02X' count: '%02X'\n", target, (char*)databuf, received);
        received = 0;
        digitalWrite(LED_BUILTIN,LOW);
    }
}



//
// handle Rx Event (incoming I2C data)
//
void receiveEvent(size_t count)
{
  target = Wire.getRxAddr();  // getRxAddr() is used to obtain target address
  Wire.read(databuf, count);  // copy Rx data to databuf
  received = count;           // set received flag to count, this triggers print in main loop
}

void receiveEvent1(size_t count)
{ 
  target = Wire1.getRxAddr();  // getRxAddr() is used to obtain target address
  Wire1.read(databuf, count);  // copy Rx data to databuf
  received = count;           // set received flag to count, this triggers print in main loop
}


// IC16
//    0x27
void emu_ic16() {
  Wire.write(0xAB); // send buffer
  Serial.printf("IC16 0x%02X received: '%02X' sent 0xAB\n", target, (char*)databuf);
}

// IC13
//    0x26
void emu_ic13() {
  Wire.write(0xAB); // send buffer
  Serial.printf("IC13 0x%02X received: '%02X' sent 0xAB\n", target, (char*)databuf);
}

//IC3
//  0x2e
void emu_ic3() {
  Wire1.write(0xAB); // send buffer
  Serial.printf("IC3 0x%02X received: '%02X' sent 0xAB\n", target, (char*)databuf);
}

//IC4
//  0x2d
void emu_ic4() {
  Wire1.write(0xAB); // send buffer
  Serial.printf("IC4 0x%02X received: '%02X' sent 0xAB\n", target, (char*)databuf);
}



//
// handle Tx Event (outgoing I2C data)
//
void requestEvent(void)
{
  if (target == IC16) {
    emu_ic16();
  }
  if (target == 0x26) {
    Serial.printf("asdf\n");
    emu_ic13();
  }
}



void requestEvent1(void)
{
  if (target == IC3) {
    emu_ic3();
  }
  if (target == IC4) {
    emu_ic4();
  }
}



