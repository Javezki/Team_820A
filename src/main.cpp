#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
controller Controller1 = controller(primary);
motor LeftDriveSmart = motor(PORT7, ratio18_1, false);
motor RightDriveSmart = motor(PORT2, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 310, mm, 1);

motor ShootingMotorA = motor(PORT3, ratio18_1, false);
motor ShootingMotorB = motor(PORT4, ratio18_1, false);
motor_group Shooting = motor_group(ShootingMotorA, ShootingMotorB);

motor Tail = motor(PORT5, ratio18_1, false);

/*vex-vision-config:begin*/
vision::signature VisionSensor__DISC = vision::signature (1, 2185, 3213, 2699,-5301, -5083, -5192,3.9, 0);
vision VisionSensor = vision (PORT1, 50, VisionSensor__DISC);
/*vex-vision-config:end*/
line LineTrackerA = line(Brain.ThreeWirePort.A);



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:      Controller1.ButtonUp.released(callback);
 {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
// Allows for easier use of the VEX Library
using namespace vex;
// Conversion rates
double CM_TO_INCH = 2.54;
double INCH_TO_CM = 0.393;

// Position in map
double xPosition = 0;
double yPosition = 0;

// Mathemtical Constants
double PI = 3.14159265;

// Robot Constants
double WHEEL_RADIUSCM = 5.08;
double WHEEL_RADIUSIN = 5.08 * CM_TO_INCH;

void threadAlive();
void initControls();


int main() {
  initControls();
  threadAlive();
}


/* 
* This class is for someone way smarter than me. Or richer. 
* Use Kinematics and calc to determine dist
*/
// class Mapping {
  
//   void updatePosition() {
//     int wheelRPS = Drivetrain.velocity(rpm) / 60;
//   } 
  

// };


/*
* Automatic controls of the robot, for the autonomous period
*/

class RobotAuto {
  public:
  static void autoTail() {
    Tail.setPosition(0, degrees);
    Tail.setVelocity(70,percent);
    while (Tail.position(degrees) != 180){
      Tail.spin(forward);
    }
    Tail.setPosition(0,degrees);
    /**
    * Set tail position
    * Set tail speed
    * Rotate x amount
    * Reset tail position
    */
  }
};


/** 
* This class has the manual controls of the robot,  
* 
*/

class RobotControls {
  /** 
  * manual for variable forward and backward controls
  * printf was used for debugging
  */
  public:
  static void manualDirectionalMovement() {
    int intensity = Controller1.Axis3.position();
    Drivetrain.setDriveVelocity(intensity, percent);
    // printf("The intensity of the car: %d\n", intensity);
    Drivetrain.drive(forward);
  };

  /** 
  * manual for variable rotation controls
  */
  public:
  static void manualRotationalMovement() {
    int intensity = Controller1.Axis1.position();
    Drivetrain.setTurnVelocity(intensity, percent);
    Drivetrain.turn(right);
  };

  /* 
  * This function sets the motors shoot manually dictated by 
  * the driver
  * Shooting Motor A is the right motor
  * Shooting Motor B is the left motor
  * The commented functions are the manual manual for left and right
  * shooting 
  */
  // public:
  // static void manualShootLeft() {
  //     Shooting.setVelocity(100, percent);
  //     while (Controller1.ButtonR1.pressing())
  //     {
  //       ShootingMotorB.spin(reverse);
  //     };
  //     ShootingMotorB.stop();
  //   };

  // public:
  //   static void manualShootRight() {
  //     Shooting.setVelocity(100, percent);
  //     while (Controller1.ButtonR2.pressing()) {
  //       ShootingMotorA.spin(forward);
  //     }
  //     ShootingMotorA.stop();
  //   }

  /* 
  * Manual controls for shooting the robot
  */

  public:
    static void manualShoot() {
      while (Controller1.ButtonR1.pressing()) {
        /*
        * Need testing 
        */
        Shooting.spin(forward);
      };
      Shooting.stop();
    }

  /**
  * This function is used to control the orientation of the tail
  * manually
  */

  public:
    static void manualTail() {
      while (Controller1.ButtonL1.pressing())
      {
        Tail.spin(forward);
      };
      while (Controller1.ButtonL2.pressing())
      {
        Tail.spin(reverse);
      };
      Tail.stop();
    }
};

/** 
* Initialize the control listeners 
*/

void initControls() {
  RobotControls controls;
  Controller1.Axis3.changed(controls.manualDirectionalMovement);
  Controller1.Axis1.changed(controls.manualRotationalMovement);
  Controller1.ButtonR1.pressed(controls.manualShoot);
  Controller1.ButtonL1.pressed(controls.manualTail);
  Controller1.ButtonL2.pressed(controls.manualTail);
}

/** 
* Keep the thread alive
*/

void threadAlive() {
  while (true) {
    wait (0.5,seconds);
  }
}