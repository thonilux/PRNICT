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
   int mod = random(1,3);
   int freq = random(45,55);
   int volt = random(200,230);
   float curr = random(0,5);
   http.begin("https://si.ft.uns.ac.id/smartpowerwall/api/InverterData");
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   String dataout = "mode="+String(mod)+"&freq=" + String(freq) + "&voltage=" + String(volt) + "&current="+ String(curr) +"&submit=enter";
   int httpResponseCode = http.POST(dataout);  
   Serial.println(httpResponseCode);
   http.end();
   if(httpResponseCode==429){
    Serial.println("Retry");//handling limitasi server menerima data tiap 3 detik
    delay(3000);
    goto checkpoint;
   }
   else if(httpResponseCode==201){ //jika sukses print data terkirim
    Serial.println(dataout);
   }
 }
 
  else{ 
    Serial.println("Error in WiFi connection");   
 }
}
