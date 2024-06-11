#include <Arduino.h>
# define RXD1 17 
# define TXD1 18 

void setup() {
Serial.begin(115200, SERIAL_8O1);
Serial1.begin(115200, SERIAL_8O1, RXD1, TXD1);
}

void loop() {
  if(Serial1.available()>0){
  Serial.write(Serial1.read());
  }
  if(Serial.available()>0){
  Serial1.write(Serial.read());
  }
}


