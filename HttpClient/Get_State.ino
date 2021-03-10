#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "Lampu Depan";
const char* password =  "Qwerty12";
int i;
void setup() {
 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  kontrol();
  }
  else{
    Serial.println("Network Error");
  }
  Serial.println("============================================");
}

void kontrol(){
    HTTPClient http;
    http.begin("https://si.ft.uns.ac.id/smartpowerwall/api/State"); //Specify the URL
    int httpCode=http.GET();
    String response = http.getString();
    int state1 = response[16];
    int state2 = response[25];
    int state3 = response[34];
    http.end();
    if(state1==49){
      Serial.print(state1);
      Serial.print("--");
      Serial.println("Main Load ON");
    }
    else if(state1==48){
      Serial.print(state1);
      Serial.print("--");
      Serial.println("Main Load OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
    if(state2==49){
            Serial.print(state2);
      Serial.print("--");
      Serial.println("Grid ON");
    }
    else if(state2==48){
      Serial.print(state2);
      Serial.print("--");
      Serial.println("Grid OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
    if(state3==49){
            Serial.print(state3);
      Serial.print("--");
      Serial.println("Battery ON");
    }
    else if(state3==48){
      Serial.print(state3);
      Serial.print("--");
      Serial.println("Main Load OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
    
}
