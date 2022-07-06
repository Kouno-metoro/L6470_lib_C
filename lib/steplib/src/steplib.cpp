#include<Arduino.h>
#include<SPI.h>

#define stepSPI_MISO 12
#define stepSPI_MOSI 11
#define stepSPI_SCK 13
#define step1_SS 2
#define step2_SS 3
#define step3_SS 4
#define step4_SS 5
#define step5_SS 6
#define step_all 0

#define hardstop 0xB8
#define softstop 0xB0
#define reset 0xC0
#define KVALacc 0x0B
#define KVALrun 0x0A
#define KVALdec 0x0C
#define OCD_TH 0x13
#define posreset 0xD8
#define ACC 0x05
#define DECELERATION 0x06
#define maxspeed 0x07
#define move 0x50
#define gotodir 0x68
#define stepmode 0x16
#define fullstep 0x00

void sendconfig(int no,uint8_t byte){
    switch (no){
      case step1_SS:
        digitalWrite(step1_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step1_SS,HIGH);
        delayMicroseconds(1);
      break;

      case step2_SS:
        digitalWrite(step2_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step2_SS,HIGH);
        delayMicroseconds(1);
      break;

      case step3_SS:
        digitalWrite(step3_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step3_SS,HIGH);
        delayMicroseconds(1);
      break;

      case step4_SS:
        digitalWrite(step4_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step4_SS,HIGH);
        delayMicroseconds(1);
      break;

      case step5_SS:
        digitalWrite(step5_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step5_SS,HIGH);
        delayMicroseconds(1);
      break;

      case step_all:
        digitalWrite(step1_SS,LOW);
        digitalWrite(step2_SS,LOW);
        digitalWrite(step3_SS,LOW);
        digitalWrite(step4_SS,LOW);
        digitalWrite(step5_SS,LOW);
        SPI.transfer(byte);
        digitalWrite(step1_SS,LOW);
        digitalWrite(step2_SS,LOW);
        digitalWrite(step3_SS,LOW);
        digitalWrite(step4_SS,LOW);
        digitalWrite(step5_SS,LOW);       
        delayMicroseconds(1);
      break;
    
    }
}

void sendconfigs(int no,void *byte,size_t len){
  uint8_t *data_ptr = (uint8_t *)byte;
  switch (no){
    case step1_SS:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step1_SS, LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step1_SS, HIGH);
        delayMicroseconds(1);
        }
    break;

    case step2_SS:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step2_SS, LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step2_SS, HIGH);
        delayMicroseconds(1);
      }
    break;

    case step3_SS:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step3_SS, LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step3_SS, HIGH);
        delayMicroseconds(1);
      }
    break;

    case step4_SS:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step4_SS, LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step4_SS, HIGH);
        delayMicroseconds(1);
      }
    break;

    case step5_SS:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step5_SS, LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step5_SS, HIGH);
        delayMicroseconds(1);
      }
    break;

    case step_all:
      for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(step1_SS,LOW);
        digitalWrite(step2_SS,LOW);
        digitalWrite(step3_SS,LOW);
        digitalWrite(step4_SS,LOW);
        digitalWrite(step5_SS,LOW);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(step1_SS,LOW);
        digitalWrite(step2_SS,LOW);
        digitalWrite(step3_SS,LOW);
        digitalWrite(step4_SS,LOW);
        digitalWrite(step5_SS,LOW);
        delayMicroseconds(1);
      }       
    break;
    
  }

}

void stephardstop(int no){
  sendconfig(no,hardstop);
}

void stepsoftstop(int no){
    sendconfig(no,softstop);
}

void stepreset(int no){
    sendconfig(no,reset);
}

void voltage_config(int no,uint8_t vacc,uint8_t vrun,uint8_t vdec){
    sendconfig(no,KVALacc);
    sendconfigs(no,&vacc,sizeof(vacc));
    sendconfig(no,KVALrun);
    sendconfigs(no,&vrun,sizeof(vrun));
    sendconfig(no,KVALdec);
    sendconfigs(no,&vdec,sizeof(vdec));
}

void current_config(int no,uint8_t val){
    sendconfig(no,OCD_TH);
    sendconfigs(no,&val,sizeof(val));
}

void reset_position(int no){
    sendconfig(no,posreset);
}

void accel_config(int no,uint16_t acc,uint16_t dec){
    sendconfig(no,ACC);
    sendconfigs(no,&acc,sizeof(acc));
    sendconfig(no,DECELERATION);
    sendconfigs(no,&dec,sizeof(dec));
}

void stepmove(int no,int32_t speed){
    uint8_t direction = (speed >= 0);
    speed=abs(speed);
    uint16_t max=0xFFFF;
    sendconfig(no,maxspeed);
    sendconfigs(no,&max,sizeof(max));

    sendconfig(no,move | direction);
    sendconfigs(no,&speed, 3);
}

void stepmoveposition(int no,int32_t speed,int32_t position){
    int8_t direction = 0;
    direction = ((speed >= 0) ? 1 : -1) * ((position >= 0) ? 1 : -1);
    direction = (direction >= 0);

    speed = abs(speed) >> 10;

    sendconfig(no,maxspeed);
    sendconfigs(no,&speed, 2);

    sendconfig(no,gotodir | direction);
    sendconfigs(no,&position, 3);

}

void stepfullstep(int no){
    sendconfig(no,stepmode);
    sendconfig(no,fullstep);
}