
#include <Adafruit_CC3000.h>
#include <ccspi.h>
//#include <SPI.h>
#include <string.h>
#include "utility/debug.h";
#include <SPI.h>
#include <SD.h>


  // Arduino LCD library

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER/8); // you can change this clock speed

#define WLAN_SSID       "thebighack"           // cannot be longer than 32 characters!
#define WLAN_PASS       "bigHack!?15"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "www.bacuuk.com"
#define WEBPAGE      "/control.php"

uint32_t ip;

Adafruit_CC3000_Client www;

void setup(void){
  Serial.begin(115200);
 // Serial.println(F("Hello, CC3000!\n")); 


 // Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
 // Serial.println("Connected!1");
  /* Initialise the module */
//  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
 //   Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  //Serial.println("Connected!2");
  
    // Put this line at the beginning of every sketch that uses the GLCD:
  
  

  // clear the screen with a black background
//  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to yellow
  //TFTscreen.stroke(255, 255, 0);
 
   // Optional SSID scan
  // listSSIDResults();
  
  // try to access the SD card
//  Serial.print("Initializing SD card...");
 // if (!
 // SD.begin(SD_CS);
 // ){
//    Serial.println("failed!");
//    return;
//  }
//  Serial.println("OK!");
 // Serial.println("Connected!3");
//  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
 if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
   while(1);
 }
   
 Serial.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
//  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  ip = 0;
  // Try looking up the website's IP address
//  Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
 //     Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }

  cc3000.printIPdotsRev(ip);
  
  // Optional: Do a ping test on the website
  /*
  Serial.print(F("\n\rPinging ")); cc3000.printIPdotsRev(ip); Serial.print("...");  
  replies = cc3000.ping(ip, 5);
  Serial.print(replies); Serial.println(F(" replies"));
  */  

www = cc3000.connectTCP(ip, 80);
Serial.println("FINE SETUP");

//HTTPrequest(www);
  
//www.close();
// Serial.println(F("-------------------------------------"));
  
//login = TFTscreen.loadImage("login.bmp");
//TFTscreen.image(login,0,0);
  
}
  
//  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
//  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));
//  
//  cc3000.disconnect();
//  
char info[15]={0};
void loop()
{
 
 if(HTTPrequest(www)==1)
 {
   // Serial.println("");
   //Serial.print("info: ");
   Serial.print(info);
   // Serial.println("");
   //visualizza(info);
 }
 
 delay(10000);
}


void listSSIDResults(void)
{
  uint32_t index;
  uint8_t valid, rssi, sec;
  char ssidname[33]; 

  if (!cc3000.startSSIDscan(&index)) {
    // Serial.println(F("SSID scan failed!"));
    return;
  }

  // Serial.print(F("Networks found: ")); Serial.println(index);
  // Serial.println(F("================================================"));

  while (index) {
    index--;

    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
    
    // Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
    // Serial.println();
    // Serial.print(F("RSSI         : "));
    // Serial.println(rssi);
    // Serial.print(F("Security Mode: "));
    // Serial.println(sec);
    // Serial.println();
  }
  // Serial.println(F("================================================"));

  cc3000.stopSSIDscan();
}

bool displayConnectionDetails(void){
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    // Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    // Serial.print(F("\nIP Addr: ")); 
    cc3000.printIPdotsRev(ipAddress);
   // Serial.print(F("\nNetmask: ")); 
    cc3000.printIPdotsRev(netmask);
   // Serial.print(F("\nGateway: ")); 
    cc3000.printIPdotsRev(gateway);
   // Serial.print(F("\nDHCPsrv: ")); 
    cc3000.printIPdotsRev(dhcpserv);
   // Serial.print(F("\nDNSserv: ")); 
    cc3000.printIPdotsRev(dnsserv);
   // Serial.println();
    return true;
  }
}



char HTTPrequest(Adafruit_CC3000_Client client){
  
  if (client.connected()) {
    client.fastrprint(F("GET "));
    client.fastrprint(WEBPAGE);
    client.fastrprint(F(" HTTP/1.1\r\n"));
    client.fastrprint(F("Host: ")); client.fastrprint(WEBSITE); client.fastrprint(F("\r\n"));
    client.fastrprint(F("\r\n"));
    client.println();
  } else {
   Serial.println(F("Connection failed"));    
    return NULL;
  }

//  Serial.println(F("-------------------------------------"));
  
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  unsigned long lastRead = millis();
  while (client.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    int i=0;
    
    while (client.available()) {
      char c = client.read();
      
      //viene stampato il dato
    Serial.print(c);
      info[i]=c;
      i++;
      lastRead = millis();
    }
  }
  return 1;
}

