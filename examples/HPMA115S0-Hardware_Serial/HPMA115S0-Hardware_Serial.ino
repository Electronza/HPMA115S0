// HPMA115S0 dust sensor example
// for use with devices with hardware Serial ports
// like Arduino Mega or Arduino Due
//
// IMPORTANT!!!
// When using Arduino Mega boards, 
// a logic level converter for 
// TX and RX lines is mandatory
// (I used BOB-12009 from Sparkfun)
// ---------------------------------

#include <hpma115s0.h>
bool my_status;
float p25;
float p10;

HPMA115S0 my_hpm(Serial2);
 
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println ("HPMA115S0 hardware serial example");

  delay(100);
 
  // Stop autosend
  my_status = my_hpm.stop_autosend(); 
  if (my_status == 1){
    Serial.println("Autosend disabled");
  }
  else{
  Serial.print("Error");  
  }
  delay(500);
  
  // Start fan (and measurement mode)
  my_status = my_hpm.start_measurement();  
  if (my_status == 1){
    Serial.println("Start Particle Measurement");
  }
  else{
  Serial.print("Error");  
  }
  delay(5000);
}
 
 
void loop() {
  // Read the particle data every fifteen seconds
  my_status = my_hpm.read(&p25,&p10); 
  if (my_status == 1){
	Serial.print("PM2.5 value is ");
    Serial.println(p25);
    Serial.print("PM10 value is ");
    Serial.println(p10);
    Serial.println(" ");
  }
  else{
	Serial.println("Measurement fail");  
  }	
  // Wait 15 seconds
  delay(15000);
}
 
