//This LoRa Receiver end code for realy controlling ..
//Here the serial monitor can freceive the input message of Transeceiver serial monitor..
//By the that inputs the relay can control here by receiving message ..
When digital Relay output pin is 1 and the outpin also 1 like this[1,1] then first realy is on.
Like vice versa it will on and off
#include <SPI.h>
#include <LoRa.h>

#define BAND 868E6  // LoRa frequency

// Define the GPIO pins connected to the relay module
const int relay1Pin = 15;
const int relay2Pin = 22;
const int relay3Pin = 4;
const int relay4Pin = 26;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize the relay pins as outputs
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);

  // Initialize LoRa
  LoRa.setPins(5, 14, 2); // Set the pins: NSS, RESET, DIO0 (adjust according to your wiring)
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Receiver Ready");
}

void loop() {
  // Try to parse a LoRa packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String command = "";
    while (LoRa.available()) {
      command += (char)LoRa.read();
    }
    
    Serial.print("Received command: ");
    Serial.println(command);

    // Parse the command
    int relayNumber = command.substring(1, 2).toInt();
    int relayState = command.substring(3, 4).toInt();

    // Control the relays based on the received command
    switch (relayNumber) {
      case 1:
        digitalWrite(relay1Pin, relayState == 0 ? HIGH : LOW);
        break;
      case 2:
        digitalWrite(relay2Pin, relayState == 0 ? HIGH : LOW);
        break;
      case 3:
        digitalWrite(relay3Pin, relayState == 0 ? HIGH : LOW);
        break;
      case 4:
        digitalWrite(relay4Pin, relayState == 0 ? HIGH : LOW);
        break;
      default:
        Serial.println("Invalid relay number");
        break;
    }
  }
}
