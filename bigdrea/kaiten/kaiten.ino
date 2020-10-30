#include<QTRSensors.h>
#define LED_OUTPIN 2

QTRSensors qtr;
unsigned int sensorValues[1];


void setup(){
  Serial.begin(9600);
  pinMode(LED_OUTPIN, OUTPUT);
  digitalWrite(LED_OUTPIN, HIGH);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){11}, 1);
  qtr.calibrate();
  Serial.println("start!");
}

void loop(){
  qtr.readCalibrated(sensorValues);
  Serial.println(sensorValues[0]);
  delay(100);
}
