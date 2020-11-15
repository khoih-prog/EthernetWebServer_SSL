/****************************************************************************************************************************
  MQTTClient_Auth.ino - Dead simple SSL MQTT Client for Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license

  Version: 1.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
 *****************************************************************************************************************************/

/*
  Basic MQTT example (without SSL!) with Authentication
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - providing username and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.
*/

#include "defines.h"

#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* mqttServer = "broker.example"; // Broker address
//IPAddress mqttServer(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

EthernetClient  ethClient;
PubSubClient    client(mqttServer, 1883, callback, ethClient);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart MQTTClient_Auth on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));

#if USE_ETHERNET_WRAPPER

  EthernetInit();

#else

  #if USE_ETHERNET
    ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
  #elif USE_ETHERNET_ESP8266
    ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
  #else
    ET_LOGWARN(F("========================="));
  #endif

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

  #if defined(ESP8266)
    // For ESP8266, change for other boards if necessary
    #ifndef USE_THIS_SS_PIN
      #define USE_THIS_SS_PIN   D2    // For ESP8266
    #endif
  
    ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);
  
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
      // For ESP8266
      // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
      // Ethernet           0                 X            X            X            X        0
      // Ethernet2          X                 X            X            X            X        0
      // Ethernet3          X                 X            X            X            X        0
      // EthernetLarge      X                 X            X            X            X        0
      // Ethernet_ESP8266   0                 0            0            0            0        0
      // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
      // Must use library patch for Ethernet, EthernetLarge libraries
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
      #ifndef ETHERNET3_MAX_SOCK_NUM
        #define ETHERNET3_MAX_SOCK_NUM      4
      #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
    
    #elif USE_CUSTOM_ETHERNET
    
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      Ethernet.init(USE_THIS_SS_PIN);
    
    #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
  #elif defined(ESP32)
  
    #ifndef USE_THIS_SS_PIN
      #define USE_THIS_SS_PIN   22    // For ESP32
    #endif
  
    ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);
  
    // For other boards, to change if necessary
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
      // Must use library patch for Ethernet, EthernetLarge libraries
      // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
      // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
    
      //Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
      #ifndef ETHERNET3_MAX_SOCK_NUM
        #define ETHERNET3_MAX_SOCK_NUM      4
      #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
    
    #elif USE_CUSTOM_ETHERNET
    
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      Ethernet.init(USE_THIS_SS_PIN);
  
    #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
  #else   //defined(ESP8266)
    // unknown board, do nothing, use default SS = 10
    #ifndef USE_THIS_SS_PIN
      // Select USE_THIS_SS_PIN as follows
      //  10    // Most Arduino shields
      //   5    // MKR ETH shield
      //   0    // Teensy 2.0
      //  20    // Teensy++ 2.0
      //  15    // ESP8266 with Adafruit Featherwing Ethernet
      //  33    // ESP32 with Adafruit Featherwing Ethernet
      #define USE_THIS_SS_PIN   10    // For other boards
    #endif
  
    ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  
    // For other boards, to change if necessary
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
      // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
    
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
    
    #elif USE_CUSTOM_ETHERNET
    
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      Ethernet.init(USE_THIS_SS_PIN);
    
    #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
  #endif    //defined(ESP8266)


#endif  //USE_ETHERNET_WRAPPER


  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);
#if USE_ETHERNET3
  Serial.print("SPI_CS:");
  Serial.println(SPI_CS);
#endif
  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
  
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
  
  if (client.connect("arduinoClient", "testuser", "testpass")) 
  {
    client.publish("outTopic", "hello world");
    client.subscribe("inTopic");
  }
}

void loop()
{
  client.loop();
}
