#include <Utility.h>
#define M_PI 3.14159265359

double freq = 0.1;
double period_us = 1000000 / freq / 6;
double omega_us = 1 / period_us * M_PI / 3;
const int outPins[3] = {3, 6, 9}; //D3, D5, D8
const int modePins[3] = {2, 7, 8};
double moterf[3];
uint16_t moter[3];

struct pin_status {
  bool mode;
  uint8_t st_pin;
  uint8_t up_pin;
  uint8_t dn_pin;
};


struct pin_status mode_map[6] = {
  {0, 0, 1, 2},
  {1, 1, 2, 0},
  {0, 2, 0, 1},
  {1, 0, 1, 2},
  {0, 1, 2, 0},
  {1, 2, 0, 1}
};

void setup() {
  Serial.begin(9600);
  Serial.println("StaRt!");
  for (int i = 0; i < 3; i++) {
    pinMode(outPins[i], OUTPUT);
    pinMode(modePins[i], OUTPUT);
    setPWMFrequency(outPins[i], PWM_DIV32);
  }
  
}

int pwm1, pwm2, i;
unsigned long prev_t;
unsigned long now_t;

void loop() {
  if(freq < 150){
    if(freq < 50){
      freq += 2;
    }else if(freq < 100){
      freq += 0.2;
    }/*else if(freq < 110){
      freq +=0.02;
    }else if(freq < 135){
      freq += 0.002;
    }else{
      freq += 0.0002;
    }*/
    Serial.println(freq);
    period_us = 1000000 / freq / 6;
    omega_us = 1 / period_us * M_PI / 3;
  }
  for (i = 0; i < 6; i++) {
    prev_t = micros();
    digitalWrite(modePins[mode_map[i].st_pin],mode_map[i].mode);
    analogWrite(outPins[mode_map[i].st_pin],250);
    digitalWrite(modePins[mode_map[i].up_pin],!mode_map[i].mode);
    digitalWrite(modePins[mode_map[i].dn_pin],!mode_map[i].mode);
    while ((micros() - prev_t) <= period_us) {
      now_t = micros() - prev_t;
      pwm1 = 250 * sin(now_t * omega_us);
      pwm2 = 250 * sin((period_us - now_t) * omega_us);
      analogWrite(outPins[mode_map[i].up_pin],pwm1);
      analogWrite(outPins[mode_map[i].dn_pin],pwm2);
    }
  }/*
  int period = 1000;
  double t = 2 * PI * (millis()%period) / period;
  
  moterf[0] = sin(t);
  moterf[1] = sin(t+2*PI/3);
  moterf[2] = sin(t+4*PI/3);
  for(int i=0; i<3; i++){
    moter[i] = (1+moterf[i])/2 * 240;
    Serial.print(moter[i]);
    Serial.print(" ");
    analogWrite(outPins[i], moter[i]);
  }
  Serial.println("");*/
}
