// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  controllerOne = new frc::XboxController(0);

  leftOne = new TalonSRX(3);
  leftTwo = new TalonSRX(4);
  rightOne = new TalonSRX(1);
  rightTwo = new VictorSPX(2);

  arm = new TalonSRX(5);

  gripper = new frc::DoubleSolenoid(6, frc::PneumaticsModuleType::CTREPCM, 0, 1);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
//set left and right drivebase speeds, uses turnery operators for deadzones (similar to "if-else", condition || True ? False)
  double leftSpeed = (controllerOne->GetRightY() > 0.1 || controllerOne->GetRightY() < -0.1 ? controllerOne->GetRightY() : 0);
  double rightSpeed = (controllerOne->GetLeftY() > 0.1 || controllerOne->GetLeftY() < -0.1 ? controllerOne->GetLeftY() : 0);
//set our motors to the respective speeds ('-' to counter gearbox fighting)
  rightOne->Set(ControlMode::PercentOutput, -rightSpeed);
  rightTwo->Set(ControlMode::PercentOutput, rightSpeed);
  leftOne->Set(ControlMode::PercentOutput, -leftSpeed);
  leftTwo->Set(ControlMode::PercentOutput, leftSpeed);

//using both triggers (line for each) adjust speed value, second line will overwrite first if the right trigger is pulled, this gives upwards bias (for safety)
  double armSpeed = (controllerOne->GetLeftTriggerAxis() > 0.1 ? controllerOne->GetLeftTriggerAxis() : 0);
  armSpeed = (controllerOne->GetRightTriggerAxis() > 0.1 ? -controllerOne->GetRightTriggerAxis() : armSpeed);

  arm->Set(ControlMode::PercentOutput, armSpeed*0.4);

//checks if the bumper is pressed (no debounce code :/ ) if so actuate piston, else actuate out.
  if(controllerOne->GetRightBumper()){
    gripper->DoubleSolenoid::Set(frc::DoubleSolenoid::kForward);
  } else {
    gripper->DoubleSolenoid::Set(frc::DoubleSolenoid::kReverse);
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
