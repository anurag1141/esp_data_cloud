#include <WiFi.h>
#include"ThingSpeak.h"
#define PIN 4
 
// Replace with your own network credentials
const char* ssid = "POCO M2";
const char* password = "Anurag@123";
WiFiClient Client ;
unsigned long  myChannelNumber = 1;
const char * myWriteAPIKey = "5D2U9OS2QXEXD1DJ";

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;//minimum value allow to free user
int data; 
void setup(){
 
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);//as astation 
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting to WiFi Network ..");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
 
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    ThingSpeak.begin(Client);  // Initialize ThingSpeak
}
void loop(){
   if((millis() - lastTime > timerDelay))
   {
    data =touchRead(PIN);
    Serial.print("touch sensor data is");
    Serial.println(data);
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, data, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
   }
}
