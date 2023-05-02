#include <LiquidCrystal.h>


LiquidCrystal lcd(2, 3, 9, 10, 11, 12);

byte customChar[8] = { 
    
  0b00000,
	0b11000,
	0b11000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};



#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7     // Digital pin connected to the DHT sensor 

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11    // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

const int buttonPin = 8;
int buttonState = LOW;
int lastButtonState = LOW:

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int count = 0;


void setup() {
  Serial.begin(9600);
  lcd.createChar(0, customChar); 
  lcd.begin(16, 2); //lcd display will take 16 coloums and 2 rows 
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
  delayMS = sensor.min_delay / 1000;
 
}

void loop() {
int reading = digitalRead(buttonPin);
if (reading != lastButtonState){
lastDebounceTime = millies();
}
if ((millis() - lastDebounceTime) > deBounceDelay){

  if (reading != buttonState){
    buttonstate = reading; 

    if(buttonState == HIGH){
      count++;
      if (count=4){
        count = 1; 
      }
    }
  }
}
 Switch case(count){
   case 1:
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
  
    lcd.setCursor(0,0);
    lcd.print("T=" );
    lcd.print(event.temperature);
    lcd.write((byte)0);
    lcd.print("C");
    Serial.print(F("Temperature Celcius: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

    Serial.print(F("Temperature Fahrenheit: "));
    float Fvalue = ((event.temperature*9/5) + 32);
    Serial.print(Fvalue);
    Serial.println(F("°F"));

    lcd.setCursor(0,0);
    lcd.print("T=" );
    lcd.print(event.temperature);
    lcd.write((byte)0);
    lcd.print("C");
    lcd.print(Fvalue);
    lcd.write((byte)0);
    lcd.print("F");

  
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
  

    lcd.setCursor(0,1);
    lcd.print("H= ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
    lcd.print("         ");

  
  }
   
}
