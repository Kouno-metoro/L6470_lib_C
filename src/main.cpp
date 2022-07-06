#include <Arduino.h>
#include<SPI.h>
#include"../lib/steplib/include/steplib.h"

#define stepSPI_MISO 12
#define stepSPI_MOSI 11
#define stepSPI_SCK 13
#define step1_SS 2
#define step2_SS 3
#define step3_SS 4
#define step4_SS 5
#define step5_SS 6
#define step1 1
#define step2 2
#define step3 3
#define step4 4
#define step5 5
#define all 0

void setup(){
  pinMode(stepSPI_MOSI,OUTPUT);
  pinMode(stepSPI_MISO,INPUT);
  pinMode(stepSPI_SCK,OUTPUT);
  pinMode(step4_SS,OUTPUT);
  digitalWrite(step4_SS,HIGH);

  SPI.setDataMode(SPI_MODE2);
  SPI.begin();

  stephardstop(step4);
  stepreset(all);
  delay(100);

  //fullstep();
  voltage_config(all,0x40,0x30,0x40);
  current_config(all,0xF);
  reset_position(all);
  accel_config(all,0x20, 0x20);
  stephardstop(all);
  delay(100);
}

void loop(){
  stepmove(all,-20000);
  delay(5000);
  stephardstop(all);
  delay(100);
  stepmoveposition(all,40000,0);
  delay(5000);
  stephardstop(all);
  delay(100);
  stepmoveposition(all,10000,25600);
  delay(5000);
  stephardstop(all);
  delay(100);
  stepmoveposition(all,-10000,0);
  delay(5000);
  stephardstop(all);
  delay(100);
}