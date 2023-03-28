#include <MQ135.h>

#define MQ A0
#define LDR A2
#define SOIL A1
#define FIRE 2
#define R 3


MQ135 mq135_sensor(MQ);

float temperature = 21.0; // Assume current temperature. Recommended to measure with DHT22
float humidity = 25.0; // Assume current humidity. Recommended to measure with DHT22

float CO2;
int Mos, FRE, Light, Pump;

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(SOIL, INPUT);
  pinMode(FIRE, INPUT);
  pinMode(R, OUTPUT);
}

void loop() {
 
  CO2= mq135_sensor.getCorrectedPPM(temperature, humidity);
  
  Mos = analogRead(SOIL);
  Mos = map(Mos, 530, 1023, 100, 0);
  Light = analogRead(LDR);
  Light = map(Light, 0, 1023, 0, 100);
  FRE = !digitalRead(FIRE);

  while (Serial.available()) {
    Pump = Serial.read() - '0';
  }
  if (Pump == 1) {
    digitalWrite(R, LOW);
  } else {
    digitalWrite(R, HIGH);
  }

  Serial.print(" C ");
  Serial.print(CO2);
  Serial.print(" M ");
  Serial.print(Mos);
  Serial.print(" L ");
  Serial.print(Light);
  Serial.print(" F ");
  Serial.print(FRE);
  Serial.println();
  delay(300);
}
