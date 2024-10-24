#include <SPI.h>
#include <Ethernet.h>

// MAC address for the Ethernet module (you can change this to any valid MAC address)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP address (optional if you use DHCP)
IPAddress ip(192, 168, 1, 177);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  Ethernet.init(10);
  
  
  // Allow some time for the W5500 to initialize
  delay(1000);
  
  // Start the Ethernet connection
  Serial.println("Starting Ethernet connection...");

  // Start Ethernet using DHCP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // If DHCP fails, set a static IP
    Ethernet.begin(mac, ip);
  }

  // Print the IP address assigned to the module
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Keep the Ethernet module alive
}
