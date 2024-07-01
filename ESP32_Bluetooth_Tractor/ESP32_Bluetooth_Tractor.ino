#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>

Servo steeringServo;
int steeringPin=25;

//Right motor
int enableRightMotor=22; 
int rightMotorPin1=16;
int rightMotorPin2=17;
//Left motor
int enableLeftMotor=23;
int leftMotorPin1=18;
int leftMotorPin2=19;

#define MAX_MOTOR_SPEED 255

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));  
}

void setUpPinModes()
{
  steeringServo.attach(steeringPin); 

  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);

  //Set up PWM for speed
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel); 

  rotateMotor(0, 0);
  steeringServo.write(90);
}

void setup()
{
  setUpPinModes();
  Dabble.begin("MyBluetoothCar"); 
}

void loop()
{
  int rightMotorSpeed=0;
  int leftMotorSpeed=0;
  int steering = 90;
  Dabble.processInput();

  int xAxisValue = GamePad.getXaxisData();
  int yAxisValue = GamePad.getYaxisData();

  if (yAxisValue >= 3)
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  if (yAxisValue <= -3)
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (xAxisValue <= -3)
  {
    steering = 60;
  }

  if (xAxisValue >= 3)
  {
    steering = 120;
  }

  rotateMotor(rightMotorSpeed, leftMotorSpeed); 
  steeringServo.write(steering); 
}















