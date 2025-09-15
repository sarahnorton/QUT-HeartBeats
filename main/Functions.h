extern Adafruit_DCMotor *ArmMagnets; // Sharing info between both docs

// Definitions
#define EIGTHREV 25 //(200/8)
#define FULLREV 200 // 200 
#define FILLINGREV 150 // full cycle - 2 block posiiton


// INITIALISATION SECTION

void initialiseMotorShield(){
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Stepper motor on M3 & M4
Adafruit_StepperMotor *stepperMotor = AFMS.getStepper(200, 2);
// Electromagnet on M1
Adafruit_DCMotor *ArmMagnets = AFMS.getMotor(1);
// Electromagnet on M1
Adafruit_DCMotor *LockMagnets = AFMS.getMotor(2);

if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
    if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  }
}

// OPERATION FUNCTIONS


// Magnet Functions
void hold(String onOrOff){ // To use the function you either say hold(on) or hold(off)
  if(onOrOff == "on"){
    ArmMagnets->run(FORWARD);
  }
  else{
    ArmMagnets->run(RELEASE);
  }
}

void repel(unsigned long ms) { // To use the function you say repel(1000) for repeling for 1000ms for example
  Serial.print("Repel (reverse) for ");
  Serial.print(ms);
  Serial.println(" ms");
  ArmMagnets->run(BACKWARD);
  delay(ms);
}

// Locking magnets function
void lock(String OnOff){
  if(OnOff == "on"){
    LockMagnets->run(FORWARD);
  }
  else{
    LockMagnets->run(RELEASE);
  }
}


// Stepper Functions

void FillAndDischarge(){ // Designed to be used with the stepper on block two @ the inlet
  hold(on);
  stepperMotor->step(FILLINGREV, FORWARD, INTERLEAVE); 
}

void SwitchLockedBlocks(){
  lock(off); // unlocks block one
  stepperMotor->step(EIGTHREV, FORWARD, INTERLEAVE); // pushed both blocks one position
  lock(on); // locks block two
  // @ this point we should have block one at the outlet and block two locked in
}

void PickupOtherBlock(){
  hold(off);
  stepperMotor->step(EIGTHREV, FORWARD, INTERLEAVE); // goes to the next block
  hold(on); // grabs the block
  // we should now be ready to run the fill and empty function again
}