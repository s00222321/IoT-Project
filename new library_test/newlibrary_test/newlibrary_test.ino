
#include <Stepper.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int sensorPin = A0;  
int sensorValue = 0;
int sensorPrintValue = 0; 
int buttonPin = 4;

int buttonState = 0;

#define STEPS_PER_MOTOR_REVOLUTION 32
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

int  Steps2Take;

void setup()  
{
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
}

void loop()  
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
  sensorValue = analogRead(sensorPin);
  sensorPrintValue = sensorValue / 4.3;
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.println();
  
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;
  
if (sensorValue > 0)
{
if (sensorValue >= 700) 
  {
    small_stepper.setSpeed(700);
    small_stepper.step(Steps2Take);
    lcd.setRGB(255, 0, 0);
    lcd.print("Heartrate: ");
    lcd.print(sensorPrintValue);
    delay(500);
    lcd.clear();
  }
  else if (sensorValue >= 500 && sensorValue < 700)
  {
    small_stepper.setSpeed(500);
    small_stepper.step(Steps2Take);
    lcd.setRGB(0, 255, 0);
    lcd.print("Heartrate: ");
    lcd.print(sensorPrintValue);
    delay(500);
    lcd.clear();
  }
  else if (sensorValue >= 300 && sensorValue < 500)
  {
    small_stepper.setSpeed(300);
    small_stepper.step(Steps2Take);
    lcd.setRGB(0, 0, 255);
    lcd.print("Heartrate: ");
    lcd.print(sensorPrintValue);
    delay(500);
    lcd.clear();
  }
  else
  {
    small_stepper.setSpeed(100);
    small_stepper.step(Steps2Take);
    lcd.setRGB(0, 200, 200);
    lcd.print("Heartrate: ");
    lcd.print(sensorPrintValue);
    delay(500);
    lcd.clear();
  }
}

  else 
  {
    small_stepper.setSpeed(0);
    small_stepper.step(Steps2Take);
  }

  }

else{
  small_stepper.setSpeed(0);
  small_stepper.step(Steps2Take);
}
}
}

