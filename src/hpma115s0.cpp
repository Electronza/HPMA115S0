// HPMA115S0 dust sensor PM2.5 and PM10
// ---------------------
//
// By T.Costachioiu (blog@electronza.com)
// March 2019
//
// Documentation:
// Honeywell HPMA115S0 datasheet
// https://sensing.honeywell.com/HPMA115S0-particulate-matter-sensors

#include "hpma115s0.h"

HPMA115S0::HPMA115S0(Stream& serial):
hpmport(serial) {}

bool HPMA115S0::start_measurement (void)
{
  // First, we send the command
  byte start_measurement[] = {0x68, 0x01, 0x01, 0x96 };
  hpmport.write(start_measurement, sizeof(start_measurement));
  //Then we wait for the response
  while(hpmport.available() < 2);
  byte read1 = hpmport.read();
  byte read2 = hpmport.read();
  // Test the response
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    // ACK
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    // NACK
    return 0;
  }
  else return 0;
}
 
bool HPMA115S0::stop_measurement(void)
{
  // First, we send the command
  byte stop_measurement[] = {0x68, 0x01, 0x02, 0x95 };
  hpmport.write(stop_measurement, sizeof(stop_measurement));
  //Then we wait for the response
  while(hpmport.available() < 2);
  char read1 = hpmport.read();
  char read2 = hpmport.read();
  // Test the response
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    // ACK
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    // NACK
    return 0;
  }
  else return 0;
}
 
bool HPMA115S0::read (float *p25, float *p10)
{
  // Send the command 0x68 0x01 0x04 0x93
  byte read_particle[] = {0x68, 0x01, 0x04, 0x93 };
  hpmport.write(read_particle, sizeof(read_particle));
  // A measurement can return 0X9696 for NACK
  // Or can return eight bytes if successful
  // We wait for the first two bytes
  while(hpmport.available() < 1);
  byte HEAD = hpmport.read();
  while(hpmport.available() < 1);
  byte LEN = hpmport.read();
  // Test the response
  if ((HEAD == 0x96) && (LEN == 0x96)){
    // NACK
    Serial.println("NACK");
    return 0;
  }
  else if ((HEAD == 0x40) && (LEN == 0x05))
  {
    // The measuremet is valid, read the rest of the data 
    // wait for the next byte
    while(hpmport.available() < 1);
    byte COMD = hpmport.read();
    while(hpmport.available() < 1);
    byte DF1 = hpmport.read(); 
    while(hpmport.available() < 1);
    byte DF2 = hpmport.read();     
    while(hpmport.available() < 1);
    byte DF3 = hpmport.read();   
    while(hpmport.available() < 1);
    byte DF4 = hpmport.read();     
    while(hpmport.available() < 1);
    byte CS = hpmport.read();      
    // Now we shall verify the checksum
    if (((0x10000 - HEAD - LEN - COMD - DF1 - DF2 - DF3 - DF4) % 0XFF) != CS){
      Serial.println("Checksum fail");
      return 0;
    }
    else
    {
      // Checksum OK, we compute PM2.5 and PM10 values
      *p25 = DF1 * 256 + DF2;
      *p10 = DF3 * 256 + DF4;
      return 1;
    }
  }
}
 

bool HPMA115S0::stop_autosend(void)
{
  // Stop auto send
  byte stop_autosend[] = {0x68, 0x01, 0x20, 0x77 };
  hpmport.write(stop_autosend, sizeof(stop_autosend));
  //Then we wait for the response
  while(hpmport.available() < 2);
  byte read1 = hpmport.read();
  byte read2 = hpmport.read();
  // Test the response
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    // ACK
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    // NACK
    return 0;
  }
  else return 0;
}
 
bool HPMA115S0::enable_autosend(void)
{
 // Start auto send
  byte start_autosend[] = {0x68, 0x01, 0x40, 0x57 };
  hpmport.write(start_autosend, sizeof(start_autosend));
  //Then we wait for the response
  while(hpmport.available() < 2);
  byte read1 = hpmport.read();
  byte read2 = hpmport.read();
  // Test the response
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    // ACK
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    // NACK
    return 0;
  }
  else return 0;
}
