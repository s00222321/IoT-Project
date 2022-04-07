
#include <Stepper.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int sensorPin = A0;  
int sensorValue = 0;
int sensorPrintValue = 0; 

#define STEPS_PER_MOTOR_REVOLUTION 32
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

int  Steps2Take;

void setup()  
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  lcd.begin(16, 2);
}

void loop()  
{
  sensorValue = analogRead(sensorPin);
  sensorPrintValue = sensorValue / 4.3;

  lcd.print("Chad's CardiHack");

  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;
  
  
if (sensorValue >= 700) 
  {

    small_stepper.setSpeed(400);
    small_stepper.step(-Steps2Take);
    sensorValue = analogRead(sensorPin);
    sensorPrintValue = sensorValue / 4.3;
    
    lcd.setRGB(255, 0, 0);


   
  }
  else if (sensorValue >= 500 && sensorValue < 700)
  {

    small_stepper.setSpeed(600);
    small_stepper.step(-Steps2Take);
    sensorValue = analogRead(sensorPin);
    sensorPrintValue = sensorValue / 4.3;

    lcd.setRGB(0, 255, 0);



  }
  else if (sensorValue >= 300 && sensorValue < 500)
  {

    small_stepper.setSpeed(800);
    small_stepper.step(-Steps2Take);
    sensorValue = analogRead(sensorPin);
    sensorPrintValue = sensorValue / 4.3;

    lcd.setRGB(0, 0, 255);

  }
  else
  {

    small_stepper.setSpeed(1000);
    small_stepper.step(-Steps2Take);
    sensorValue = analogRead(sensorPin);
    sensorPrintValue = sensorValue / 4.3;
    
    lcd.setRGB(0, 200, 200);

  }

  lcd.clear();

}
