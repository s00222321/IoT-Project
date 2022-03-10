#include <CheapStepper.h>
const int buttonPin = 4;  
int buttonState = 0; 

CheapStepper stepper (8,9,10,11);  

 // let's also create a boolean variable to save the direction of our rotation
 // and a timer variable to keep track of move times

bool moveClockwise = true;
unsigned long moveStartTime = 0; // this will save the time (millis()) when we started each new move


void setup() {
  pinMode(buttonPin, INPUT);
  // let's run the stepper at 12rpm (if using 5V power) - the default is ~16 rpm

  stepper.setRpm(100); // CHANGED RPM

  // let's print out the RPM to make sure the setting worked
  
  Serial.begin(0); // CHANGED SPEED
  Serial.print("stepper RPM: "); Serial.print(stepper.getRpm());
  Serial.println();

  // and let's print the delay time (in microseconds) between each step
  // the delay is based on the RPM setting:
  // it's how long the stepper will wait before each step

  Serial.print("stepper delay (micros): "); Serial.print(stepper.getDelay());
  Serial.println(); Serial.println();

  // now let's set up our first move...
  // let's move a half rotation from the start point

  stepper.newMoveTo(moveClockwise, 2048);

  moveStartTime = millis(); // let's save the time at which we started this move
  
}

void loop() {
buttonState = digitalRead(buttonPin);
  // we need to call run() during loop() 
  // in order to keep the stepper moving
  // if we are using non-blocking moves

  if (buttonState == HIGH) {
    stepper.run();
  } else {
    stepper.stop();
  }
  
//BUTTON PRESS


 // let's check how many steps are left in the current move:
  
  int stepsLeft = stepper.getStepsLeft();

  // if the current move is done...
  
  if (stepsLeft == 0){

    // let's print the position of the stepper to serial
    
    Serial.print("stepper position: "); Serial.print(stepper.getStep());
    Serial.println();

    // and now let's print the time the move took

    unsigned long timeTook = millis() - moveStartTime; // calculate time elapsed since move start
    Serial.print("move took (ms): "); Serial.print(timeTook);
    Serial.println(); Serial.println();
    
    // let's start a new move in the reverse direction
    
    moveClockwise = !moveClockwise; // reverse direction
    stepper.newMoveDegrees (moveClockwise, 50); // move 180 degrees from current position CHANGED DEGREES
    moveStartTime = millis(); // reset move start time

  }

}
