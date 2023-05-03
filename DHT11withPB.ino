#include <LiquidCrystal.h> // Include the LiquidCrystal library

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 9, 10, 11, 12);

#include <Adafruit_Sensor.h> // Include this library to provide common interface for reading sensor data
#include <DHT.h> // Include DHT library to provide functions for reading temperature and humidity data from DHT sensor
#include <DHT_U.h>

#define DHTPIN 7     // Digital pin connected to the DHT sensor 

#define DHTTYPE    DHT11    

DHT_Unified dht(DHTPIN, DHTTYPE); // Create a "dht" instance of the "DTH_Unified" class.


uint32_t delayMS;

const int buttonPin = 8; // Create a constant integer variable to reflect the number of button pins.
// Create integer variables to store the button's current and previous states.
int buttonState = LOW;
int lastButtonState = LOW;
// Set up variables to manage debouncing the button signal
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;
// Create a variable to record how many times the button has been pressed.
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
int reading = digitalRead(buttonPin);//Read the state of the button
//debounce the button to avoid  bouncing signals
if (reading != lastButtonState){
lastDebounceTime = millies();
}

if ((millis() - lastDebounceTime) > deBounceDelay){
//update the buttonState variable if the button status has changed and is stable.
  if (reading != buttonState){
    buttonstate = reading; 
//If the button is pressed, it will cycle through the display options.
    if(buttonState == HIGH){
      count++;
      if (count==4){
        count = 1; 
      }
    //switch case statement to control different display options
 Switch case(count){
  //Display temperature in Celsius
   case 1:
  sensors_event_t event;
  dht.temperature().getEvent(&event); // Using the temperature() function, read the temperature data from the DHT11 sensor and put the results in the "event" variable.
  if (isnan(event.temperature)) {  // If temperature event isn't a number
    Serial.println(F("Error reading temperature!")); // serial print Error
  }
  else { // Print temperature event number with Celsius symbol
    lcd.setCursor(0,0);
    lcd.print("T=" );
    lcd.print(event.temperature);
    lcd.print("C");
    Serial.print(F("Temperature Celcius: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"))
  }
  break;
	 case 2:
  //Display humidity
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event); // reads the humidity data from the DHT11 sensor using humidity() function and store the result in the "event" variable.
  if (isnan(event.relative_humidity)) { // If humidity event is not a number
    Serial.println(F("Error reading humidity!")); //print error

  }
  else {
    Serial.print(F("Humidity: ")); // Print humidity number with a percentage symbol
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("H= ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
    lcd.print("         ");
  } 
break;
	case 3: 
         //Display temperature in Fahrenheit
          dht.temperature().getEvent(&event);
          if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
	  }
else { // Conversion from Celsius to Fahrenheit
    Serial.print(F("Temperature Fahrenheit: "));
    float Fvalue = ((event.temperature*9/5) + 32);
    Serial.print(Fvalue);
    Serial.println(F("°F"));

    lcd.setCursor(0,0);
    lcd.print("T=" );
    lcd.print(event.temperature);
    lcd.print("C");
    lcd.print(Fvalue);
    lcd.print("F");
}
break;
    }
  }
 }
}

//update lastButtonState to current reading for next cycle
lastButtonState = reading;

}