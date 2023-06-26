#include "global.h"

static int nodeId;

void loraSetup() {
  Serial.println("=== LoRa Receiver ===");

  // LoRa module setup
  LoRa.setPins(PIN_SS, PIN_RST, PIN_DIO0);
  while (!LoRa.begin(LORA_SIMPLE_FREQUENCY)) {
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(LORA_SIMPLE_SYNC_WORD);
  Serial.println("...LoRa Initializing OK!");

  // write NODEID in EEPROM
  // EEPROM.write(EEPROM_ADDRESS_NODEID, NODEID); // turn this on if first time
  // set up NODEID, hence not yet written in EEPROM

  // check what current node ID is
  nodeId = (int)EEPROM.read(EEPROM_ADDRESS_NODEID);
  Serial.print("nodeId at EEPROM address '" + (String)EEPROM_ADDRESS_NODEID +
               "' is: " + (String)nodeId);
}

void sendMsg(const String _msg) {
  String payload =
      "nodeId " + (String)nodeId + " Sending message: " + _msg;

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();
}

void recvMsg() {
  // parse received packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("nodeId " + (String)nodeId + " Received message: '");

    // read packet
    while (LoRa.available()) {
      String msg = LoRa.readString();
      Serial.print(msg);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

#ifdef BRD_ESP32
  EEPROM.begin(EEPROM_SIZE);  // must be turned on for ESP32
#endif                        // BRD_ESP32

  loraSetup();
}

long lastSend = 0;
int count = 0;

void loop() {
  recvMsg();

  if (millis() - lastSend > 5000) {
    sendMsg(String(count++));
    lastSend = millis();
  }
}