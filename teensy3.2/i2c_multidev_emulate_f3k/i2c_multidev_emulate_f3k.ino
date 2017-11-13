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
// This creates a simple I2C Slave device which will print whatever text string is sent to it.
// It will retain the text string in memory and will send it back to a Master device if 
// requested.  It is intended to pair with a Master device running the basic_master sketch.
//
// The Slave will respond to a range of I2C addresses.  It demonstrates use of the getRxAddr() 
// function which can be used to obtain the Slave address.  This allows a single device to 
// act as multiple different Slave targets.
//
// This example code is in the public domain.
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
//  -and-
// IC2 
// Slave 0x2C received: ''
// IC16 PA
// Slave 0x27 received: ''
// Slave 0x27 received: '⸮'
// Slave 0x27 received: '⸮'
// IC13 PA
// Slave 0x26 received: ''
// Slave 0x26 received: '⸮'
// Slave 0x26 received: '⸮'
// IC3 PA
// Slave 0x2E received: ''
// IC4 PA
// Slave 0x2D received: ''

//
// 12nov2017
// Teensy code kinda works.
// issue is that when I put the teensy3.2 on the i2c bus it screws with the 
// communication for the NTRX i2c devices, have external 2.7k pull-up on 
// SDA and SCL...solution is to specify tightly the range for listening from 
// 0x26 to 0x2E -- unfortunately 0x2C is in there...but looks like I can assign
// a Wire and Wire1 to the same I2C pins...awesome!



#include <i2c_t3.h>

// Function prototypes
void receiveEvent(size_t len);
void requestEvent(void);

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
    pinMode(LED_BUILTIN,OUTPUT); // LED

    // Setup for Slave mode, addresses 0x08 to 0x77, pins 18/19, external pullups, 400kHz
    Wire.begin(I2C_SLAVE, 0x26, 0x27, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire1.begin(I2C_SLAVE, 0x2D, 0x2E, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);

    // Data init
    received = 0;
    target = 0;
    memset(databuf, 0, sizeof(databuf));

    // register events
    Wire.onReceive(receiveEvent);
    Wire1.onReceive(receiveEvent1);
    //Wire.onRequest(requestEvent);

    Serial.begin(115200);
    Serial.println("starting i2c_multidev_emulate_f3k");
}

void loop()
{
    // print received data
    if(received)
    {
        digitalWrite(LED_BUILTIN,HIGH);
        Serial.printf("Slave 0x%02X received: '%s'\n", target, (char*)databuf);
        received = 0;
        digitalWrite(LED_BUILTIN,LOW);
    }
}

//
// handle Rx Event (incoming I2C data)
//
void receiveEvent(size_t count)
{
    target = Wire.getRxAddr();  // getRxAddr() is used to obtain Slave address
    Wire.read(databuf, count);  // copy Rx data to databuf
    received = count;           // set received flag to count, this triggers print in main loop
}

void receiveEvent1(size_t count)
{
    target = Wire1.getRxAddr();  // getRxAddr() is used to obtain Slave address
    Wire1.read(databuf, count);  // copy Rx data to databuf
    received = count;           // set received flag to count, this triggers print in main loop
}

//
// handle Tx Event (outgoing I2C data)
//
void requestEvent(void)
{
    Wire.write(databuf, MEM_LEN); // fill Tx buffer (send full mem)
}
