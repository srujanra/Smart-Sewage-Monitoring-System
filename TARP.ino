
#define BLYNK_TEMPLATE_ID "TMPLlXvwj4Go"
#define BLYNK_DEVICE_NAME "TARP"
#define BLYNK_AUTH_TOKEN "GYuO0NCjRKmOCjMjyBMGZjSyBGnBY0Sw"

//#define BLYNK_TEMPLATE_ID "TMPLlXvwj4Go"
//#define BLYNK_DEVICE_NAME "distance measurement"
////#define BLYNK_TEMPLATE_NAME "distance measurement"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#include "BlynkEdgent.h"
#define MQ2 34
#define echoPin 32
#define trigPin 33
#define buzzer 5
#define rpin 27
#define gpin 18

boolean state = false;
long duration;
int distance;
long sensorValue;
void setup()
{
  Serial.begin(115200);
  pinMode(gpin, OUTPUT);
  pinMode(rpin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(MQ2, INPUT);
  BlynkEdgent.begin();
  delay(2000);
}
void gas_sensor() {

  sensorValue = analogRead(MQ2);
  Blynk.virtualWrite(V3, sensorValue);
  Serial.println("gas");
  Serial.println(sensorValue);

  if (sensorValue > 600)
  {
    
    //digitalWrite(gpin, LOW);
    //digitalWrite(rpin, HIGH);
    digitalWrite(buzzer, HIGH);
    Blynk.logEvent("alert","gas detected");
  }

  else
  {
    //digitalWrite(gpin, HIGH);
    //digitalWrite(rpin, LOW);
    digitalWrite(buzzer, LOW);
  }
}
void ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
  Serial.println("Distance: ");
  Serial.println(distance);
  Blynk.virtualWrite(V0, distance);
  delay(500);
  if (distance < 4) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(rpin, HIGH);
    digitalWrite(gpin, LOW);
    Blynk.virtualWrite(V1, 1);
    Blynk.virtualWrite(V2, 0);
    
    Blynk.logEvent("alert","blocked!!!!");
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(rpin, LOW);
    digitalWrite(gpin, HIGH);
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V1, 0);
  }
}
void loop()
{
  BlynkEdgent.run();
  ultrasonic();
  gas_sensor();
}
