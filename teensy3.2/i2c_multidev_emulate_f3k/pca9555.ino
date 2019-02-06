////////////////////////////////////////////////////////////////////////////
//pca9555.ino
//
//Remote 16-Bit I2C And SMBus I/O Expander
//
//0x26 is IC13 PCA9555 on sheet 3 -- LPF and atu/attn/fan/tx -- address 6 on schematic
//0x27 is IC16 PCA9555 on sheet 6 -- tuner, output 0 is L, output 1 is C -- address 7 on schematic
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//0x27
//PCA9555
//tuner control
//cmd 0x02 -- output 0 -- all L
//cmd 0x03 -- output 1 -- all C
////////////////////////////////////////////////////////////////////////////
void decode_ic16() {
  Serial.printf("IC16: ");
  PrintHex8((uint8_t*)databuf, 2);
  Serial.printf("\n");
}



////////////////////////////////////////////////////////////////////////////
//0x26
//PCA9555
//LPF control and housekeeping
//cmd 0x02 -- output 0 -- LPF filters
//cmd 0x03 -- output 1 -- housekeeping stuff -- ATU in out, etc.
////////////////////////////////////////////////////////////////////////////
void decode_ic13() {
  if (databuf[0] == OUTPUT0) {
    switch (databuf[1]) {
      case LPF0:
        Serial.printf("LPF0 - 6M\n");
        break;
      case LPF1:
        Serial.printf("LPF1 - 160M\n");
        break;
      case LPF2:
        Serial.printf("LPF2 - 10/12M\n");
        break;
      case LPF3:
        Serial.printf("LPF3 - 60/40M\n");
        break;
      case LPF4:
        Serial.printf("LPF4 - 30/20M\n");
        break;
      case LPF5:        
        Serial.printf("LPF5 - 17/15M\n");
        break;
      case LPF6:
        Serial.printf("LPF6 - 80M\n");
        break;
      case LOWZ:
        Serial.printf("LOWZ\n");
        break;    
      default:
        Serial.printf("IC13 OUTPUT0 Unknown received: ");
        PrintHex8((uint8_t*)databuf, 2);
        Serial.printf("\n");
        break;
    } //switch
  } // if OUTPUT1
  
  if (databuf[0] == OUTPUT1) {
    switch (databuf[1]) {
      case CLEAR:
        //Serial.printf("clear\n");
        break;
      case ATU:
        //Serial.printf("ATU\n");
        break;
      case ATTN:
        Serial.printf("ATTN\n");
        break;
      case FANON:
        //Serial.printf("FANON\n");
        break;
      case FANONATU:
        Serial.printf("fan on, ATU high\n");
        break;
      default:
        Serial.printf("IC13 OUTPUT1 Unknown received: ");
        PrintHex8((uint8_t*)databuf, 2);
        Serial.printf("\n");
        break;
    } //switch
  } // if OUTPUT1
  //Serial.printf("OUTPUT0 ");
  //PrintHex8((uint8_t*)databuf, 2);
  //Serial.printf("\n");
}



////////////////////////////////////////////////////////////////////////////
// IC16
//    send data
////////////////////////////////////////////////////////////////////////////
void emu_ic16() {
  Wire.write(0xAB); // send buffer
  Serial.printf("IC13 0x%02X received: ", target);
  PrintHex8((uint8_t*)databuf, 8);
  Serial.printf(" sent 0xAB\n");
}



////////////////////////////////////////////////////////////////////////////
// IC13
//    send data
////////////////////////////////////////////////////////////////////////////
void emu_ic13() {
  Wire.write(0xAB); // send buffer
  Serial.printf("IC13 0x%02X received: ", target);
  PrintHex8((uint8_t*)databuf, 8);
  Serial.printf(" sent 0xAB\n");
}

