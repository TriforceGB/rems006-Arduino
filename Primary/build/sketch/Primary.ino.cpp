#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// Pins List
#define SoftTX 14 // Phyical TX 0
#define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Initialize Library
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object with port for RS485

bool SlaveLED = 1; // Enable Slave LED by default

uint16_t randomfloat_UINT16[200];
float *randomfloat = (float*)randomfloat_UINT16;

uint16_t randomtime_UINT16[200];
float *randomtime = (float*)randomtime_UINT16;

#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 49 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
bool debug(uint16_t message);
#line 22 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup()
{
  pinMode(LED, OUTPUT);

  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(5000);
}

void loop()
{
  uint16_t returncode = modbus.readHoldingRegisters(1, 0, randomfloat_UINT16, 1);
  Serial.println(returncode);
  if(return == 0) {
    for (int i = 0; i <= 200; i++) {
      Serial.println(randomfloat_UINT16[i]);
    }
  uint16_t returncode = modbus.writeSingleCoil(1, 0, true);
  Serial.println(returncode);
    if (returncode == 0) {
      Serial.println("New Number Coming");
    }
  }
  delay(5000);
}


bool debug(uint16_t message){
  uint16_t returnCode = message;
    if (returnCode == 0) {
      return true;
  }
  else {
    // Shows error Message in Debug Terminal
    Serial.print("Error Code: ");
    Serial.println(returnCode);
    return false;
  }
}
