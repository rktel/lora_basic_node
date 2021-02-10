
#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
float frequency = 868.0;
int txPower = 20;

long prevMillis = 0;

String deviceID = "LORD01,01,";
String payload = "";
void setup()
{
  Serial.begin(9600);
  //while (!Serial) ; // Wait for serial port to be available
  Serial.println("Start LoRa Client");
  if (!rf95.init())
    Serial.println("init failed");
  // Setup ISM frequency
  loraSetup();

}

void loop()
{
  if (runEvery(5000)) {
    Serial.print("Sending: ");
    String payload = deviceID + String(random(20, 40));
    Serial.println(payload);
    rf95.send(payload.c_str(), payload.length());
    rf95.waitPacketSent();
    payload = "";
  }

}
void loraSetup() {
  rf95.setTxPower(txPower, false);
  rf95.setFrequency(frequency);
}
bool runEvery(long _interval) {
  if (millis() - prevMillis > _interval) {
    prevMillis = millis();
    return true;
  }
  return false;
}
