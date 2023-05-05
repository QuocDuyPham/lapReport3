// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
e
LiquidCrystal lcd(2,3,9,10,11,12);
const int pB = 4;
int buttonState;
int value = 0; // to store the time PB has been pressed
float x; // to convert the degree temperature to Farenhiet
int lastButtonState = HIGH;
float temperature=0; // to store the event temperature 





#define DHTPIN 8     // Digital pin connected to the DHT sensor 

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
// To create the degree sympol on lcd
byte customChar[8] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  //delayMS = sensor.min_delay / 1000;
  //initialize lcd display
  lcd.begin(16, 2);
  lcd.createChar(0,customChar);
  pinMode(pB, INPUT_PULLUP);
  

}

void loop() {
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
 

  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
temperature = event.temperature; 
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));

  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  
  }
   buttonState = digitalRead(pB); // Read the value from the PB
  if (buttonState == LOW && lastButtonState == HIGH) { // Check if button was just pressed
  delay(50);
  buttonState = digitalRead(pB);
 if (buttonState == LOW) {
   value++; 
 if (value > 3) {
   value = 1;
 x = (event.temperature*9/5)+32.0;
 }
 }
  }
  lastButtonState = buttonState;
  // use switch case to the lcd screen base on the value of PB 
    switch (value) {
     case 1:
     lcd.setCursor(0,0);
     lcd.print(F("Hum:"));
     lcd.print(event.relative_humidity);
     lcd.print(F("%"));
     lcd.print("  ");
     break ; 
     case 2:
     lcd.setCursor(0,0);
     lcd.print(F("Temp:"));
     lcd.print(temperature);
     lcd.write((byte)0);
     lcd.print(F("C"));
     lcd.print("  ");
     break ;
 
     case 3:
     lcd.setCursor(0,0);
     lcd.print(F("Far:"));
     lcd.print(x);
     lcd.write((byte)0);
     lcd.print(F("F"));
     lcd.print(" ");
   }
  }
