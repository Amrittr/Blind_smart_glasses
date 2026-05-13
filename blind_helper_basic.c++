#define TRIG_FRONT 18
#define ECHO_FRONT 19
#define TRIG_LEFT 21
#define ECHO_LEFT 22
#define TRIG_RIGHT 23
#define ECHO_RIGHT 27

#define MOTOR_LEFT 25
#define MOTOR_RIGHT 26

#define THRESHOLD 5

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
}

float getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  float f = getDistance(TRIG_FRONT, ECHO_FRONT);
  float l = getDistance(TRIG_LEFT, ECHO_LEFT);
  float r = getDistance(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("F: "); Serial.print(f);
  Serial.print(" L: "); Serial.print(l);
  Serial.print(" R: "); Serial.println(r);

  digitalWrite(MOTOR_LEFT, LOW);
  digitalWrite(MOTOR_RIGHT, LOW);

  if (f <= THRESHOLD && f > 0) {
    digitalWrite(MOTOR_LEFT, HIGH);
    digitalWrite(MOTOR_RIGHT, HIGH);
  }
  else if (l <= THRESHOLD && l > 0) {
    digitalWrite(MOTOR_LEFT, HIGH);
  }
  else if (r <= THRESHOLD && r > 0) {
    digitalWrite(MOTOR_RIGHT, HIGH);
  }

  delay(200);
}
