#include <CheapStepper.h>

int sensorPin = A0;  
int sensorValue = 0; 

CheapStepper stepper (8,9,10,11);  

bool moveClockwise = true;
unsigned long moveStartTime = 0;


void setup() {
  pinMode(sensorPin, INPUT);
  // let's run the stepper at 12rpm (if using 5V power) - the default is ~16 rpm

  stepper.setRpm(16); // CHANGED RPM
  
  Serial.begin(9600); // CHANGED SPEED
  Serial.print("stepper RPM: "); Serial.print(stepper.getRpm());
  Serial.println();

  Serial.print("stepper delay (micros): "); Serial.print(stepper.getDelay());
  Serial.println(); Serial.println();

  stepper.newMoveTo(moveClockwise, 4096);

  moveStartTime = millis();
  
}

void loop() {
  
  sensorValue = analogRead(sensorPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.println();

  if (sensorValue >= 700) 
  {
    stepper.setRpm(16);
    stepper.run();
  }
  else if (sensorValue >= 500)
  {
    stepper.setRpm(10);
    stepper.run();
  }
  else if (sensorValue >= 300)
  {
    stepper.setRpm(5);
    stepper.run();
  }
  else 
  {
    stepper.stop();
  }
  
  int stepsLeft = stepper.getStepsLeft();

  
  if (stepsLeft == 0){
    /*
    Serial.print("stepper position: "); Serial.print(stepper.getStep());
    Serial.println();

    unsigned long timeTook = millis() - moveStartTime; // calculate time elapsed since move start
    Serial.print("move took (ms): "); Serial.print(timeTook);
    Serial.println(); Serial.println();
    
    // let's start a new move in the reverse direction
    */
    //moveClockwise = !moveClockwise; // reverse direction
    stepper.newMoveDegrees (moveClockwise, 360); // move 180 degrees from current position CHANGED DEGREES
    moveStartTime = millis(); // reset move start time

  }
  

}
