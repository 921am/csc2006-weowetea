#include <SPI.h>
#include <LoRa.h>
#include <Arduino_JSON.h>
#include "DHT.h"
#include <hcsr04.h>

#define DHTTYPE DHT11   // DECLARE DHT 11
#define DHTPIN 3 // DHT 11 PIN 3
DHT dht(DHTPIN, DHTTYPE); // DHT object

#define TRIG_PIN 4 // Ultrasonic TRIGGER PIN
#define ECHO_PIN 5 // Ultrasonic ECHO PIN
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000); // Ultrasonic object

int FLAME_PIN=A0;

const int TRASHBIN = 3;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  dht.begin(); // begin DHT 

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  // create trash info object
  JSONVar trashObject;
  trashObject["ID"] = TRASHBIN;
  trashObject["level"] = hcsr04.distanceInMillimeters();
//  trashObject["humidity"] = dht.readHumidity();
//  trashObject["temperature"] = dht.readTemperature();
trashObject["humidity"] = 60;
trashObject["temperature"] = 27.6;
  trashObject["flame"] = analogRead(0);
  
  String trashmsg = JSON.stringify(trashObject);
  
  // send packet
  LoRa.beginPacket();
  LoRa.print(trashmsg);
  LoRa.endPacket();

  // log packet
  Serial.println(trashmsg);

  delay(1000);
}
