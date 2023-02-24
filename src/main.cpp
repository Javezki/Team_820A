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
motor Crossbow = motor(PORT8, ratio18_1, false);

motor Roller = motor(PORT20, ratio18_1, false);

motor Intake = motor(PORT10, ratio18_1, false);




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
// double xPosition = 0;
// double yPosition = 0;

// Mathemtical Constants
double PI = 3.14159265; 

// Robot Constants
// double WHEEL_RADIUSCM = 5.08;
// double WHEEL_RADIUSIN = 5.08 * CM_TO_INCH;
int shootSpeed = 40;
int intakeSpeed = 40;

void threadAlive();
void initControls();
void initModes();

/* THE ROBOT CONTROLS AND MAPPING
* R1 - Shooting (You can hold it)
* R2 - Roller Adjustment (You can hold it)
* L1 - Intake (You can hold it)
* L2 - Tail (You can hold it)
* Y - Field Expansions (Hold for 1 second)
* Up Arrow - Increase Shooting Speed
* Down Arrow - Decrease Shooting Speed
* Left Joy Stick - Drive forward or backward (You can hold)
* Right Joy Stick - Turn the robot (You can hold)
*/

int main() {
  initModes();
  initControls();
  threadAlive();
  return 0;
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

class AutonomousPeriod {
  public:
  static void onCompetition() {

  }
};

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
  /** 
  * Get the disc distance based off of colour camera sensor
  * Formula was created based off of Experimental values in logger pro
  *
  */
  public:
  double getDiscDistance() {
    int px = VisionSensor.largestObject.width;
    return 0;
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
      Shooting.setVelocity(shootSpeed, percent);
      while (Controller1.ButtonR1.pressing()) {
        /*
        * Need testing 
        */
        ShootingMotorA.spin(forward);
        ShootingMotorB.spin(reverse);
      };
      Shooting.stop();
    }

  public:
    static void manualIntake() {
      Intake.setVelocity(intakeSpeed, percent);
      while(Controller1.ButtonL1.pressing()) {
        Intake.spin(forward);
      }
      Intake.stop();
    }

  public:
    static void manualRoller() {
      while (Controller1.ButtonR2.pressing()) {
        Roller.spin(forward);
      }
      Roller.stop();
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

      /* 
  * Manual shooting of the crossbow, a wait function to 
  * check if the button is still being held
  */
    
  public:
    static void manualCrossbow() {
      wait(1, seconds);
      if (Controller1.ButtonY.pressing()==false) return;
      Crossbow.spinFor(forward, 90, degrees);
      // printf("Y Button executed\n");
    }

  /*
  * Adjust the speed of the shooting motors
  */
  public:
  static void increaseShootingSpeed() {
    Controller1.Screen.clearLine(3);
    printf("The shooting motor speed: %d\n", shootSpeed);
    if (shootSpeed == 100) {
      Controller1.Screen.print("Shooting Speed 100");
      return;
    }
    shootSpeed += 5;
    Controller1.Screen.print("Shooting Speed %d", shootSpeed);
  }

  public:
  static void decreaseShootingSpeed() {
    Controller1.Screen.clearLine(3);
    if (shootSpeed == 0) {
      Controller1.Screen.print("Shooting Speed 0");
      return;
    }
    shootSpeed -= 5;
    Controller1.Screen.print("Shooting Speed %d", shootSpeed);
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
  Controller1.ButtonR2.pressed(controls.manualRoller);
  Controller1.ButtonL1.pressed(controls.manualIntake);
  Controller1.ButtonL2.pressed(controls.manualTail);
  Controller1.ButtonUp.pressed(controls.increaseShootingSpeed);
  Controller1.ButtonDown.pressed(controls.decreaseShootingSpeed);
  Controller1.ButtonY.pressed(controls.manualCrossbow);
  }

void initModes() {
  AutonomousPeriod ap;
  competition Competition;
  Competition.autonomous(ap.onCompetition);
}

/** 
* Keep the thread alive
*/

void threadAlive() {
  while (true) {
    wait (1,seconds);
  }
}