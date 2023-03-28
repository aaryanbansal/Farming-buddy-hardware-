#include "Arduino.h"
#include "DHT.h"
#include "SoilMoisture.h"


// Pin Definitions
#define DHT_PIN_DATA	2
#define IRFLAME_5V_PIN_AOUT	A3
#define MQ2_5V_PIN_AOUT	A1
#define SOILMOISTURE_5V_PIN_SIG	A5



// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);
SoilMoisture soilMoisture_5v(SOILMOISTURE_5V_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Infrared Flame Detection Sensor is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '4') {
    // Soil Moisture Sensor - Test Code
    int soilMoisture_5vVal = soilMoisture_5v.read();
    Serial.print(F("Val: ")); Serial.println(soilMoisture_5vVal);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) Infrared Flame Detection Sensor"));
    Serial.println(F("(3) Methane, Butane, LPG and Smoke Gas Sensor - MQ-2"));
    Serial.println(F("(4) Soil Moisture Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Infrared Flame Detection Sensor - note that this component doesn't have a test code"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 - note that this component doesn't have a test code"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Soil Moisture Sensor"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
