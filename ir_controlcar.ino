#include <IRremote.h>

float controlpwm = 0.00;
float kp = 8.00;
float ki = 0;
float kd = 20;
float error = 0.00;
float preerror = 0.00;
float errorsum = 0.00;
float desired = 20.00;
float actual = 0.00;

int TRIG = 5;
int ECHO = 4;
float timeduration;
float distance;
float distance_cm;

int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENA = 3;
int ENB = 10;

const int irpin = 11;
IRrecv receiver(irpin);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(irpin, INPUT);
  receiver.enableIRIn();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  if (receiver.decode(&results)) {
    ircontrol();
    receiver.resume();
  }
  actual = get_distance();
  preerror = error;
  error = desired - actual;
  errorsum = errorsum + error;
  errorsum = constrain(errorsum, -100 / ki, 100 / ki);
  controlpwm = (kp * error) + (ki * errorsum) + kd * (error - preerror);
  movePID(controlpwm);
  distance_cm = get_distance();
  Serial.print("distance:");
  Serial.println(distance_cm);
  Serial.print("error:");
  Serial.println(error);
}

float get_distance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  timeduration = pulseIn(ECHO, HIGH);
  distance = (timeduration / 2) * 0.034;
  return distance;
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void movePID(float speed) {
  int signpwm;
  if (speed >= 0) {
    signpwm = 1;
    speed = speed * 4;
  } else {
    signpwm = -1;
  }
  int magpwm = constrain(abs(speed), 0, 250);
  analogWrite(ENA, magpwm);
  analogWrite(ENB, magpwm);
  if (signpwm == -1) {
    forward();
  } else {
    reverse();
  }
}

void ircontrol() {
  switch (results.value) {
    case 0xFFE01F:
      desired += 2;
      break;
    case 0xFFA857:
      desired -= 2;
      break;
  }
}
