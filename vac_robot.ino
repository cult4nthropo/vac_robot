//digital pins motor

const int MOTOR_RIGHT1 = 3; //digital 3 motor left
const int MOTOR_RIGHT2 = 5; // digital 5 motor left
const int MOTOR_LEFT1 = 6; //digital 6 motor right
const int MOTOR_LEFT2 = 9;//digital 9 motor right

//digital pins bumber
const int BUMBER1 = 10; //digital 10 bumber 1
const int BUMBER2 = 11; //digital 11 bumber 2

//fan output
const int FAN = 12; //MosFet to fan

const int LED = 13; 

//analog sensors
const int SENSOR_LEFT = 0; //analog 0 //check where the other both sensor contacts come from
const int SENSOR_RIGHT = 1; //analog 1

const int BATTERY = 4; 

const float BATTERY_CHARGED;
const float BATTERY_LOW;
const float BATTERY_HIGH;
const int SENSOR_MIN = 30;

//variables
int bumberState = 0;
int counter = 0;
boolean control = true;


void setup() {
  // put your setup code here, to run once:
  //initialize outputs and inputs
  pinMode(MOTOR_RIGHT1, OUTPUT);
  pinMode(MOTOR_RIGHT2, OUTPUT);
  pinMode(MOTOR_LEFT1, OUTPUT);
  pinMode(MOTOR_LEFT2, OUTPUT);
  pinMode(FAN, OUTPUT);

  pinMode(SENSOR_LEFT, INPUT); //see sensor const: where it comes from determines, which pinMode it should have
  pinMode(SENSOR_RIGHT, INPUT);

  pinMode(BUMBER1, INPUT_PULLUP); //corrected. I thought just INPUT - try to understand PULLUP
  pinMode(BUMBER2, INPUT_PULLUP); //try to understand PULLUP

  pinMode(LED, OUTPUT);

  pinMode(BATTERY, INPUT);
  
  blinkLED(5,1);
  
  // wait 5s and initialize fan, if voltage ok
  if(readBattery(BATTERY)>12.1){ //doublecheck value
    digitalWrite(FAN, HIGH);
    delay(1000);
    else:
    //nothing
  }
  
}

//functions

def blinkLED(){
  
}

def sensorDistance(){

}

def bothMotors(){

}

def leftMotor(){

}

def rightMotor(){

}

def backwardMotor(){

}

def stopMotor(){

}

def readBattery(){

}

def batteryControl(){

}

void loop() {
  // put your main code here, to run repeatedly:
  //set everything up, if battery is at max
  

}
