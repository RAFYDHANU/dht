#include <DHT.h>
#include <UbidotsMicroESP8266.h> // 

#define DHTPIN 4
#define DHTTYPE DHT11

char auth[] = "-GXQoie3o8On4IlemNejA_N003nRpC8e"; 
char ssid[] = "Dhanu";
char pass[] = "masalupa";

DHT dht(DHTPIN,DHTTYPE); 
Ubidots client(auth);     // setting token di ubidots
unsigned long last = 0;

void setup() {
  Serial.begin(9600);
  dht.begin(); // dht mulai membaca suhu dan kelembapan 
  delay(20);  //delay 0,2 detik
  client.wifiConnection(ssid,pass); // menyambungkan ubidots client ke wifi

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-last>10000){ // jika udh 10 detik
    float hum = dht.readHumadity();
    float temp = dht.readTemperature();

    last = millis(); //11
    client.add("kelembapan",hum); //ubidots client membaca kelembapan 
    client.add("Temperature"temp); //ubidots client membaca suhu
    client.sendAll(true); // ubidots client mengirimkan semua data
  }
}
