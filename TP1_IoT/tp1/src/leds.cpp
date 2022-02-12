#include <Arduino.h>

/*----- blink/blink.ino -----*/

// ledPin refers to ESP32 GPIO 23 :  Broche D23 sur la carte
/*const int greenLedPin = 23; 
const int redLedPin = 22;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("** This message will only be displayed on start or reset. **");
    delay(1*1000); // wait for one seconds

    // Initialize/configure digital pin ledPin as an OUTPUT.
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    digitalWrite(redLedPin, HIGH);

    delay(1*1000);
}

// the loop function runs over and over again forever
void loop() {
    if(digitalRead(redLedPin) == HIGH){
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);
    }
    else{
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        }
    //digitalWrite(redLedPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1*1000);                // wait for a second
    //digitalWrite(redLedPin, LOW);    // turn the LED off by making the voltage LOW
    //delay(1*1000);
    if(digitalRead(redLedPin) == HIGH) Serial.println("** red led on **");
    else if(digitalRead(greenLedPin) == HIGH) Serial.println("** green led on **");
    Serial.println("** One loop done. **");               // wait for a second
}*/
