/*#include <Arduino.h>
#define TRUE 1
#define FALSE 0
char receivedChar;
String receivedStr; // Evite .. perf
int sensorValue;
int jour = FALSE;
float val = 0.0;

void setup() {
    Serial.begin(9600);
    Serial.println("<Serial is ready>");
}

void loop() {
    // L'ESP écrit sur le lien serial
    sensorValue = analogRead(A5); // read analog input : light
    Serial.print(sensorValue, DEC); // prints the value to the serial port
    Serial.print("\n"); // as human-readable ASCII text

    // L'ESP lit
    while(Serial.available() > 0){
        // read from serial
        //receivedChar = Serial.read();
        receivedStr = Serial.readStringUntil('\n');
        Serial.print("\n received : "); // say what you got :
        //Serial.println(receivedChar);
        Serial.print(receivedStr);

        // Action ?
        //if(receivedStr == '1') jour = TRUE; else jour = FALSE;

        val = receivedStr.toFloat();
        Serial.println(val);
    }
    delay(1000);
}*/