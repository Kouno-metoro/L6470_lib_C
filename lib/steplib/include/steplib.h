#ifndef _steplib_h
#define _steplib_h

//プロトタイプ宣言
void sendconfig(uint8_t,uint8_t);
void sendconfigs(uint8_t,void*,size_t);
void stephardstop(uint8_t);
void stepsoftstop(uint8_t);
void stepreset(uint8_t);
void voltage_config(uint8_t,uint8_t,uint8_t,uint8_t);
void current_config(uint8_t,uint8_t);
void reset_position(uint8_t);
void accel_config(uint8_t,uint16_t,uint16_t);
void stepmove(uint8_t,int32_t);
void stepmoveposition(uint8_t,int32_t,int32_t);
void stepfullstep(uint8_t);

#endif