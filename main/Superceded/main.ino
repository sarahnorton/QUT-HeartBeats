#include <Adafruit_MotorShield.h>
#include "Functions.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Stepper motor on M3 & M4
Adafruit_StepperMotor *stepperMotor = AFMS.getStepper(200, 2);

// Electromagnet on M1
Adafruit_DCMotor *ElectroMag1 = AFMS.getMotor(1);


void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Stepper + Magnet Test!");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set speeds
  stepperMotor->setSpeed(60);  // 60 rpm - I'm not sure what real speed we need but I assume its something around this
  ElectroMag1->setSpeed(150);   // Made this a little less to help with overheating
}


// How The code is intended to run at the moment
// - The magnet is over the block, the magnet picks it up, the stepper takes it 180 degrees, the magnet repels the block while the stepper keeps moving, after another 180 degrees the magnet picks up the block again

void loop() {
  Serial.println("Main Loop");

  // Hold magnet ON while moving stepper
  holdOn();
  stepperMotor->step(200, FORWARD, INTERLEAVE); // 200 steps = 180 degrees & interleave looks like a smooth fast choice for movement type

  // Repel briefly during handover
  repel(1000); // reverse for 1 second
  Serial.println("Handover");

  // Back to attract
  holdOn(); 
  stepperMotor->step(200, FORWARD, INTERLEAVE);
}
