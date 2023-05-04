#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,9,10,11,12);
const int pB = 4;
int buttonState;
int value = 0;
float x;
int lastButtonState = HIGH;
float temperature=0;
float duration, distance;
float soundsp= 0;
float soundcm= 0;
#define trigPin 6   // This sends the trigger signal
#define echoPin 7 // This receives the echo signal




#define DHTPIN 8     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

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
  pinMode(trigPin, OUTPUT);    // Assign trigPin as OUTPUT
pinMode(echoPin, INPUT);     // Assign echoPin as Input

}

void loop() {
  // Delay between measurements.
  //delay(delayMS);
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
  
digitalWrite(trigPin, LOW); // Sets the trigger pin (connected to the ultrasonic sensor) to LOW
delayMicroseconds(2);       // To ensure trigger pin has settle down, put delay
digitalWrite(trigPin, HIGH); // Set the trigger pin to HIGH, which sends a 10-microsecond pulse to the ultrasonic sensor.
delayMicroseconds(20);     // Recommended minimum time between the trigger signal and the start of the echo pulse
digitalWrite(trigPin, LOW); // Set the trigger pin back to LOW to complete the trigger signal.

//measure the duration of the echo pulse and calculate the distance 
//based on the duration and the speed of sound
duration = pulseIn(echoPin, HIGH);
distance = (duration /2 ) * 0.0343;

// Print the distance on the serial monitor
Serial.print("Distance: ");
/*If the distance is out of range (less than 2cm or more than 400cm), 
it prints "Out of Range" instead of the distance*/
if (distance >= 400 || distance <= 2) {
  Serial.println("Out od Range");
} else {
  Serial.print(distance);
  Serial.println(" cm");
      // Calculate the Speed of Sound in M/S
    soundsp = 331.4 + (0.606 * temperature) + (0.0124 * event.relative_humidity);
    
    // Convert to cm/ms
    
    soundcm = soundsp / 10000;
}
  }
   buttonState = digitalRead(pB);
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
    switch (value) {
     case 1:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(F("Hum:"));
     lcd.print(event.relative_humidity);
     lcd.print(F("%"));
     lcd.print("  ");
     lcd.setCursor(0,1);
     lcd.print(F("Temp:"));
     lcd.print(temperature);
     lcd.write((byte)0);
     lcd.print(F("C"));
     lcd.print("  ");
     break ; 
     case 2:
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
if (distance >= 400 || distance <= 2) {
  lcd.setCursor(0,1);
  lcd.print("Out of Range");
} else {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
     lcd.setCursor(0,1);
     lcd.print(F("Far:"));
     lcd.print(x);
     lcd.write((byte)0);
     lcd.print(F("F"));
     lcd.print(" ");
}
     break ;
 
     case 3:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("speed= ");
     lcd.setCursor(0,1);
     lcd.print(soundcm);
     lcd.print("cm/ms");
   }
  }