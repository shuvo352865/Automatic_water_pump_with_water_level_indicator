#define BLYNK_TEMPLATE_ID "TMPLsIRSWk4m"
#define BLYNK_DEVICE_NAME "Water tank monitor and control"
#define BLYNK_AUTH_TOKEN "ux3xaeQKfr2-hPLOp3md4YIJaQOUSyxu"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trig D5   // Trig pin
#define echo D6 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "shahadat";
char pass[] = "12341234";
int depth =8;
BlynkTimer timer;
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, waterlevel);
}
void waterlevel()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  long level= depth-cm;
  if (level<0)
  level=0;
  level = map(level,0,depth-3,0,100);
  Blynk.virtualWrite(V0, level);
}
BLYNK_WRITE(V1) {
  digitalWrite(D0, param.asInt());
}
void loop()
{
  Blynk.run();
  timer.run();
  }
