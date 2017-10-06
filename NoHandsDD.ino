 /*
 *  Wireless Differential Drive with ESP82666
 *  - arush15june
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>`
#include <DNSServer.h>
#include "DifferentialDrive.h"
ADC_MODE(ADC_VCC);

/* Constants */
// DD Constants
direction CurrentDirection = STOP;

// WiFI Consts
const char* ssid_AP = "Look Ma No Hands";
const char* password_AP = "";
IPAddress apIP(192, 168, 12, 24);
IPAddress netMsk(255, 255, 255, 0);
const char* ssid_WIFI = "Charge-Fi; // Your Home WLAN SSID
const char* password_WIFI = "19951999"; // Your Home WLAN Password
  
// Update Server Consts
const char* host = "discover"; // mDNS Hostname (dosen't really matter);
const char* update_path = "/firmware";// HTTPUpdater endpoint
const char* update_username = ""; // Update Auth
const char* update_password = ""; 
// DNS Server Consts
const byte DNS_PORT = 53;
DNSServer dnsServer;

/* Global Objects */
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
DifferentialDrive dd({1, 2, 3, 4, 5, 6}, 255, 255});


void setup() {

}

void loop() {

}
