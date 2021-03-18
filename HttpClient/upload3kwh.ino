#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid = "PRN ICT";
const char* password =  "prnict2021";
int i=1;

void setup() {
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
void loop() {
  
 if(WiFi.status()== WL_CONNECTED){
   checkpoint:
   HTTPClient http;
   int p = random(0,10);
   int v = random(220,230);
   int io = random(0,9);
   http.begin("https://si.ft.uns.ac.id/smartpowerwall/api/ApiData");
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   String dataout = "kwh="+String(i)+"&power=" + String(p) + "&voltage=" + String(v) + "&current="+ String(io) +"&submit=enter";
   int httpResponseCode = http.POST(dataout);  
   Serial.println(httpResponseCode);
   http.end();
   if(httpResponseCode==429){
    Serial.println("Retry");
    delay(3000);
    goto checkpoint;
   }
   else if(httpResponseCode==201){
    Serial.println(dataout);
   }
   i++;
   if(i>3){
    i=1;
    Serial.println("=================================================");
    delay(3000);
   }
 }
 
  else{ 
    Serial.println("Error in WiFi connection");   
 }
}
