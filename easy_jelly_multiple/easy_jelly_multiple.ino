#include <AccelStepper.h>

// Define two steppers and the pins they will use
AccelStepper stepper1(1, 9, 8);
AccelStepper stepper2(1, 7, 6);

int pos1 = 3600;
int pos2 = 5678;

void setup()
{  
  stepper1.setMaxSpeed(3000);
  stepper1.setAcceleration(1000);
  stepper2.setMaxSpeed(2000);
  stepper2.setAcceleration(800);
}

void loop()
{
  if (stepper1.distanceToGo() == 0)
  {
    delay(500);
    pos1 = -pos1;
    stepper1.moveTo(pos1);
  }
  if (stepper2.distanceToGo() == 0)
  {
    delay(500);
    pos2 = -pos2;
    stepper2.moveTo(pos2);
  }
  stepper1.run();
  stepper2.run();
}
