/*#include <Arduino.h>

int gpio = 26; // GPIO pin

void setup() {
    Serial.begin(9600);
    pinMode(gpio, OUTPUT);
    ledcAttachPin(gpio,0);
    ledcSetup(0,5000,12);
    //ledcWrite(0,1024);
}

void loop() {
    for(int i=0; i<2048; i++){
        ledcWrite(0,i);
        Serial.println(i);
    }
}*/
