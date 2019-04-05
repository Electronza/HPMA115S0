// ---------------------------------
// HPMA115S0 dust sensor example
// for use with devices with SoftSerial
// on boards like Arduino Uno
//
// IMPORTANT!!!
// When using Arduino Uno boards, 
// a logic level converter for 
// TX and RX lines is mandatory
// (I used BOB-12009 from Sparkfun)
// ---------------------------------

#include <hpma115s0.h>
#include <SoftwareSerial.h>

bool my_status;
float p25;
float p10;

SoftwareSerial mySerial(10, 11); // RX, TX
HPMA115S0 my_hpm(mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println ("HPMA115S0 software serial example");

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
