#include<Arduino.h>
#include<SPI.h>

//ピン設定
#define stepSPI_MISO 12
#define stepSPI_MOSI 11
#define stepSPI_SCK 13
#define step1_SS 2
#define step2_SS 3
#define step3_SS 4
#define step4_SS 5
#define step5_SS 6
#define step_all 0

//コマンド設定
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

//送信用関数
void sendconfig(uint8_t no,uint8_t byte){
  //1ポート
  if((no&0x01)==1){
    digitalWrite(step1_SS,LOW);
    SPI.transfer(byte);
    digitalWrite(step1_SS,HIGH);
    delayMicroseconds(1);
  }
  //2ポート
  if((no&0x02)==2){
    digitalWrite(step2_SS,LOW);
    SPI.transfer(byte);
    digitalWrite(step2_SS,HIGH); 
    delayMicroseconds(1);   
  }
  //3ポート
  if((no&0x04)==4){
    digitalWrite(step3_SS,LOW);
    SPI.transfer(byte);
    digitalWrite(step3_SS,HIGH);
    delayMicroseconds(1);
  }
  //4ポート
  if((no&0x08)==8){
    digitalWrite(step4_SS,LOW);
    SPI.transfer(byte);
    digitalWrite(step4_SS,HIGH);
    delayMicroseconds(1);
  }
  //5ポート
  if((no&0x10)==16){
    digitalWrite(step5_SS,LOW);
    SPI.transfer(byte);
    digitalWrite(step5_SS,HIGH);
    delayMicroseconds(1);
  }
}

//送信用関数(複数ビット)
void sendconfigs(uint8_t no,void *byte,size_t len){
  uint8_t *data_ptr = (uint8_t *)byte;
  //1ポート
  if((no&0x01)==1){
    for (int8_t i = len - 1; i >= 0; i--) {
      digitalWrite(step1_SS, LOW);
      SPI.transfer(*(data_ptr + i));
      digitalWrite(step1_SS, HIGH);
      delayMicroseconds(1);
    }
  }
  //2ポート
  if((no&0x02)==2){
    for (int8_t i = len - 1; i >= 0; i--) {
      digitalWrite(step1_SS, LOW);
      SPI.transfer(*(data_ptr + i));
      digitalWrite(step1_SS, HIGH);
      delayMicroseconds(1);
    }
  }
  //3ポート
  if((no&0x04)==4){
    for (int8_t i = len - 1; i >= 0; i--) {
      digitalWrite(step1_SS, LOW);
      SPI.transfer(*(data_ptr + i));
      digitalWrite(step1_SS, HIGH);
      delayMicroseconds(1);
    }
  }
  //4ポート
  if((no&0x08)==8){
    for (int8_t i = len - 1; i >= 0; i--) {
      digitalWrite(step1_SS, LOW);
      SPI.transfer(*(data_ptr + i));
      digitalWrite(step1_SS, HIGH);
      delayMicroseconds(1);
    }
  }
  //5ポート
  if((no&0x10)==16){
    for (int8_t i = len - 1; i >= 0; i--) {
      digitalWrite(step1_SS, LOW);
      SPI.transfer(*(data_ptr + i));
      digitalWrite(step1_SS, HIGH);
      delayMicroseconds(1);
    }
  }
}

void stephardstop(uint8_t no){
  sendconfig(no,hardstop);
}

void stepsoftstop(uint8_t no){
  sendconfig(no,softstop);
}

void stepreset(uint8_t no){
  sendconfig(no,reset);
}

void voltage_config(uint8_t no,uint8_t vacc,uint8_t vrun,uint8_t vdec){
  sendconfig(no,KVALacc);
  sendconfigs(no,&vacc,sizeof(vacc));
  sendconfig(no,KVALrun);
  sendconfigs(no,&vrun,sizeof(vrun));
  sendconfig(no,KVALdec);
  sendconfigs(no,&vdec,sizeof(vdec));
}

void current_config(uint8_t no,uint8_t val){
  sendconfig(no,OCD_TH);
  sendconfigs(no,&val,sizeof(val));
}

void reset_position(uint8_t no){
  sendconfig(no,posreset);
}

void accel_config(uint8_t no,uint16_t acc,uint16_t dec){
  sendconfig(no,ACC);
  sendconfigs(no,&acc,sizeof(acc));
  sendconfig(no,DECELERATION);
  sendconfigs(no,&dec,sizeof(dec));
}

void stepmove(uint8_t no,int32_t speed){
  uint8_t direction = (speed >= 0);
  speed=abs(speed);
  uint16_t max=0xFFFF;
  sendconfig(no,maxspeed);
  sendconfigs(no,&max,sizeof(max));
  sendconfig(no,move | direction);
  sendconfigs(no,&speed, 3);
}

void stepmoveposition(uint8_t no,int32_t speed,int32_t position){
  int8_t direction = 0;
  direction = ((speed >= 0) ? 1 : -1) * ((position >= 0) ? 1 : -1);
  direction = (direction >= 0);

  speed = abs(speed) >> 10;

  sendconfig(no,maxspeed);
  sendconfigs(no,&speed, 2);
  sendconfig(no,gotodir | direction);
  sendconfigs(no,&position, 3);
}

void stepfullstep(uint8_t no){
  sendconfig(no,stepmode);
  sendconfig(no,fullstep);
}