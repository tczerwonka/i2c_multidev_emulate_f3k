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



/*
 * startup
IC16: 0x06 00 
IC16: 0x02 AB 
IC16: 0x02 AB 
IC13 0x27 received: 0x02 AB 00 00 00 00 00 00  sent 0xAB
IC16: 0x06 00 
IC16: 0x07 00 
IC16: 0x02 00 
IC13 OUTPUT0 Unknown received: 0x02 AB 
IC13 OUTPUT0 Unknown received: 0x02 AB 
asdf
IC13 0x26 received: 0x02 AB 00 00 00 00 00 00  sent 0xAB
IC13 OUTPUT0 Unknown received: 0x02 00 
Unknown received IC3: 0x00 AB 
IC13 0x2E received: 0x00 AB 00 00 00 00 00 00  sent 0xAB
Unknown received IC3: 0x00 00 
Unknown received IC3: 0x20 FF 
Unknown received IC3: 0x40 00 
Unknown received IC3: 0x60 FF 
bias off
DIGOUT2
IC13 0x2D received: 0x00 AB 00 00 00 00 00 00  sent 0xAB
bias off
DIGOUT2
A0RDAC
A1RDAC
IC4 Unknown received: 0x60 FF 
*/


#include <i2c_t3.h>
#include "device_def.h"

// Function prototypes
void receiveEvent(size_t len);
void requestEvent(void);
void decode_ic16(void);
void decode_ic13(void);
void decode_ic3(void);
void decode_ic4(void);

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
  //Wire1.begin(I2C_SLAVE, 0x2D, 0x2E, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);
  Wire1.begin(I2C_SLAVE, 0x2D, 0x49, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);


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
  if (received) {
    digitalWrite(LED_BUILTIN, HIGH);

    switch (target) {
      case IC16:
        decode_ic16();
        break;

      case IC13:
        decode_ic13();
        break;

      case IC3:
        decode_ic3();
        break;

      case IC4:
        decode_ic4();
        break;

      case IC11:
        decode_ic11();
        break;

      default:
        Serial.printf("Unknown 0x%02X received: ", target);
        PrintHex8((uint8_t*)databuf, 3);
        Serial.printf("\n");
        break;
    }

    received = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
}



//https://forum.arduino.cc/index.php?topic=38107.0
void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
  Serial.print("0x");
  for (int i = 0; i < length; i++) {
    if (data[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
}

void adcval(uint8_t *data) // prints 8-bit data in hex with leading zeroes
{
    Serial.print(data[1], HEX);
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









