/*
  This example configures LinkIt 7697 to act as a simple GATT server with 1 characteristic.

  To use it, open AppInventor project:

    * 

  Build & install it on Android id

  created Mar 2017
*/
#include <LBLE.h>
#include <LBLEPeriphral.h>

#define r_Pin 14
#define g_Pin 15
#define b_Pin 16

// Define a simple GATT service with only 1 characteristic
LBLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214");
LBLECharacteristicInt switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", LBLE_READ | LBLE_WRITE);

void setup() {

  pinMode(r_Pin, OUTPUT);
  pinMode(g_Pin, OUTPUT);
  pinMode(b_Pin, OUTPUT);
  digitalWrite(r_Pin, HIGH);
  digitalWrite(g_Pin, HIGH);
  digitalWrite(b_Pin, HIGH);
  // Initialize LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // to check if USR button is pressed
  pinMode(6, INPUT);

  // Initialize BLE subsystem
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");

  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");

  // configure our advertisement data.
  // In this case, we simply create an advertisement that represents an
  // connectable device with a device name
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice("BLE LED");

  // Configure our device's Generic Access Profile's device name
  // Ususally this is the same as the name in the advertisement data.
  LBLEPeripheral.setName("BLE LED");

  // Add characteristics into ledService
  ledService.addAttribute(switchCharacteristic);

  // Add service to GATT server (peripheral)
  LBLEPeripheral.addService(ledService);

  // start the GATT server - it is now 
  // available to connect
  LBLEPeripheral.begin();

  // start advertisment
  LBLEPeripheral.advertise(advertisement);
}

void loop() {
  delay(1000);

  Serial.print("conected=");
  Serial.println(LBLEPeripheral.connected());

  if (digitalRead(6))
  {
    Serial.println("disconnect all!");
    LBLEPeripheral.disconnectAll();
  }

  if (switchCharacteristic.isWritten()) {
    const char value = switchCharacteristic.getValue();
    switch (value) {
      case 1:
        analogWrite(r_Pin, 246);
        analogWrite(g_Pin, 235);
        analogWrite(b_Pin, 57);
        break;
      case 2:
        analogWrite(r_Pin, 248);
        analogWrite(g_Pin, 186);
        analogWrite(b_Pin, 21);
        break;
      case 3:
        analogWrite(r_Pin, 248);
        analogWrite(g_Pin, 153);
        analogWrite(b_Pin, 29);
        break;
      case 4:
        analogWrite(r_Pin, 239);
        analogWrite(g_Pin, 85);
        analogWrite(b_Pin, 34);
        break;
      case 5:
        analogWrite(r_Pin, 235);
        analogWrite(g_Pin, 51);
        analogWrite(b_Pin, 35);
        break;
      case 6:
        analogWrite(r_Pin, 166);
        analogWrite(g_Pin, 29);
        analogWrite(b_Pin, 75);
        break;
      case 7:
        analogWrite(r_Pin, 124);
        analogWrite(g_Pin, 54);
        analogWrite(b_Pin, 146);
        break;
      case 8:
        analogWrite(r_Pin, 70);
        analogWrite(g_Pin, 46);
        analogWrite(b_Pin, 144);
        break;
      case 9:
        analogWrite(r_Pin, 62);
        analogWrite(g_Pin, 92);
        analogWrite(b_Pin, 169);
        break;
      case 10:
        analogWrite(r_Pin, 7);
        analogWrite(g_Pin, 145);
        analogWrite(b_Pin, 204);
        break;
      case 11:
        analogWrite(r_Pin, 100);
        analogWrite(g_Pin, 173);
        analogWrite(b_Pin, 69);
        break;
      case 12:
        analogWrite(r_Pin, 205);
        analogWrite(g_Pin, 220);
        analogWrite(b_Pin, 57);
        break;
      default:
        Serial.println("Unknown value written");
        break;
    }
  }


}
