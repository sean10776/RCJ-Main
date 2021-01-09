#include <Arduino.h>
#include <Robot.h>
Robot Attack;
Motor car;
IR ir;
int pwr = 20;
void seaching();
void setup()
{
  // put your setup code here, to run once:
  car.init();
  ir.init();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
void searching()
{
  float angle = ir.GetVal();
  if (angle > 80 && angle < 100)
  {
    car.Motion(0, 20);
  }
  else if (angle > 100 && angle < 270)
  {
    float x = pwr * cos(radians(angle + 60)), y = pwr * sin(radians(angle + 60));
    car.Motion(x, y);
  }
  else if (!(angle < 0))
  {
    float x = pwr * cos(radians(angle - 60)), y = pwr * sin(radians(angle - 60));
    car.Motion(x, y);
  }
  else
  {
    car.Motion(0, 0);
  }
}
