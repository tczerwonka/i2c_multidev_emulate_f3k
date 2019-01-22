////////////////////////////////////////////////////////////////////////////
//ad5263.ino
//
//0x2e is IC3 -- AD5263 -- final bias
//0x2d is IC4 -- AD5263 -- driver bias
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//IC4
//AD5263 digital potentiometer
//P5 of 6
//Driver Q3/Q2 bias?
//On MOX: Unknown received IC4:         0x04 04 00 00 00 00 00 00 
//on MOX release: Unknown received IC4: 0x00 04 00 00 00 00 00 00 
//believe that 0x04 CMD sets SDO/O1 high - tied to SHDN on both IC4 and IC3 --
//SHDN tied to ground via 2.2K, when sent high, is enable
////////////////////////////////////////////////////////////////////////////
void decode_ic4(void)
{
    switch (databuf[0]) {
      case CLEAR:
        Serial.printf("bias off\n");
      case DIGOUT2:
        Serial.printf("DIGOUT2\n");
        break;
      case DIGOUT1:
        Serial.printf("bias enable: ");
        adcval((uint8_t*)databuf);
        Serial.printf("\n");
        break;    
      case SHUTDN:
        Serial.printf("SHDN\n");
        break;
      case RESETWPR:
        Serial.printf("RESETWPR\n");
        break; 
      case A0RDAC:
        Serial.printf("A0RDAC\n");
        break;
      case A1RDAC:
        Serial.printf("A1RDAC\n");
        break;         
        
      default:
        Serial.printf("IC4 Unknown received: ");
        PrintHex8((uint8_t*)databuf, 2);
        Serial.printf("\n");
        break;
    } //switch
} //decode_ic4




////////////////////////////////////////////////////////////////////////////
//IC3
//AD5263 digital potentiometer
////////////////////////////////////////////////////////////////////////////
void decode_ic3(void)
{
  Serial.printf("Unknown received IC3: ");
  PrintHex8((uint8_t*)databuf, 2);
  Serial.printf("\n");

}



////////////////////////////////////////////////////////////////////////////
//IC3
//  0x2e
//  send data
////////////////////////////////////////////////////////////////////////////
void emu_ic3() {
  Wire1.write(0xAB); // send buffer
  Serial.printf("IC13 0x%02X received: ", target);
  PrintHex8((uint8_t*)databuf, 8);
  Serial.printf(" sent 0xAB\n");
}



////////////////////////////////////////////////////////////////////////////
//IC4
//  0x2d
//  send data
////////////////////////////////////////////////////////////////////////////
void emu_ic4() {
  Wire1.write(0xAB); // send buffer
  Serial.printf("IC13 0x%02X received: ", target);
  PrintHex8((uint8_t*)databuf, 8);
  Serial.printf(" sent 0xAB\n");
}

