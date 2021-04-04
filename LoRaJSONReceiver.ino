#include <SPI.h>
#include <LoRa.h>
#include <Arduino_JSON.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    
    // read packet
    while (LoRa.available()) {
      String trashmsg = LoRa.readString();
      Serial.println(trashmsg);
    }
    
    // print RSSI of packet
    
  }
}
