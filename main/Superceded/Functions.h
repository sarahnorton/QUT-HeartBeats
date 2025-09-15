// Magnet Functions
void hold(String onOrOff){ // To use the function you either say hold(on) or hold(off)
  if(onOrOff == "on"){
    ElectroMag1->run(FORWARD);
  }
  else{
    ElectroMag1->run(RELEASE);
  }
}

void repel(unsigned long ms) { // To use the function you say repel(1000) for repeling for 1000ms for example
  Serial.print("Repel (reverse) for ");
  Serial.print(ms);
  Serial.println(" ms");
  ElectroMag1->run(BACKWARD);
  delay(ms);
}

// Stepper Functions