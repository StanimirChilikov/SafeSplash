#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define Sone 2
#define Stwo 3
#define Sthree 4
#define Sfour 11
#define Sfive 12
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int pumpPin = 13;
const unsigned long interval = 5000;
unsigned long previousMillis = 0;

int ena = 5;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int enb = 10;
int trigPin = A0;
int echoPin = A1;

int analog3 = A2;

long duration;
int distance;

void setup() {

  pinMode(Sone, INPUT);
  pinMode(Stwo, INPUT);
  pinMode(Sthree, INPUT);
  pinMode(Sfour, INPUT);
  pinMode(Sfive, INPUT);

  pinMode(pumpPin, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(pumpPin, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Starting...");
  display.display();
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();

  bool value1 = digitalRead(Sone);
  bool value2 = digitalRead(Stwo);
  bool value3 = digitalRead(Sthree);
  bool value4 = digitalRead(Sfour);
  bool value5 = digitalRead(Sfive);
  int analogvalue3 = analogRead(analog3);
  Serial.println(analogvalue3);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
      distance = -1; // no reading
  } else {
      distance = duration * 0.034 / 2;
      //Serial.println(distance);
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");
  display.print("Flames: ");
  display.print(digitalRead(Sone));
  display.print(digitalRead(Stwo));
  display.print(digitalRead(Sthree));
  display.print(digitalRead(Sfour));
  display.println(digitalRead(Sfive));
  display.print("Pump: ");
  if(digitalRead(pumpPin) == HIGH) {
    display.println("ON");
  } else {
    display.println("OFF");
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    display.display();
    Serial.println("Timer triggered!");
  }

  /*Serial.print(value1);
  Serial.print(" ");
  Serial.print(value2);
  Serial.print(" ");
  Serial.print(value3);
  Serial.print(" ");
  Serial.print(value4);
  Serial.print(" ");
  Serial.println(value5);*/
  
  //bool fireDetected = value1 || value2 || value3 || value4 || value5;
  if (value3 && analogvalue3 > 900) {
      digitalWrite(pumpPin, HIGH);
  } else {
      digitalWrite(pumpPin, LOW);
  }
  if (distance < 30 && distance > 10) {
    Serial.println("stopping!");
    Serial.println(distance);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(pumpPin, LOW);
  }
  else if (analogvalue3 < 950 && value3 == HIGH) {  // Fire ahead
      Serial.println("Fire ahead");
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      analogWrite(ena,255);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(enb,255);
  }
  else if (value3 == HIGH && value2 == HIGH && value4 == HIGH) {
      Serial.println("Fire ahead");
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      analogWrite(ena,255);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(enb,255);
  }
  else if (value2 == HIGH || value1 == HIGH) {  // Fire right
      Serial.println("Fire right");
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      analogWrite(ena,255);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(enb,0);
  }
  else if (value4 == HIGH || value5 == HIGH) {  // Fire left
      Serial.println("Fire left");
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      analogWrite(ena,0);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(enb,255);
  }
  else {  // No fire
      if (analogvalue3 > 960) {
        Serial.println("Too close to fire");
        //digitalWrite(pumpPin, HIGH);
      }
      else {
        Serial.println("No fire");
        //digitalWrite(pumpPin, LOW);
      }
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
  }
  delay(50);
}