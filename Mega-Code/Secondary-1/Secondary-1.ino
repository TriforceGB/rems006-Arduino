/*
  Secondary Sensors Sender

  The Skectch Made for Secondarys that Collect Data from Sensors and Send them to the Primany Arduino to be send to other locations. All Secondary used the same code with different ID per system

  Pin List
    - D0 RX
    - D1 TX
    - D2 LED
    - D4 AM2302 Heat/DHT221
    - D5 SR-HC 50x Motion
    - D6 SW-1815P Vibration Sensor
    - D7 DS18B20 Heat
    - D14/A0 Water Leak Set 1 (Digital)
    - D15/A1 Water Leak Set 2 (Digital)
    - D18/A6 Water Leak Set 1 (Analog)
    - D19/A7 Water Leak Set 2 (Analog)

Modbus Address
Coil Address Index
 - (0) Command to Read Sensors

Input Register/Float Register Address Index (InputRegister)[FloatRegister]
 - (0-1)[0] Temperature from DS18B20
 - (2-5)[1-2] Temperature and Humidity from AM2302

Discrete Inputs Address Index
 - (0) Motion Sensor
 - (1) Water Leak Sensor
 - (2) Vibration Sensor

  Created on November 11, 2024
  By Zachary Schultz
  Help from Arham Rashad For Sensor Code
*/

// Initializing libraries
#include <ModbusRTUSlave.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

//Importing .h files
#include "conf.h"
#include "DS18B20_Sensor.h"
#include "AM2302_Sensor.h"

//Modbus Arrays Numbers come from conf.h
bool Coils[CoilAddress];
bool DiscreteInputs[DIAddress];
uint16_t HoldingRegisters[HRAddress];
uint16_t InputRegisters[IRAddress];
float *FloatRegisters = (float*)InputRegisters; // Turns an array of uint16 into floats by taking array in pairs

// Creating Modbus Connection
ModbusRTUSlave modbus(RS485Serial); // DERE Pins aren't used with our RS485 so they do not have to be define

//Read all Sensors to test if they are working
void readDebug() {
      Serial.print("DS18B20 Temperature: ");
      Serial.println(DS18B20_Temp());
      Serial.print("AM2302 Temperature: ");
      Serial.println(AM2302_Temp());
      Serial.print("AM2302 Humidity: ");
      Serial.println(AM2302_Humidity());
}
// used for debuging modbus arrays can be remove if needed
void printdata() {
  Serial.println("-----Discrete Input-----");
    for (int z = 0; z < DIAddress; z++) {
      Serial.print(DiscreteInputs[z]);
      Serial.print(",");
      delay(100);
    }
  Serial.println();
  Serial.println("-----RAW Input Register-----");
    for (int z = 0; z < IRAddress; z++)
    {
      Serial.print(InputRegisters[z]);
      Serial.print(",");
      delay(100);
    }
  Serial.println();
  Serial.println("-----Float Register-----");
    for (int z = 0; z < IRAddress/2; z++)
    {
      Serial.print(FloatRegisters[z]);
      Serial.print(",");
      delay(100);
    }
    Serial.println();
}

// ----------Basic Setup and Loop Start Here ----------
void setup(){
  modbus.configureCoils(Coils,CoilAddress);
  modbus.configureDiscreteInputs(DiscreteInputs,DIAddress);
  modbus.configureHoldingRegisters(HoldingRegisters,HRAddress);
  modbus.configureInputRegisters(InputRegisters,IRAddress);

  Serial.begin(baud);
  RS485Serial.begin(baud); // Only Needed if using Software Serial or have 2 Serial Terminals
  modbus.begin(ID, baud);

// Initializing Sensors
  initializeDS18B20();

  Serial.println("Secondary Board Sketch");
  Serial.print("Board ID: "); 
  Serial.println(ID);
  delay(1000);
}

void loop() {    
  modbus.poll(); // Checks for request on Modbus
  if (Coils[0] == 1) { // Read Data Only When Primary Tells it To
    Serial.println("Sending Data");
  
    FloatRegisters[0] = 19.4;  //DS18B20_Temp();
    FloatRegisters[1] = 20.6;//AM2302_Temp();
    FloatRegisters[2] = 40.3;//AM2302_Humidity();

    DiscreteInputs[0] = 1; // Motion
    DiscreteInputs[1] = 0; // Water
    DiscreteInputs[2] = 1; // Vibration

    printdata(); //for debuging

    Coils[0] = 0; // Pervent Looping More then 1 Time
  }
}