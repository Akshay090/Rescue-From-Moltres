#include <FirebaseArduino.h>

#include <DHT.h>
#include <dht.h>

#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "node-fire-aks.firebaseio.com"
#define WIFI_SSID "LAN" // Change the name of your WIFI
#define WIFI_PASSWORD "qwerty12345" // Change the password of your WIFI

#define DHTPIN 14    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {

   Serial.begin(115200);

     pinMode(5, INPUT);

   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {
 
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
 
  int sensorVal = digitalRead(5);

  
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);

  if (sensorVal == HIGH)
 { Serial.println ("fire");
   Firebase.setString ("Status","fire");  
 }
else
  {Serial.println ("healthy");
   Firebase.setString ("Status","healthy");  
  }
 
  Serial.println (t);
  Serial.println (h);
  delay(200);
}