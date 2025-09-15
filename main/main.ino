#include <Adafruit_MotorShield.h>
#include "Functions.h"

/* HOW TO SETUP TO USE THIS CODE

Block 1: in the middle locked position
Block 2: at the inlet
Stepper Arm: on block two

CONNECTIONS

- Arm electromagnets: plugged into motor 1 location
- Lock electromagnets: plugged into motor 2 location
- Stepper : plugged into M3 & M4


*/

void setup() {
  Serial.begin(9600); // Initialising the serial
  initialiseMotorShield(); // Initialising the motor shield
  
  // Set speeds
  stepperMotor->setSpeed(60);  // 60 rpm - I'm not sure what real speed we need but I assume its something around this
  ArmMagnets->setSpeed(150);   // Made this a little less to help with overheating
  LockMagnets->setSpeed(150);   // Made this a little less to help with overheating
}

void loop() {
  Serial.println("Begining Fill & Discharge Phase");
  FillAndDischarge();
  Serial.println("Check if block 2 is now on the inlet port");
  delay(3000); // Giving testers time to check
  SwitchLockedBlocks();
  Serial.println("Check if block 2 is now locked and block one is at the outlet");
  delay(3000); // Giving testers time to check
  PickupOtherBlock(); 
  Serial.println("Check if stepper left the blocks alone but changed the block it is holding");
  delay(3000); //
}
