#include <QTRSensors.h>

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             7  // emitter is controlled by digital pin 2

#define MIN_SPEED 20
#define MAX_SPEED 255

#define SOFT_TURN 60
#define MEDIUM_TURN 160
#define INSTANT_TURN 255

//#define DEBUG;

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  15, 14, 13, 12, 11, 10, 9, 8
  //8, 9, 10, 11, 12, 13, 14, 15
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int maxValues[NUM_SENSORS];

const int PWM_A   = 3;
const int DIR_A   = 12;
const int BRAKE_A = 9;
const int SNS_A   = A0;

const int PWM_B   = 11;
const int DIR_B   = 13;
const int BRAKE_B = 8;
const int SNS_B   = A1;

// speed of left and right wheel
int left_speed = 255;
int right_speed = 255;

static bool IsBrake;

void set_speed(int _speed, int motor);
void go_forward();
void turn_left();
void turn_right();
void go_backward();
void brake();
void calibrate_qtra();

void turn_right_instant_and_slow();
void turn_right_instant();
void turn_right_softly();

void turn_left_instant_and_slow();
void turn_left_instant();
void turn_left_softly();

void start_drive() {
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(BRAKE_B, LOW);

  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
  digitalWrite(DIR_B, HIGH);

//  set_speed(right_speed, PWM_A);
//  set_speed(left_speed, PWM_B);
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_SENSORS; i++) {
    maxValues[i] = 0;
  }

  calibrate_qtra();
  // print the calibration maximum values measured when emitters were on

#ifdef DEBUG
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(maxValues[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println("Koniec kalibracji");
  Serial.println();
#endif

  delay(3000);

  // Configure DC Motors output
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A

  pinMode(BRAKE_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);

  IsBrake = false;
  Serial.println("Uruchomienie silników");
  start_drive();
  Serial.println("BEGIN");
  

}

void loop() {

  // read all sensors
  qtra.read(sensorValues);
  // for each sensor
  #ifdef DEBUG
    for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensorValues[i] > maxValues[i]) {
     Serial.print ("black ");
    }
    Serial.print(sensorValues[i]); // comment it later
    Serial.print('\t');
    }
  Serial.println();
  #endif
  if (IsBrake == true) {
    unbrake();
  }
    else if (sensorValues[7] > maxValues[7]) {
      #ifdef DEBUG
      Serial.println("LEFT_INSTANT");
      #endif
      brake_one(PWM_B);
        turn_left_instant_and_slow();
    }
    else if (sensorValues[6] > maxValues[6]) {
         #ifdef DEBUG
        Serial.println("LEFT_MEDIUM");
        #endif
        turn_left_instant();
    }
    else if (sensorValues[5] > maxValues[5]) {
         #ifdef DEBUG
        Serial.println("LEFT_SOFT");
        #endif
        turn_left_softly();
    }
    else if (sensorValues[0] > maxValues[0]) {
         #ifdef DEBUG
        Serial.println("RIGHT_INSTANT");
        #endif
        brake_one(PWM_A);
        turn_right_instant_and_slow();
    }
    else if (sensorValues[1] > maxValues[1]) {
        #ifdef DEBUG
        Serial.println("RIGHT_MEDIUM");
        #endif
        turn_right_instant();
    }
    else if (sensorValues[2] > maxValues[2]) {
         #ifdef DEBUG
        Serial.println("RIGHT_SOFT");
        #endif
        turn_right_softly();
    }
    else {//if ((sensorValues[3] > maxValues[3]) || (sensorValues[4] > maxValues[4])) {
        #ifdef DEBUG
        Serial.println("GO_FORWARD");
        #endif     
      go_forward();
    }
}

// calibrate sensors. Compute maximum values in every sensor's. (I made it like this because (unfortunately), my sensors are askew. :(
void calibrate_qtra() {
  for (int i = 0; i < 8; i++) {
    qtra.read(sensorValues);
    for (int j = 0; j < NUM_SENSORS; j++) {
      if (sensorValues[j] > maxValues[j]) {
        maxValues[j] = sensorValues[j];
        if (j == 0 || j == 7) {
          maxValues[j] *= 3;  
        }
        else if (j == 1) {
          maxValues[j] *= 3;          
        }
        else if (j == 2 || j == 6) {
          maxValues[j] *= 6;          
        }
        else {
          maxValues[j] *= 7; 
        }
      }
    }
    delay(400);
  }
}


void set_speed(int _speed, int motor) {
  analogWrite(motor, _speed);     // Set the speed of the motor, 255 is the maximum value
}

void go_forward() {
  set_speed(right_speed, PWM_A);
  set_speed(left_speed, PWM_B);
}

void turn_left_softly() {
  set_speed(left_speed - SOFT_TURN, PWM_B);
  set_speed(right_speed, PWM_A);
}

void turn_left_instant() {
  set_speed(left_speed - MEDIUM_TURN, PWM_B);
  set_speed(right_speed, PWM_A);
}

void turn_left_instant_and_slow() {
  
  set_speed(left_speed - INSTANT_TURN, PWM_B);
  set_speed(right_speed, PWM_A);
}

void turn_right_softly() {
  set_speed(left_speed, PWM_B);
  set_speed(right_speed - SOFT_TURN, PWM_A);  
}

void turn_right_instant() {
  set_speed(right_speed - MEDIUM_TURN, PWM_A);
  set_speed(left_speed, PWM_B);
}
void turn_right_instant_and_slow() {
   set_speed(left_speed, PWM_B);
   set_speed(right_speed - INSTANT_TURN, PWM_A);
}

void go_backward() {
  digitalWrite(DIR_A, LOW);
  digitalWrite(DIR_B, LOW);

  set_speed(255, PWM_A);
  set_speed(255, PWM_B);
}

void brake_one(int motor) {
  if (motor == PWM_A) {
    digitalWrite(BRAKE_A, HIGH);  // setting br
  }
  else {
    digitalWrite(BRAKE_B, HIGH);  // setting br
  }
  IsBrake = true;
}

void unbrake() {
    digitalWrite(BRAKE_A, LOW);  // setting br
    digitalWrite(BRAKE_B, LOW);  // setting br
    IsBrake = false;
}
void brake() {
  set_speed(0, PWM_A);
  set_speed(0, PWM_B);
}



