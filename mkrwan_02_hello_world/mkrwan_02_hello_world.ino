#include <MKRWAN.h>
#include "arduino_secrets.h" 

// Select your region (AS923, AU915, EU868, KR920, IN865, US915, US915_HYBRID)
_lora_band region = EU868;

LoRaModem modem(Serial1);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!modem.begin(region)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  Serial.println("Successfully joined the network!");

  Serial.println("Enabling ADR and setting low spreading factor");
  modem.setADR(true);
  modem.dataRate(5);
}

void loop() {
  modem.beginPacket();
  modem.print("hi");
  
  int err = modem.endPacket(false);

  if (err > 0) {
    Serial.println("Big success!");
  } else {
    Serial.println("Error");
  }
  delay(1000 * 60);
}
