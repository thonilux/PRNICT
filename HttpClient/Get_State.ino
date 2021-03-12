#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "PRN ICT";
const char* password =  "prnict2021";
int i;


void setup() {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
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
    http.end();
    int state1 = response[16];
    int state2 = response[25];
    int state3 = response[34];

    if(state1==49){
      digitalWrite( 18, LOW);
      Serial.print(state1);
      Serial.print("--");
      Serial.println("Main Load ON");
    }
    else if(state1==48){
      digitalWrite( 18, HIGH);
      Serial.print(state1);
      Serial.print("--");
      Serial.println("Main Load OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
    
    if(state2==49){
      digitalWrite( 19, LOW);
      Serial.print(state2);
      Serial.print("--");
      Serial.println("Grid ON");
    }
    else if(state2==48){
      digitalWrite( 19, HIGH);
      Serial.print(state2);
      Serial.print("--");
      Serial.println("Grid OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
    
    if(state3==49){
      digitalWrite( 21, LOW);
      Serial.print(state3);
      Serial.print("--");
      Serial.println("Battery ON");
    }
    else if(state3==48){
      digitalWrite( 21, HIGH);
      Serial.print(state3);
      Serial.print("--");
      Serial.println("Main Load OFF");
    }
    else{
      Serial.println("System Failure - Check Web API");
    }
}
