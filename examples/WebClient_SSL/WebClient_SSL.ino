/****************************************************************************************************************************
  WebClient_SSL.ino - Dead simple SSL WebClient for Ethernet shields
  
  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 *****************************************************************************************************************************/

// This sample sketch connects to SSL website (https://www.arduino.cc/asciilogo.txt)
// Generate trust_achors.h at https://openslab-osu.github.io/bearssl-certificate-utility/
  
#include "defines.h"

// You must have SSL Certificates here
#include "trust_anchors.h"

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// Raw IP address not accepted in SSL
//IPAddress server_host(104, 22, 48, 75);

const char      server_host[]   = "www.arduino.cc"; // leave this alone, change only above two
const uint16_t  server_port     = 443;

// Choose the analog pin to get semi-random data from for SSL
// Pick a pin that's not connected or attached to a randomish voltage source
const int rand_pin = A0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM);

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;

bool printWebData = true;  // set to false for better speed measurement

void initEthernet()
{
#if USE_ETHERNET_PORTENTA_H7
  ET_LOGWARN(F("======== USE_PORTENTA_H7_ETHERNET ========"));
#elif USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_ETHERNET_GENERIC
  ET_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));  
#elif USE_ETHERNET_ESP8266
  ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
#else
  ET_LOGWARN(F("========================="));
#endif

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)

#if (USING_SPI2)
  #if defined(CUR_PIN_MISO)
    ET_LOGWARN(F("Default SPI pinout:"));
    ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
    ET_LOGWARN(F("========================="));
  #endif
#else
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));
#endif

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif

  ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // For ESP8266
    // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
    // EthernetGeneric    X                 X            X            X            X        0
    // Ethernet_ESP8266   0                 0            0            0            0        0
    // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
    // Must use library patch for Ethernet, EthernetLarge libraries
    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
  
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif defined(ESP32)

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   5   //22    // For ESP32
  #endif

  ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
    // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN); 
  
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  ET_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
     
  #endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  #if defined(BOARD_NAME)
    ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  #else
    ET_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
  #endif

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#endif    // defined(ESP8266)

#endif    // #if !(USE_NATIVE_ETHERNET)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)
  ET_LOGWARN(F("========================="));
  
  #if defined( ESP32 )
    // Just info to know how to connect correctly
    // To change for other SPI
    ET_LOGWARN(F("Currently Used SPI pinout:"));
    ET_LOGWARN1(F("MOSI:"), PIN_MOSI);
    ET_LOGWARN1(F("MISO:"), PIN_MISO);
    ET_LOGWARN1(F("SCK:"),  PIN_SCK);
    ET_LOGWARN1(F("SS:"),   PIN_SS);
  #else
    #if defined(CUR_PIN_MISO)
      ET_LOGWARN(F("Currently Used SPI pinout:"));
      ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
      ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
      ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
      ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
    #else
      ET_LOGWARN(F("Currently Used SPI pinout:"));
      ET_LOGWARN1(F("MOSI:"), MOSI);
      ET_LOGWARN1(F("MISO:"), MISO);
      ET_LOGWARN1(F("SCK:"),  SCK);
      ET_LOGWARN1(F("SS:"),   SS);
    #endif
  #endif
  
  ET_LOGWARN(F("========================="));

#elif (USE_ETHERNET_PORTENTA_H7)
  if (Ethernet.hardwareStatus() == EthernetNoHardware) 
  {
    Serial.println("No Ethernet found. Stay here forever");
    
    while (true) 
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Not connected Ethernet cable");
  }
#endif

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart WebClient_SSL on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);

  initEthernet();

  // give the Ethernet shield a second to initialize:
  delay(2000);

  Serial.print("Connecting to : ");
  Serial.print(server_host);
  Serial.print(", port : ");
  Serial.println(server_port);

  // if you get a connection, report back via serial:
  auto start = millis();

  // specify the server and port, 443 is the standard port for HTTPS
  if (sslClient.connect(server_host, server_port))
  {
    auto time = millis() - start;
    Serial.print("Connected to ");

#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET_ENC || USE_UIP_ETHERNET )
    Serial.println(client.remoteIP());  
#else    
    Serial.println(server_host); 
#endif
    
    Serial.print("Took: ");
    Serial.println(time);

    // Make a HTTP request:
    sslClient.println("GET /asciilogo.txt HTTP/1.1");
    sslClient.println("User-Agent: SSLClientOverEthernet");
    sslClient.print("Host: ");
    sslClient.println(server_host);
    sslClient.println("Connection: close");
    sslClient.println();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("Connection failed");
  }

  beginMicros = micros();

  
#if 1
  // For testing only to use micros() instead of analogRead()
  uint8_t rng_seeds[16];
  // take the bottom 8 bits of the analog read
  
  // KH mod to use micro()
  Serial.println("Using micros()");
  
  for (uint8_t i = 0; i < sizeof rng_seeds; i++)
  {
    rng_seeds[i] = static_cast<uint8_t>((uint16_t) micros() * (uint16_t) (micros() >> 8));
    Serial.print(rng_seeds[i], HEX);
    Serial.print(" ");
  }
  
  Serial.println("\nUsing analogRead()");
  
  for (uint8_t i = 0; i < sizeof rng_seeds; i++)
  {
    rng_seeds[i] = static_cast<uint8_t>(analogRead(rand_pin));
    Serial.print(rng_seeds[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
#endif
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = sslClient.available();

  if (len > 0)
  {
    byte buffer[80];

    if (len > 80)
      len = 80;

    sslClient.read(buffer, len);

    if (printWebData)
    {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }

    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the sslClient:
  if (!sslClient.connected())
  {
    endMicros = micros();

    Serial.println();
    Serial.println("Disconnecting.");
    sslClient.stop();

    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(" s, rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true)
    {
      delay(1);
    }
  }
}
