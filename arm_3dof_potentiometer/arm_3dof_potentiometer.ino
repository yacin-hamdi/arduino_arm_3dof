#include <Servo.h>   

// Create four Servo object for each joint
Servo base, joint_1, joint_2, gripper;

// Declare potentiometers pins
int pot_base = A0;
int pot_joint_1 = A1;
int pot_joint_2 = A2;
int pot_gripper = A3;

void setup()
{
  // Attachs the Servo pins to each servo object
  base.attach(8, 460, 2400);
  joint_1.attach(9, 460, 2400);
  joint_2.attach(10, 460, 2400);
  gripper.attach(11, 460, 2400);
  
  // Start the Serial
  Serial.begin(9600);
//  TIMSK0=0;
    
}

void loop(void)
{

  // move joints and get the each joint angle
  int base_val = move_joint(pot_base, base, 0, 180);
  int joint_1_val = move_joint(pot_joint_1, joint_1, -20, 120);
  int joint_2_val = move_joint(pot_joint_2, joint_2, 0, 90);
  int gripper_val = move_joint(pot_gripper, gripper, 0, 180);

  // Print each joint angle
  Serial.println("base:"+String(base_val)
                +", joint_1:"+String(joint_1_val)
                +", joint_2:"+String(joint_2_val)
                +", gripper:"+String(gripper_val));
}

int angle_to_ms(int angle){
  double val =256.0 + 544.0 + (((2400.0 - 544.0) / 180.0) * angle);
  return (int)val;
}

int move_joint(int pot, Servo &servo, int low_angle, int high_angle){

  // Read the value of potentiometer and scale it between low_angle and high_angle
  int angle = map(analogRead(pot), 0, 1023, low_angle, high_angle);
  int ms = angle_to_ms(angle);
  // sets the position of the servo 
  servo.writeMicroseconds(ms);
  delay(10);
  
  // Returns the scaled value
  return angle;
}
