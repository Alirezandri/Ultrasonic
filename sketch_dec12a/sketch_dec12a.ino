#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 9;
const int echoPin = 10;

const int ledPin = 6;

unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Distance:");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.0343 / 2;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  if (distance <= 10) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  } else {
    digitalWrite(ledPin, LOW);
    ledState = LOW;
  }

  delay(100);
}
