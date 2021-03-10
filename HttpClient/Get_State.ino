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
 
    HTTPClient http;
    http.begin("https://si.ft.uns.ac.id/smartpowerwall/api/State"); //Specify the URL
    int httpCode=http.GET();
    String response = http.getString();
      Serial.println(response);
      Serial.println(response[16]);
      Serial.println(response[25]);
      Serial.println(response[34]);

//    String payload1 = http.getString();
//    Serial.println(payload1);//Make the request
    http.end(); //Free the resources
  }
 
  delay(10000);
 
}
