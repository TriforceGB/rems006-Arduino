#include <ModbusRTUSlave.h>

// Pins List
// #define SoftTX 14 // Phyical TX 0
// #define SoftRX 15 // Phyical RX 1
#define DERE 9
#define LED 2

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Library
ModbusRTUSlave modbus(Serial, DERE); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[2];
float *FloatRegisters = (float*)InputRegisters; // Usable Address is from 0-99? Temperature: 0-49, Humidity 50-99 

void setup()
{
  pinMode(LED, OUTPUT);

  modbus.configureCoils(coils, 1);
  modbus.configureInputRegisters(InputRegisters, 2);
  modbus.begin(ID, 19200);          // ID | Baud Rate
  Serial.begin(9600);              // For Debuging
}

void loop() {
modbus.poll();
    if (coils[0] == 1) {
        coils[0] = 0;
        FloatRegisters[0] = random(0, 1000) / 100.0f;
        Serial.println();
        Serial.println("----------------------------------------------------------------");
        Serial.print("InputRegisters 1: "); Serial.println(InputRegisters[0]);
        Serial.print("InputRegisters 2: "); Serial.println(InputRegisters[1]);
        Serial.print("Float Registers 1: "); Serial.println(FloatRegisters[0]);
    }
}