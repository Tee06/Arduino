#include <Servo.h>

#define MOTOR_L_1 8
#define MOTOR_L_2 10
#define MOTOR_R_1 12
#define MOTOR_R_2 11

Servo center;
Servo arm1;
Servo arm2;
Servo grip;
#define center_servo 9
#define arm1_servo 5
#define arm2_servo 6
#define grip_servo 3
int code;

float center_angle = 90;
float arm1_angle = 90;
float arm2_angle = 90;
float grip_angle = 90;

float roll_speed = 0.01;

bool isCenterIn = false;
bool isCenterDe = false;

bool isArm1In = false;
bool isArm1De = false;

bool isArm2In = false;
bool isArm2De = false;

bool isArmControl = false;
int maxspeed = 100;

void setup() {
  // put your setup code here, to run once:
  center.attach(center_servo);
  arm1.attach(arm1_servo);
  arm2.attach(arm2_servo);
  grip.attach(grip_servo);
  Serial.begin(9600);

  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);
  // myservo.write(0);
  //delay(2000);
  grip.write(90);
  center.write(90);
  arm1.write(90);
  arm2.write(90);
}



void loop() {

  if (Serial.available()) {
    code = Serial.read();
    Serial.println((char)code);
  }
  if (code == 'V') {
    isArmControl = true;
  } else if (code == 'v') {
    isArmControl = false;
  }
  if (isArmControl) {
    if (code == 'F') {
      stop_arm();
      isArm1De = true;  // di thang
    } else if (code == 'S' || code == 'w' || code == 'u') {
      stop_arm();
    } else if (code == 'B') {
      stop_arm();
      isArm1In = true;
    } else if (code == 'G') {
      stop_arm();
      isArm1In = true;
      isArm2In = true;
    } else if (code == 'I') {
      stop_arm();
      isArm1In = true;
      isArm2De = true;
    } else if (code == 'L') {
      stop_arm();
      isArm2In = true;
    } else if (code == 'R') {
      stop_arm();
      isArm2De = true;
    } else if (code == 'H') {
      stop_arm();
      isArm1De = true;
      isArm2In = true;
    } else if (code == 'J') {
      stop_arm();
      isArm1De = true;
      isArm2De = true;
    } else if (code == 'X') {
      grip.write(170);
    } else if (code == 'x') {
      grip.write(80);
    } else if (code == 'W') {
      stop();
      isCenterIn = true;
    } else if (code == 'U') {
      stop();
      isCenterDe = true;
    }
    servo_control();

  } else {
    if (code == 'F') {  // di thang
      forward();
    } else if (code == 'S') {
      stop();
    } else if (code == 'B') {
      backward();
    } else if (code == 'G') {
      forwardLeft();
    } else if (code == 'I') {
      forwardRight();
    } else if (code == 'L') {
      left();
    } else if (code == 'R') {
      right();
    } else if (code == 'H') {
      backwardLeft();
    } else if (code == 'J') {
      backwardRight();
    }
  }
}

void stop() {
  motor_l_tien(0);
  motor_r_tien(0);
}

void forward() {
  motor_l_tien(maxspeed);
  motor_r_tien(maxspeed);
}

void forwardLeft() {
  motor_l_tien(0);
  motor_r_tien(maxspeed);
}

void forwardRight() {
  motor_l_tien(maxspeed);
  motor_r_tien(0);
}

void backward() {
  motor_r_lui(maxspeed*3/4);
  motor_l_lui(maxspeed*3/4);
}

void backwardLeft() {
  motor_l_lui(maxspeed);
  motor_r_tien(0);
}

void backwardRight() {
  motor_l_lui(0);
  motor_r_tien(maxspeed);
}

void left() {
  motor_l_lui(maxspeed*3/4);
  motor_r_tien(maxspeed*3/4);
}
void right() {
  motor_r_lui(maxspeed*3/4);
  motor_l_tien(maxspeed*3/4);
}

void stop_arm() {
  isArm1In = false;
  isArm1De = false;
  isArm2In = false;
  isArm2De = false;
  isCenterIn = false;
  isCenterDe = false;
}

void servo_control() {
  if (isArm1In && arm1_angle + roll_speed < 180) {
    arm1_angle += roll_speed;
  }
  if (isArm1De && arm1_angle - roll_speed > 0) {
    arm1_angle -= roll_speed;
  }

  if (isArm2In && arm2_angle + roll_speed < 180) {
    arm2_angle += roll_speed;
  }
  if (isArm2De && arm1_angle - roll_speed > 0) {
    arm2_angle -= roll_speed;
  }

  if (isCenterIn && arm2_angle + roll_speed < 180) {
    center_angle += roll_speed;
  }
  if (isCenterDe && arm1_angle - roll_speed > 0) {
    center_angle -= roll_speed;
  }

  arm1.write(arm1_angle);
  arm2.write(arm2_angle);
  center.write(center_angle);
}

void motor_l_tien(int speed){
  digitalWrite(MOTOR_L_1, LOW);
  analogWrite(MOTOR_L_2, constrain(speed, 0, 255));  
}
void motor_l_lui(int speed){
  digitalWrite(MOTOR_L_1, HIGH);
  analogWrite(MOTOR_L_2, constrain(255 - speed, 0, 255));
  Serial.print("HIGH");
}
void motor_r_tien(int speed){
  digitalWrite(MOTOR_R_1, LOW);
  analogWrite(MOTOR_R_2, constrain(speed, 0, 255));  
}
void motor_r_lui(int speed){
  digitalWrite(MOTOR_R_1, HIGH);
  analogWrite(MOTOR_R_2, constrain(255-speed, 0, 255));
  Serial.print("HIGH");
}
