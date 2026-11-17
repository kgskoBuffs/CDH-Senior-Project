#include <Wire.h> //this is to include to the I2C library(might have to also download it?)

byte i2c_rcv;

unsigned long previousMillis = 0; 
const long deployment_time = 45; //milliseconds?

//push button stuff
int buttonPin = 4;
bool deployCommand = false;

//Gains
float Kp = 550;
float Ki = 275;

//Control Variables
float setPoint = ; //desired boom length
float integral = 0.0; //this is the integral accumulator, starts at 0(?)
float previousTime = 0.0; //this is used to get delta_T , starts at 0 

void setup() {
  // put your setup code here, to run once:
    Wire.begin(); //joins the I2C bus as the master
    i2c_rcv = 255; //arbitrary value

  //Pins
  pinMode(buttonPin, input); // 4 / push button / do we need to do 'INPUT_PULLUP' to use internal pull-down resistor
  pinMode(5, ); // rotary encoder? data
  pinMode(6, ); // rotary encoder? data
  pinMode(7, ); // rotary encoder? power

  pinMode(9, output); // motor driver / motor in1 / in1(pin9) high, in2(pin10) low for forward
  pinMode(10, output); // motor driver / motor in2

  pinMode(11, ); // magnetometer power / VCC
}

void loop() {
  // put your main code here, to run repeatedly:

  //push button start program
  if(digitalRead(buttonPin) == LOW) {
    delay(50);
    if(digitalRead(buttonPin) == LOW) {
      deployCommand = !deployCommand; //for toggling program
      while(digitalRead(buttonPin) == LOW); //waits for button release
    }
  }

  Wire.beginTransmission(); //fill in address later / tells the bus we are sending info to the slave device

  Wire.requestFrom(0x08, 1); //address and quantity of bytes
  if(Wire.available()) {
    i2c_rcv = Wire.read();
  }

  //motor forwards
  digitalWrite(9, high);
  digitalWrite(10, low);
  // control law
  // u = Kp + e + Ki * sum(error * delta_t)

  //time loop
  float currentTime = millis() / 1000.0; //1000(change value later)
  float dt = currentTime - previousTime;
  previousTime = currentTime;

  //get/calculate current length here ???
  float error = setPoint - currentLength; //need to get current length 

  integralPart += error * dt; //integral part

  float u = Kp * error + Ki * integralPart; //output of control 
  //how does the control output effect the deployment(change the power going to the motor?)

}
