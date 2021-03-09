#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "PRN ICT";
const char* password =  "prnict2021";
 
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
 
    HTTPClient http;
    Serial.println("http start");
    http.begin("https://si.ft.uns.ac.id/smartpowerwall/api/ApiData"); //Specify the URL
    http.GET();
    Serial.println(http.GET());//Make the request
    String payload = http.getString();
    Serial.println(payload);//Make the request
    http.end(); //Free the resources
  }
 
  delay(10000);
 
}

