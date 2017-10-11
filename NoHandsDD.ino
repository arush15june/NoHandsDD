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

#define maxSpeed 255

ADC_MODE(ADC_VCC);

/* Constants */
// WiFI Consts

const char* ssid_AP = "Look Ma No Hands";
const char* password_AP = "";
IPAddress apIP(192, 168, 12, 24);
IPAddress netMsk(255, 255, 255, 0);
const char* ssid_WIFI = "Charge-Fi"; // Your Home WLAN SSID
const char* password_WIFI = "19951999"; // Your Home WLAN Password
  
// Update Server Consts

const char* host = "discover"; // mDNS Hostname (dosen't really matter);
const char* update_path = "/firmware";// HTTPUpdater endpoint
const char* update_username = ""; // Update Auth
const char* update_password = ""; 

// DNS Server Consts

const byte DNS_PORT = 53;
DNSServer dnsServer;

// Global Objects

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
int pins[] = {1, 2, 3, 4, 5, 6};
DifferentialDrive dd(pins, maxSpeed, maxSpeed);

// Helper Functions

void InfoStr(String type, String Message) {
  String infostr = "[";
  infostr += type;
  infostr += "]";
  infostr += " ";
  infostr += Message;

  Serial.println(infostr);
}

void returnOK() {
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "");
}

void returnOKs() {
  server.sendHeader("Connection", "refresh,20");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "");
}

void returnFail(String msg) {
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

bool loadFromSpiffs(String path) {
  // TODO : Fix Gzipped Serving
  String dataType = "text/plain";
  String pathWithGz = path + ".gz";
  Serial.println(pathWithGz);
  if (path.endsWith("/")) path += "index.htm";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/x-pdf";
  else if (path.endsWith(".zip")) dataType = "application/x-zip";
  else if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
    {
      Serial.println(pathWithGz + " Sending GZipped");
      path += ".gz";
      dataType = "application/x-gzip";
      server.sendHeader("Content-Encoding","gzip");
      File dataFile = SPIFFS.open(path.c_str(), "r");
      if (server.hasArg("download")) dataType = "application/octet-stream";
      if (server.streamFile(dataFile, dataType) != dataFile.size()) {
      }
    
      dataFile.close();
      return true;
    }
  }
  else if (path.endsWith(".gz")) {
    dataType = "application/x-gzip";
  }
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}

// API Handlers

void handleNotFound() {
  InfoStr("WebServer","File Not Found 404");
  if (loadFromSpiffs(server.uri())) return; //Load External Files if possible
  server.send(404, "text/plain", "404 PAGE NOT FOUND");
}

void handleRoot() {
  InfoStr("WebServer","Request: Root");
  if (loadFromSpiffs("/")) return; // Send Index on Root
  else {
    String failMessage = "Couldn't load index from Spiffs";
    server.send(404, "text/plain", failMessage);
  }
}

void handleVCC() {
  InfoStr("WebServer","Request: VCC");
  uint32_t VCC = ESP.getVcc();
  String vccJSON = "{ 'vcc' : '";
  vccJSON += VCC;
  vccJSON += "'}";
  server.send(200, "text/json", vccJSON);
}

void handleRestart() {
  InfoStr("WebServer","Request: Restart"); 
  server.send(200, "text/plain", "Restarting Device");
  ESP.restart();
}

void directionHandler() {
  InfoStr("WebServer","Request: Direction");
  if(server.hasArg("direction")) {
    String dir = server.arg("direction");
    InfoStr("Direction","Recieved: "+dir);
    if(dir.equals("FORWARD")) {
      dd.forward()
      delay(10);
    }
    else if(dir.equals("BACKWARD")) {
      dd.backward()
      delay(10);
    }
    else if(dir.equals("LEFT")) {
      dd.left()
      delay(10);
    }
    else if(dir.equals("RIGHT")) {
      dd.left()
      delay(10);
    }
    else if(dir.equals("STOP")) {
      dd.stop()
      delay(10);
    }

    server.send(200,"text/plain","direction : "+dir);
  }
  else {
    server.send(500,"text/plain","No Direction");
  }

}

void setup() {
/* WiFi init */
  Serial.begin(115200);
  Serial.println();
  InfoStr("Boot","Booted Device");
  WiFi.mode(WIFI_AP_STA);
  
  // Connect to Home WLAN
  if(WiFi.begin(ssid_WIFI, password_WIFI)) InfoStr("Connect","Connected to Home WiFi");
  
  // Serve a WiFi Access Point
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(ssid_AP, password_AP);
  
  /* SPIFFS Init */
  if (!SPIFFS.begin()) {
    InfoStr("I/O","SPIFFS Mount Successfull");
    ESP.restart();
  }
  else {
    InfoStr("I/O","SPIFFS Mount Successfull");
  }

  // Flash Info
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  String str;
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
  }
  Serial.print(str);
  Serial.printf("Flash total bytes: %u\n", fs_info.totalBytes);
  Serial.printf("Flash used bytes: %u\n", fs_info.usedBytes);
  Serial.printf("Flash free bytes: %u\n", fs_info.totalBytes - fs_info.usedBytes);
  
  // Updater Service
  
  /* mDNS service init */
  MDNS.begin(host);

  httpUpdater.setup(&server, update_path, update_username, update_password);

  MDNS.addService("http", "tcp", 80);
  //Serial.printf("HTTPUpdateServer ready! Open http://%s.local%s in your browser and login with username '%s' and password '%s'\n", host, update_path, update_username, update_password);
  
  // DNS Service 
  
  /* DNS Service Init */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
  
  // API Routes

  server.on("/", handleRoot);
  server.on("/restart", handleRestart);
  server.on("/VCC", HTTP_GET, handleVCC);
  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/direction ", HTTP_PUT, directionHandler);
  server.onNotFound ( handleNotFound );
  server.begin(); // Web server start



}

void loop() {
  //DNS
  dnsServer.processNextRequest();
  //HTTP
  server.handleClient();
}
