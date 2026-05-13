#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

String account_sid = "YOUR_SID";
String auth_token  = "YOUR_TOKEN";

String from_number = "+16207027130";
String to_number   = "+91XXXXXXXXXX";

#define SOS_PIN 14
#define TRIG_FRONT 18
#define ECHO_FRONT 19
#define TRIG_LEFT 21
#define ECHO_LEFT 22
#define TRIG_RIGHT 23
#define ECHO_RIGHT 27
#define MOTOR_LEFT 25
#define MOTOR_RIGHT 26
#define THRESHOLD 5

bool sent = false;

void sendSMS() {
  HTTPClient http;

  String url = "https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json";
  http.begin(url);

  http.setAuthorization(account_sid.c_str(), auth_token.c_str());
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String data = "To=" + to_number +
                "&From=" + from_number +
                "&Body=SOS Alert! Need help immediately.";

  int code = http.POST(data);
  Serial.println(code);

  http.end();
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
  pinMode(SOS_PIN, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
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

  if (digitalRead(SOS_PIN) == HIGH && !sent) {
    sendSMS();
    sent = true;
  }
  if (digitalRead(SOS_PIN) == LOW) {
    sent = false;
  }

  delay(200);
}
