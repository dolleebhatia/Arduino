#include <AccelStepper.h>

// Define two steppers and the pins they will use
AccelStepper stepper1(1, 9, 8);
AccelStepper stepper2(1, 11, 12);

int pos1 = 1000;
int pos2 = 1800;

void setup()
{  
  stepper1.setMaxSpeed(500);
  stepper1.setAcceleration(500);
  stepper2.setMaxSpeed(500);
  stepper2.setAcceleration(500);
}

void loop()
{
  if (stepper1.distanceToGo() == 0)
  {
    delay(20);
    pos1 = -pos1;
    stepper1.moveTo(pos1);
  }
  if (stepper2.distanceToGo() == 0)
  {
    delay(20);
    pos2 = -pos2;
    stepper2.moveTo(pos2);
  }
  stepper1.run();
  stepper2.run();
}

