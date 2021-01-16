#include <Arduino.h>
#include <Robot.h>
Robot Attack;

void setup()
{
  // put your setup code here, to run once:
  Attack.init();
  Attack.debugmode.init(false, &Attack.ir, &Attack.light, NULL);
  Attack.debugmode.Debug();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(!Attack.Border()){
    Attack.Searching();
  }
}
