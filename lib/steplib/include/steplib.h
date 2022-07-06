#ifndef _steplib_h
#define _steplib_h

void sendconfig(int,uint8_t);
void sendconfigs(int,void*,size_t);
void stephardstop(int);
void stepsoftstop(int);
void stepreset(int);
void voltage_config(int,uint8_t,uint8_t,uint8_t);
void current_config(int,uint8_t);
void reset_position(int);
void accel_config(int,uint16_t,uint16_t);
void stepmove(int,int32_t);
void stepmoveposition(int,int32_t,int32_t);
void stepfullstep(int);

#endif