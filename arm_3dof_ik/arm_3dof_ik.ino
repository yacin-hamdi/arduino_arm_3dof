#include <Servo.h>   

// Create four Servo object for each joint
Servo base, joint_1, joint_2, gripper;

double pi = 3.14159265;

// Declare potentiometers pins
int pot_base = A0;
int pot_joint_1 = A1;
int pot_joint_2 = A2;
int pot_gripper = A3;

double x = 100;
double y = 0;
double z = 30;

void setup()
{
  // Attachs the Servo pins to each servo object
  base.attach(11, 460, 2400);
  joint_1.attach(9, 460, 2400);
  joint_2.attach(10, 460, 2400);
  gripper.attach(8, 544, 2400);
  
  // Start the Serial
  Serial.begin(9600);
//  TIMSK0=0;
    
}

void loop(void)
{
//for (x=55; x<=130; x++) {
//  calculate_pos(x,y,z);
//  delay(1);
//}
//
//for (x=130; x>55; x--) {
//  calculate_pos(x,y,z);
//  delay(1);
//}

  x = map(analogRead(pot_joint_1), 0, 1023, 10, 120);
  calculate_pos(x,y,z);

  y = map(analogRead(pot_joint_2), 0, 1023, 10, 120);
  calculate_pos(x,y,z);

  z = map(analogRead(pot_base), 0, 1023, 0, 90);
  calculate_pos(x,y,z);


//for (y=0; y<=130; x++) {
//  calculate_pos(x,y,z);
//  delay(10);
//}
//
//for (x=130; x>0; x--) {
//  calculate_pos(x,y,z);
//  delay(10);
//}

  // Read the value of potentiometer and scale it between low_angle and high_angle
  
  
}

int angle_to_ms(int angle){
  double val = 460.0 + (((2400.0 - 460.0) / 180.0) * angle);
  return (int)val;
}

void move_to(int base_angle, int joint_1_angle, int joint_2_angle, int gripper_angle){
  base.writeMicroseconds(angle_to_ms(base_angle));
  joint_1.writeMicroseconds(angle_to_ms(joint_1_angle));
  joint_2.writeMicroseconds(angle_to_ms(joint_2_angle));
  gripper.writeMicroseconds(angle_to_ms(gripper_angle));

//  base.write(base_angle);
//  joint_1.write(joint_1_angle);
//  joint_2.write(joint_2_angle);
//  gripper.write(gripper_angle);
}

void calculate_pos(double x, double y, double z){
//  float b = atan2(y, x) * (180 / pi);
//  float l = sqrt(x*x + y*y);
//  float h = sqrt(l*l + z*z);
//  float theta = acos(h/2/80) * (180 / pi);
//  float phi = atan(z/l) * (180 / pi);
//  float a1 = phi + theta;
//  float a2 = phi - theta ;
//  if(a2 < 0) a2 += 180;
//double a2 = acos((x*x + y*y - 80*80 - 80*80) / (2 * 80 * 80));
//double a1 = atan(y/x) - atan((80 * sin(a2)) / (80 + 80*cos(a2)));

double a1 = atan2(y, x);
double r = sqrt(x*x + y*y);
double theta = 2 * acos((r/2)/75);
double a2 = a1 - theta;

a1 = a1 * (180/pi);
a2 = a2 * (180/pi);

a1 += 90;
a2 += 180;









  Serial.println("join1: "+String(a1)+", joint2: "+String(a2)+", x: "+String(x)+", y: "+String(y));

  move_to(0, a1, a2, 0);
}
