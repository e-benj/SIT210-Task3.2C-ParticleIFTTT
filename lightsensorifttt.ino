//Ethan Benjamin
//SIT210 Task 3.2C

//Part of this code was attained from the "usage.ino" example file in the BH1750 library

#include "BH1750.h"
BH1750 sensor(0x23, Wire);

//declare global variables
bool sent;

int seconds_sun;

//declare the lux level accepted as direct sunlight as a const
const int SUNLIGHT_LUX = 15000;

void setup()
{
  //initialize the sensor
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
 
 //initialize global variables
  sent = false;
  
  seconds_sun = 0;
}

void loop()
{
    
  //force sensor to make measurement
  sensor.make_forced_measurement();
  
  
  //determine course of action based on reading and variable states
  if ((sensor.get_light_level() > SUNLIGHT_LUX) && (sent == false)){
      Particle.publish("sun", "sunlight");
      sent = true;
  }
  
  if ((sensor.get_light_level() > SUNLIGHT_LUX) && (sent == true)){
      seconds_sun += 10;
  }
  
  if ((sensor.get_light_level() < SUNLIGHT_LUX) && (sent == true)){
      Particle.publish("nosun", String(seconds_sun/60));
      seconds_sun = 0;
      sent = false;
  }

  //wait 10 seconds before next reading
  delay(10000);
}
