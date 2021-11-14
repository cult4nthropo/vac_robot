

//analog pins for sensors
const int SENSOR_LEFT1 = 0; //analogIn 0 for left sensor
const int SENSOR_RIGHT1 = 1; //analogIn 1 for right sensor
const int SENSOR_LEFT2 = 2; //analogIn 2 for left sensor
const int SENSOR_RIGHT2 = 3; //analogIn 3 for right sensor

const int BATTERY = 4; //analogIn 4 for reading the battery

const int LED = 13; //digital pin 13 for LED while testing

const int FAN_MOTOR = 12; //digital pin 12 for fan motor over h bridge

//digital pins for motors
const int MOTOR_LEFT1 = 9;
const int MOTOR_LEFT2 = 6;

const int MOTOR_RIGHT1 = 5;
const int MOTOR_RIGHT2 = 3;

const int BUMBER1 = 11; //digital pin 11 for the bumber2
const int BUMBER2 = 10; //digital pin 10 for bumber2

//constants to define control values
const float BATTERY_CHARGED = 12.68; //check this in battery manual; voltage when battery fully charged

//max power for motors - depends on battery, check this
const int MAX_POWER = 160; //depents on battery output 12V POWER_MAX = 170, 10V output MAX_POWER = 140
const int MIN_POWER = 70; //for 9V MIN_POWER = 128
//minimum distance for sensors
const int MIN_DISTANCE = 30;

//variables
int bumberState = 0; //to read the push button status
boolean batteryControl = true;
int counter = 0; //avoids infinite loop

//begin of code, first setting the pinModes for in and output
void setup() {
pinMode(FAN_MOTOR, OUTPUT);
pinMode(MOTOR_LEFT1, OUTPUT);
pinMode(MOTOR_LEFT2, OUTPUT);
pinMode(MOTOR_RIGHT1, OUTPUT);
pinMode(MOTOR_RIGHT2, OUTPUT);

pinMode(SENSOR_LEFT1, INPUT);
pinMode(SENSOR_LEFT2, INPUT);
pinMode(SENSOR_RIGHT1, INPUT);
pinMode(SENSOR_RIGHT2, INPUT);

pinMode(BUMBER1, INPUT_PULLUP);
pinMode(BUMBER2, INPUT_PULLUP);

pinMode(BATTERY, INPUT);

//Initialize and setting data rate
Serial.begin(9600);

// small if else: if battery is full just turn fan on to avoid overloading of battery (I guess) 
}

//functions
//read the distance and return it in cm
//adressing of sensors in the loop
double readSensor (int sensor){
  double distance = pow(analogRead(sensor), -0.857); //messured distance is the base, -0,857 the exponent
  return (distance * 167.9);
  
  }

//function for motors to go forward
void moveForward(int moveTime){
  analogWrite(MOTOR_LEFT1, MIN_POWER);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, MIN_POWER);
  analogWrite(MOTOR_RIGHT2, 0);
  }

//function for motors to go backwards
void moveBackwards(int moveTime){
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, MIN_POWER);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, MIN_POWER);
  }

//function for motors to move left
void moveLeft(int moveTime){
  analogWrite(MOTOR_LEFT1, MIN_POWER + 20);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, MIN_POWER);
}

void moveRight(int moveTime){
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, MIN_POWER);
  analogWrite(MOTOR_RIGHT1, MIN_POWER + 20);
  analogWrite(MOTOR_RIGHT2, 0);
  }

//stop all the motors
void stopMotors() {
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, 0);
  }
  
//function to read the battery state and returns it
float readBattery(int BATTERY){
  int readBATTERY;
  float voltage;
  readBATTERY = analogRead(BATTERY);
  voltage = (((readBATTERY * 4.9) / 1000) * BATTERY_CHARGED) / 5; //honestly don't understand why, cause I don't know in which currency the arduino delivers its output
  return voltage;
  }

//function to turn everything of, if battery state is at min
void batteryCritical(int BATTERY) {
  float batteryStatus;
  batteryStatus = readBattery(BATTERY);
  if(batteryStatus <= 11.1){
    batteryControl = false;
    }
   else{
    //shouldn't there be anything?? something like continue?
    }
  }
  
void loop() {
  // put your main code here, to run repeatedly:
  //set everything up, if battery is at max
  

}
