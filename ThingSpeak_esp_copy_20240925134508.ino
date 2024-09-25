#include<WiFi.h>
#include"ThingSpeak.h"
#define PIN 4

const char* ssid = "POCO M2";   // your network SSID (name) 
const char* password = "Anurag@123";

WiFiClient Client ;

//You need to insert the number of the channel that you’re publishing to. 
//If you only have one channel created in ThingSpeak, the channel number is 1.
// Otherwise, you can see the number of the channel on the Private View tab 
unsigned long int myChannelNumber = 1;
const char * myWriteAPIKey = "5D2U9OS2QXEXD1DJ";
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

int data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
  WiFi.mode(WIFI_STA);//as astation 
  ThingSpeak.begin(Client);  //initialize thngspeak
}

void loop() {
  // put your main code here, to run repeatedly:
  if((millis() - lastTime > timerDelay)){
  //connect to wifi network
  if(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print("attempting to connect");
    while(WiFi.status() !=WL_CONNECTED){
      WiFi.begin(ssid,password);
      delay(5000);
    }
    Serial.println("nConnected");
    
  }
  data =touchRead(PIN);
  Serial.print("touch sensor data is");
  Serial.println(data);
  delay(1000);
// Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, data, myWriteAPIKey);
  if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    

}
}