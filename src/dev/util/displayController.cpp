#include "dev/util/displayController.h"
#include "dev/util/autonController.h"
#include "dev/util/misc.h"

pros::ADIAnalogIn button('A');
bool beingPressed = false;
bool initRun=true;

void display(){
  pros::lcd::set_text(0, "Auton Name: " + getAutonName());
  pros::lcd::set_text(1, "Auton Info: " + getAutonDescription());
  pros::lcd::set_text(2, "Left Joystick: " +  std::to_string(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)));
  pros::lcd::set_text(3, "Right Joystick: " +  std::to_string(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)));

  if(button.get_value()<25 && !beingPressed){
    setAuton(getAuton()+1);
    beingPressed=true;
  }else if(button.get_value()>=25){
    beingPressed=false;
  }
  if(getAuton()>getMaxAuton() || initRun)
    setAuton(0);

  updateAuton();
  initRun=false;
}

void refresh(){
  setAuton(0);
}

bool isBeingPressed(){
  return beingPressed;
}

void setBeingPressed(bool state){
  beingPressed=state;
}