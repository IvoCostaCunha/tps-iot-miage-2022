/*#include <Arduino.h>
#include "OneWire.h" 
#include "DallasTemperature.h"

OneWire oneWire(23); // Allows to get data from multiple sensors from same bus
DallasTemperature tempSensor(&oneWire); // Allows for mesurement of athe actual sensor

void setup() {
    Serial.begin(9600);
    tempSensor.begin();
}

void loop() {
    // Request a temperature mesure in C / O is the 1st sensor if there are more ...
    tempSensor.requestTemperaturesByIndex(0);
    // Read the last temperature in C (?) for sensor 0
    float temp = tempSensor.getTempCByIndex(0); 
    Serial.print("Temp : ");
    Serial.print(temp); 
    Serial.println(" C");
    delay(1000);
}*/
