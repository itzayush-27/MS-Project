#include<chrono>
using namespace std ::chrono;
// IR Sensor pins
const int leftSensorPin = 12;
const int rightSensorPin = 13;

// Motor pins
#define M1_plus 2
#define M1_minus 3
#define M1_pwm 9
#define M2_plus 4
#define M2_minus 5
#define M2_pwm 10


// Sensor threshold values
const int threshold = 500;
int speed = 80;
void setup() {
  int i;
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  //Motor control pins in output mode
  pinMode(M1_pwm, OUTPUT);
  pinMode(M1_plus, OUTPUT);
  pinMode(M1_minus, OUTPUT);
  pinMode(M2_pwm, OUTPUT);
  pinMode(M2_plus, OUTPUT);
  pinMode(M2_minus, OUTPUT);
  //At power on, all motors should be OFF
  idle();
  //For potential debugging
  //Serial.begin(9600);
}
void idle(void) {
  digitalWrite(M1_plus, LOW);
  digitalWrite(M1_minus, LOW);
  digitalWrite(M1_pwm, LOW);
  digitalWrite(M2_plus, LOW);
  digitalWrite(M2_minus, LOW);
  digitalWrite(M2_pwm, LOW);
}
void loop() {
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // Check sensor readings and adjust motors accordingly
  if (leftSensorValue == LOW && rightSensorValue == LOW) {
    // Both sensors detect the line, move forward
    moveForward();
  } else if (leftSensorValue == HIGH && rightSensorValue == LOW) {
    // Only left sensor detects the line, turn right
    turnBotRight();
  } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
    // Only right sensor detects the line, turn left
    turnBotLeft();
  } else {
    // Both sensors do not detect the line, stop
    stopBot();
    delay(1000);
    rotate();
    //delay(1000);

  }
}

float speedsense(){
  auto start = high_resolution_clock::now();
  bool sensorstate = digitalRead();
  bool val = sensorstate;
  int i=0;
  while(true){
    sensorstate = digitalRead();
    if(sensorstate != val){
      i = 1;
    }
    if(i==1 && sensorstate == val){
      break;
    }
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(start-stop);
  return float(2*3.14/duration.count()); 
}


void moveForward() {
  // Motor 1
  digitalWrite(M1_plus, HIGH);
  digitalWrite(M1_minus, LOW̥);
  analogWrite(M1_pwm, speed);
  
  // Motor 2
  digitalWrite(M2_plus, HIGH);
  digitalWrite(M2_minus, LOW);
  analogWrite(M2_pwm, speed);

}

void stopBot() {
  // Motor 1
  digitalWrite(M1_plus, LOW);
  digitalWrite(M1_minus, LOW);
  analogWrite(M1_pwm, speed);
  
  // Motor 2
  digitalWrite(M2_plus, LOW);
  digitalWrite(M2_minus, LOW);
  analogWrite(M2_pwm, speed);
}

void reverseBot() {
 // Motor 1
  digitalWrite(M1_plus, LOW);
  digitalWrite(M1_minus, HIGH);
  analogWrite(M1_pwm, speed);
  
  // Motor 2
  digitalWrite(M2_plus, LOW);
  digitalWrite(M2_minus, HIGH);
  analogWrite(M1_pwm, speed);
}

void turnBotLeft() {
  // Motor 1
  digitalWrite(M1_plus, LOW);
  digitalWrite(M1_minus, LOW);
  analogWrite(M1_pwm, speed);
  
  // Motor 2
  digitalWrite(M2_plus, HIGH);
  digitalWrite(M2_minus, LOW);
  analogWrite(M2_pwm, speed);
  
}
void turnBotRight() {
  // Motor 1
  digitalWrite(M1_plus, HIGH);
  digitalWrite(M1_minus, LOW);
  analogWrite(M1_pwm, speed);
  
  
  // Motor 2
  digitalWrite(M2_plus, LOW);
  digitalWrite(M2_minus, LOW);
  analogWrite(M2_pwm, speed);
  
}
void rotate() {
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);
  while (leftSensorValue < threshold && rightSensorValue < threshold) {
    // Motor 1
  digitalWrite(M1_plus, HIGH);
  digitalWrite(M1_minus, LOW);
  analogWrite(M1_pwm, speed);
  
  
  // Motor 2
  digitalWrite(M2_plus, LOW);
  digitalWrite(M2_minus, HIGH);
  analogWrite(M2_pwm, speed);
  }

  speed = 150;
}
  


