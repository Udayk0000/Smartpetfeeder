#define BLYNK_TEMPLATE_ID "TMPL3KFK-rvzW"
#define BLYNK_TEMPLATE_NAME "Nodemcu8266servo"
#define BLYNK_AUTH_TOKEN "_sMRFitRhBiTvIl5GjLCtL3NaJMsrPlJ"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char ssid[] = "supreme net tf";
char pass[] = "atishay@123";
Servo food;
Servo water;
const int status=V2;
// Variables for tracking time
unsigned long lastButtonPress = 0;
unsigned long elapsedTime = 0;

// Blynk timer interval in milliseconds
BlynkTimer timer;

BLYNK_WRITE(V4){
  if(param.asInt()==1){
    elapsedTime = millis() - lastButtonPress;
    Blynk.virtualWrite(timeDisplayPin, String(elapsedTime / 1000) + " seconds ago");
  }
}

BLYNK_WRITE(V0){
  if(param.asInt()==1){
    food.write(0);
    delay(500);
    food.write(180);
    delay(2000);
    food.write(0);
    lastButtonPress = millis();
  }
}

BLYNK_WRITE(V1){
  if(param.asInt()==1){
    water.write(180);
    delay(500);
    water.write(0);
    delay(2000);
    water.write(180);
    lastButtonPress = millis(); 
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  food.attach(D6);
  water.attach(D7);

}

void loop()
{
  Blynk.run();
  timer.run();

  if(Serial.available()>0){
    char data=Serial.read();
    if(data=="1"){
      Blynk.virtualWrite(status,"pet is nearby!!!");
    }
    Else{
      Blynk.virtualWrite(status,"Waiting for pet.....");
    }
  }
  
}
