#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial ArduinoUno(3,2);
const int trigPin = 7;
const int echoPin = 8;
long duration;
int distance;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

byte animationFrames[4][8] = {
  { B11111, B00000, B00000, B00000, B11111, B10001, B01010, B00100 },
  { B11111, B00000, B00000, B00000, B11111, B11011, B10101, B00100 },
  { B11111, B00000, B00000, B00000, B11111, B11111, B11111, B00100 },
  { B11111, B00000, B00000, B00000, B11111, B11111, B11111, B00100 }
};

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
  lcd.begin();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(0, 0);
  lcd.print("Welcome!!!");
  lcd.setCursor(0, 1);
  lcd.print("Configuring.....");
  lcd.setCursor(0, 0);
  delay(8000);
  lcd.clear();
}

void loop() {

    lcd.clear();
    // Display pet feeder animation
    for (int i = 0; i < 4; i++) {
      lcd.createChar(0, animationFrames[i]);
      lcd.setCursor(7, 1);
      lcd.write((byte)0);
      lcd.createChar(0, animationFrames[i]);
      lcd.setCursor(8, 1);
      lcd.write((byte)0);
      lcd.setCursor(3, 0);
      lcd.print("Pet Feeder");
      delay(500);
      lcd.clear();
    }
    // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  if(distance<50){
  Serial.println("1");
  } 
  else{
    Serial.println("0");
  }
  
}