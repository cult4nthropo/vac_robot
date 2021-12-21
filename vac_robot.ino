#include <stdlib.h>
#include <math.h>

// analog pins for sensors
constexpr int SENSOR_LEFT1 = 0;  // analogIn 0 for left sensor
constexpr int SENSOR_RIGHT1 = 1; // analogIn 1 for right sensor
constexpr int SENSOR_LEFT2 = 2;  // analogIn 2 for left sensor
constexpr int SENSOR_RIGHT2 = 3; // analogIn 3 for right sensor

constexpr int BATTERY = 4; // analogIn 4 for reading the battery

constexpr int LED = 13; // digital pin 13 for LED while testing

constexpr int FAN_MOTOR = 12; // digital pin 12 for fan motor over h bridge

// digital pins for motors
constexpr int MOTOR_LEFT1 = 9;
constexpr int MOTOR_LEFT2 = 6;

constexpr int MOTOR_RIGHT1 = 5;
constexpr int MOTOR_RIGHT2 = 3;

constexpr int BUMBER1 = 11; // digital pin 11 for the bumber2
constexpr int BUMBER2 = 10; // digital pin 10 for bumber2

// constants to define control values
constexpr float BATTERY_CHARGED = 12.68F; // check this in battery manual; voltage when battery fully charged

// max power for motors - depends on battery, check this
constexpr int MAX_POWER = 160; // depents on battery output 12V POWER_MAX = 170, 10V output MAX_POWER = 140
constexpr int MIN_POWER = 70;  // for 9V MIN_POWER = 128

// minimum distance for sensors
constexpr int MIN_DISTANCE = 30;

// begin of code, first setting the pinModes for in and output
void setup()
{
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

  // Initialize and setting data rate
  Serial.begin(9600);

  // small if else: if battery is full just turn fan on to avoid overloading of battery (I guess)
}

// functions
// read the distance and return it in cm
// adressing of sensors in the loop
float readSensor(const int sensor)
{
  float distance = pow(static_cast<float>(analogRead(sensor)), -0.857F); // messured distance is the base, -0,857 the exponent
  return distance * 167.9;
}

// function for motors to go forward
void moveForward(const int moveTime)
{
  analogWrite(MOTOR_LEFT1, MIN_POWER);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, MIN_POWER);
  analogWrite(MOTOR_RIGHT2, 0);
}

// function for motors to go backwards
void moveBackwards(const int moveTime)
{
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, MIN_POWER);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, MIN_POWER);
}

// function for motors to move left
void moveLeft(const int moveTime)
{
  analogWrite(MOTOR_LEFT1, MIN_POWER + 20);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, MIN_POWER);
}

void moveRight(const int moveTime)
{
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, MIN_POWER);
  analogWrite(MOTOR_RIGHT1, MIN_POWER + 20);
  analogWrite(MOTOR_RIGHT2, 0);
}

// stop all the motors
void stopMotors()
{
  analogWrite(MOTOR_LEFT1, 0);
  analogWrite(MOTOR_LEFT2, 0);
  analogWrite(MOTOR_RIGHT1, 0);
  analogWrite(MOTOR_RIGHT2, 0);
}

// function to read the battery state and returns it
float readBattery()
{
  const int readBATTERY = analogRead(BATTERY);
  return (((static_cast<float>(readBATTERY) * 4.9F) / 1000.0F) * BATTERY_CHARGED) / 5.0F; // honestly don't understand why, cause I don't know in which currency the arduino delivers its output
}

// function to turn everything of, if battery state is at min
bool batteryCritical()
{
  float batteryStatus = readBattery();
  const bool batteryControl = !(batteryStatus <= 11.1);
  return batteryControl;
}

void loop()
{
  // put your main code here, to run repeatedly:
  // set everything up, if battery is at max

  const auto doVacuuming
  {
    []
    {
      digitalWrite(FAN_MOTOR, HIGH);
      readSensor(SENSOR_LEFT1);
      readSensor(SENSOR_RIGHT1);
      readSensor(SENSOR_LEFT2);
      readSensor(SENSOR_RIGHT2);

      if ((readSensor(SENSOR_LEFT1) && readSensor(SENSOR_RIGHT1) && readSensor(SENSOR_LEFT2) && readSensor(SENSOR_RIGHT2) > MIN_DISTANCE))
      {
        moveForward(500); // moveTime in ms
      }
      else if (((readSensor(SENSOR_LEFT1) || readSensor(SENSOR_LEFT2)) < MIN_DISTANCE) && (readSensor(SENSOR_RIGHT1) && readSensor(SENSOR_RIGHT2)) > MIN_DISTANCE)
      {
        moveRight(150);
        moveForward(500);
      }
      else if (((readSensor(SENSOR_RIGHT1) || readSensor(SENSOR_RIGHT2)) < MIN_DISTANCE) && (readSensor(SENSOR_LEFT1) && readSensor(SENSOR_LEFT2)) > MIN_DISTANCE)
      {
        moveLeft(150);
        moveForward(300);
      }
      else
      {
        const int direction = rand() % 2; // should give random 0 or 1
        if (direction == 0)
        {
          moveBackwards(150);
          moveLeft(150);
          moveForward(500);
        }
        else
        {
          moveBackwards(150);
          moveRight(150);
          moveForward(500);
        }
      }
      batteryCritical(BATTERY); 
    }
  };

  while (!batteryCritical(BATTERY))
  {
    doVacuuming();
  }

  stopMotors();
  digitalWrite(FAN_MOTOR, LOW);
}
