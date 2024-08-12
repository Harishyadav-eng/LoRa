//This is the Transceiver code for control of Relay through LoRa RFM95 using ESP32 ..
//By using serial monitor sending message like[1,1] it will on the first Relay.
//By seending message like[1,0] it can off the First Relay..
//like this vice-versa upto 4 realy control..

#include <SPI.h>
#include <LoRa.h>

const int csPin = 5;   // LoRa module CS pin
const int resetPin = 14; // LoRa module reset pin
const int dio0Pin = 2;  // LoRa module IRQ pin

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Transmitter");

  LoRa.setPins(csPin, resetPin, dio0Pin);
  if (!LoRa.begin(868E6)) {  // Adjust frequency as needed
    Serial.println("Failed to initialize LoRa");
    while (1);
  }
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    LoRa.beginPacket();
    LoRa.print(command);
    LoRa.endPacket();
    Serial.print("Sent command: ");
    Serial.println(command);
  }
}
