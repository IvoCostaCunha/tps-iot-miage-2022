#define TRUE 1
#define FALSE 0

#include <Arduino.h>

#include "OneWire.h" 
#include "DallasTemperature.h"

#include <string>

/*** Basic Wifi connection: wificonnect.ino ***/
#include <SPI.h>
#include <WiFi.h> // https://www.arduino.cc/en/Reference/WiFi

#include <ArduinoJson.h>

#define SaveDisconnectTime 1000 // Time im ms for save disconnection, needed to avoid that WiFi works only every second boot: https://github.com/espressif/arduino-esp32/issues/2501

char receivedChar;
String receivedStr;

/* Credentials */
const char ssid[] = "SSID";
const char password[] = "PWD"; 

// D25 D26 for led
// D23 for temperature sensor
// D32 for luminosity sensor

OneWire oneWire(23); // Allows to get data from multiple sensors from same bus
DallasTemperature tempSensor(&oneWire); // Allows for mesurement of athe actual sensor

const int greenLedPin = 25; 
const int redLedPin = 26;
String redLedStatus;
String greenLedStatus;

/*------------------------*/
String translateEncryptionType(wifi_auth_mode_t encryptionType) {
   // cf https://www.arduino.cc/en/Reference/WiFiEncryptionType 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}
/*------------------------*/
void print_network_status_light(){ // array of chars
  char s[256];
  sprintf(s,"\tIP address : %s\n", WiFi.localIP().toString().c_str()); Serial.print(s);
  sprintf(s,"\tMAC address : %s\n", WiFi.macAddress().c_str()); Serial.print(s);
  sprintf(s,"\tWifi SSID : %s\n", WiFi.SSID()); Serial.print(s);
  sprintf(s,"\tWifi Signal Strength : %ld dBm\n",WiFi.RSSI()); Serial.print(s);
  sprintf(s,"\tWifi Signal Strength : %ld %\n",constrain(2 * (WiFi.RSSI() + 100), 0, 100)); Serial.print(s);
  sprintf(s,"\tWifi BSSID : %s\n", WiFi.BSSIDstr().c_str()); Serial.print(s);
  sprintf(s,"\tWifi Encryption type : %s\n", translateEncryptionType(WiFi.encryptionType(0))); Serial.print(s);
}
void print_network_status(){ // Utilisation de String !
  String s = "";
  s += "\tIP address : " + WiFi.localIP().toString() + "\n"; 
  s += "\tMAC address : " + String(WiFi.macAddress()) + "\n";
  s += "\tWifi SSID : " + String(WiFi.SSID()) + "\n";
  s += "\tWifi Signal Strength : " + String(WiFi.RSSI()) + " dBm\n";
  s += "\tWifi Signal Strength : " + String(constrain(2 * (WiFi.RSSI() + 100), 0, 100)) + " %\n";
  s += "\tWifi BSSID : " + String(WiFi.BSSIDstr()) + "\n";
  s += "\tWifi Encryption type : " + translateEncryptionType(WiFi.encryptionType(0))+ "\n";
  Serial.print(s);
}
/*------------------------*/
void connect_wifi(){
 #define WiFiMaxTry 10
 int i;
 String hostname = "Mon petit objet ESP32";

 WiFi.mode(WIFI_OFF); 
 // Set WiFi to station mode 
 WiFi.mode(WIFI_STA);
 // WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
 // Disconnect from an AP if it was previously connected
 WiFi.disconnect(true); // delete old config
 // WiFi.persistent(false); //Avoid to store Wifi configuration in Flash
 delay(100); // ms

 // Define hostname before begin
 WiFi.setHostname(hostname.c_str()); 
  
 Serial.println(String("\nAttempting to connect AP of SSID : ")+ssid);
 WiFi.begin(ssid, password);
 i = 0;
 while(WiFi.status() != WL_CONNECTED && (i < WiFiMaxTry)){
   delay(SaveDisconnectTime); // 500ms seems to work in most cases, may depend on AP
   Serial.print(".");
   i++;
 }
}

void turnRedLedOn() {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    greenLedStatus = "off";
    redLedStatus = "on";
}

void turnGreenLedOn() {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    greenLedStatus = "on";
    redLedStatus = "off";
}

void setup() {
    Serial.begin(9600);
    while(!Serial);//wait for a serial connection  

    // Python script dromserial.py can't translate into json
    // for some reason if wifi fails this if off ... to fix
    connect_wifi();          // Connect wifi 
  
    if (WiFi.status() == WL_CONNECTED){
        Serial.print("\nWiFi connected : \n");
        print_network_status();  // Print status
    } 

    tempSensor.begin();

    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);

    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);

    redLedStatus = "off";
    greenLedStatus = "on";
}

void loop() {

    while(Serial.available() > 0) {

        // JSON Parser apapted to arduino dev
        // exemple : https://wandbox.org/permlink/iDBqO7Vqs7t8W1qH
        // https://arduinojson.org

        // 50 is the size in bits
        StaticJsonDocument<50> doc;

        // Read from serial
        //receivedChar = Serial.read();
        receivedStr = Serial.readStringUntil('\n'); // A string
        Serial.print("\nESP received : "); // say what you got:
        //Serial.println(receivedChar);
        Serial.println(receivedStr) ;
        // Should be tested to check fo errors but i'm gonna ignore this there 
        //DeserializationError error = deserializeJson(doc, receivedStr);
        /*if (error) {
            std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
            return 1;
        }*/

        deserializeJson(doc, receivedStr);
        String cmd = doc["cmd"];
        
        if(cmd == "start") {
            turnGreenLedOn();
        }
        
        else if(cmd == "stop") {
            turnRedLedOn();
        }
    }


    int sensorValue = analogRead(A4); // Read pin 32 ADC1_4
    // Request a temperature mesure in C / O is the 1st sensor if there are more ...
    tempSensor.requestTemperaturesByIndex(0);
    // Read the last temperature in C (?) for sensor 0
    float temp = tempSensor.getTempCByIndex(0); 
    

    String json = "{\n\"temperature\": \""+(String)temp+" C\",\n\"light\": \""+(String)sensorValue+" lm\",\n\"red-led\": \""+redLedStatus+"\",\n\"green-led\": \""+greenLedStatus+"\"\n}";

    Serial.println(json+"\n");
    delay(1000);
}