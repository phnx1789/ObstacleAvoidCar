//--------------------------------------------------- Attaching libraries
#include <Ultrasonic.h>
#include <Servo.h>


//--------------------------------------------------- Attaching motors's pins
const int LeftMotorForward = 8;
const int LeftMotorBackward = 9;
const int RightMotorForward = 10;
const int RightMotorBackward = 11;

//--------------------------------------------------- Initializing servo and sonar
int distMap[6];
int distance;
Ultrasonic sonar(12, 13);
Servo servo;

void setup() {
  Serial.begin(9600);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo.attach(7);
  servo.write(90);
}

//--------------------------------------------------- Scannig funtion
int scanAhead() {
  for (int pos = 180; pos >= 30; pos -= 1) {

    servo.write(pos);
    delay(18);

    if (pos % 30 == 0) {
      distMap[pos / 30 - 1] = sonar.read();
      Serial.print(distMap[pos / 30 - 1]);
      Serial.print(" ");
    }
  }
  Serial.println("");
  servo.write(90);
  return distMap;
}

//--------------------------------------------------- Moving functions
void stop(){
  digitalWrite(LeftMotorForward, 0);
  digitalWrite(RightMotorForward, 0);

  digitalWrite(LeftMotorBackward, 0);
  digitalWrite(RightMotorBackward, 0);

  Serial.println("Stopped");
}

void goForward(){
  digitalWrite(LeftMotorForward, 1);
  digitalWrite(RightMotorForward, 1);

  digitalWrite(LeftMotorBackward, 0);
  digitalWrite(RightMotorBackward, 0);

  Serial.println("Go forward");
}

void goBackward(){
  digitalWrite(LeftMotorForward, 0);
  digitalWrite(RightMotorForward, 0);

  digitalWrite(LeftMotorBackward, 1);
  digitalWrite(RightMotorBackward, 1);

  Serial.println("Go backward");
}

void turnLeft(){
  digitalWrite(LeftMotorForward, 0);
  digitalWrite(LeftMotorBackward, 1);

  digitalWrite(RightMotorForward, 1);
  digitalWrite(RightMotorBackward, 0);

  Serial.println("Turned left");
  
  delay(400);
  stop();

}

void turnRight(){
  digitalWrite(LeftMotorForward, 1);
  digitalWrite(LeftMotorBackward, 0);

  digitalWrite(RightMotorForward, 0);
  digitalWrite(RightMotorBackward, 1);

  Serial.println("Turned right");

  delay(400);
  stop();
}



void loop() {
//---------------------------------------------- Debug functionality
  if (Serial.available()) {
    int data = Serial.parseInt();

    switch (data) {
      case 1: scanAhead();
        break;
      
      case 2: stop();
        break;
      
      case 8: goForward();
        break;  
      
      case 4: turnLeft();
        break;
      
      case 5: goBackward();
        break;  

      case 6: turnRight();
        break;  

      default:
        break;
    }
  }

  //----------------------------------------------- Main cycle
  
  distance = sonar.read();

  if (distance < 20) {
    stop();
    delay(20);
    goBackward();
    delay(400);
    stop();
    scanAhead();

  }
  else {
    goForward();
  } 
}



//  int distanceRight = 0;
//  int distanceLeft = 0;
//  delay(50);
//
//  if (distance <= 20){
//    moveStop();
//    delay(300);
//    moveBackward();
//    delay(400);
//    moveStop();
//    delay(300);
//    distanceRight = lookRight();
//    delay(300);
//    distanceLeft = lookLeft();
//    delay(300);
//
//    if (distance >= distanceLeft){
//      turnRight();
//      moveStop();
//    }
//    else{
//      turnLeft();
//      moveStop();
//    }
//  }
//  else{
//    moveForward();
//  }
//    distance = readPing();
//}
//
//int lookRight(){
//  servo_motor.write(50);
//  delay(500);
//  int distance = readPing();
//  delay(100);
//  servo_motor.write(115);
//  return distance;
//}
//
//int lookLeft(){
//  servo_motor.write(170);
//  delay(500);
//  int distance = readPing();
//  delay(100);
//  servo_motor.write(115);
//  return distance;
//  delay(100);
//}
//
//int readPing(){
//  delay(70);
//  int cm = sonar.ping_cm();
//  if (cm==0){
//    cm=250;
//  }
//  return cm;
//}
//
//void moveStop(){
//
//  digitalWrite(RightMotorForward, LOW);
//  digitalWrite(LeftMotorForward, LOW);
//  digitalWrite(RightMotorBackward, LOW);
//  digitalWrite(LeftMotorBackward, LOW);
//}
//
//void moveForward(){
//
//  if(!goesForward){
//
//    goesForward=true;
//
//    digitalWrite(LeftMotorForward, HIGH);
//    digitalWrite(RightMotorForward, HIGH);
//
//    digitalWrite(LeftMotorBackward, LOW);
//    digitalWrite(RightMotorBackward, LOW);
//  }
//}
//
//void moveBackward(){
//
//  goesForward=false;
//
//  digitalWrite(LeftMotorBackward, HIGH);
//  digitalWrite(RightMotorBackward, HIGH);
//
//  digitalWrite(LeftMotorForward, LOW);
//  digitalWrite(RightMotorForward, LOW);
//
//}
//
//void turnRight(){
//
//  digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(RightMotorBackward, HIGH);
//
//  digitalWrite(LeftMotorBackward, LOW);
//  digitalWrite(RightMotorForward, LOW);
//
//  delay(500);
//
//  digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(RightMotorForward, HIGH);
//
//  digitalWrite(LeftMotorBackward, LOW);
//  digitalWrite(RightMotorBackward, LOW);
//
//
//
//}
//
//void turnLeft(){
//
//  digitalWrite(LeftMotorBackward, HIGH);
//  digitalWrite(RightMotorForward, HIGH);
//
//  digitalWrite(LeftMotorForward, LOW);
//  digitalWrite(RightMotorBackward, LOW);
//
//  delay(500);
//
//  digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(RightMotorForward, HIGH);
//
//  digitalWrite(LeftMotorBackward, LOW);
//  digitalWrite(RightMotorBackward, LOW);
//}
