
#define MOTOR_R_1 8
#define MOTOR_R_2 9
#define MOTOR_L_1 10
#define MOTOR_L_2 11
const uint8_t SENSORS_PIN[] = { 5, 4, 3, 2};

const uint8_t maxspeed = 70;
int error = 0;

void setup() {
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // digitalWrite(MOTOR_R_1, LOW);
  // analogWrite(MOTOR_R_2, maxspeed);  
  // Serial.println("LOW");// put your main code here, to run repeatedly:
  // delay(3000);
  // digitalWrite(MOTOR_R_1, HIGH);
  // analogWrite(MOTOR_R_2, 10);
  // Serial.println("HIGH");
  // delay(3000);
  read_sensors();
  control_motor();
}

void read_sensors() {
  String sensorArray = "";
  for (auto sensorPin : SENSORS_PIN) {
    sensorArray += (char)(digitalRead(sensorPin) + 48);
  }

  Serial.println(sensorArray);

 if (sensorArray == "1000"){
   error = 3;
 }else if (sensorArray == "1110"){
   error = 2;
 } else if (sensorArray == "0100"){
   error = 1;
 } else if (sensorArray == "0110"){
   error = 0;
 }else if (sensorArray == "0010"){
   error = -1;
 }else if (sensorArray == "0111"){
   error = -2;
 }else if (sensorArray == "0001"){
   error = -3;
 }
  else if (sensorArray == "0000") {
    if (error < 0)
      error = -4;
    else if (error > 0)
      error = 4;
  } 
}

void control_motor() {
  int speedA = maxspeed - error*20;
  int speedB = maxspeed + error*20;
  if (error > 0){
    speedB = maxspeed + error * 10;
    speedA = maxspeed - error*20;
  }else {
    speedB = maxspeed + error * 20;
    speedA = maxspeed - error*10;
  }
  if (speedA < 0){
    motor_l_lui( - speedA);
  }else{
    motor_l_tien(speedA);
  }

  if (speedB < 0){
    motor_r_lui(- speedB);
  }else{
    motor_r_tien(speedB);
  }
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




