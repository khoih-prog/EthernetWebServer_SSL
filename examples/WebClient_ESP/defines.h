/****************************************************************************************************************************
  defines.h
  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 ***************************************************************************************************************************************/

#pragma once

#ifndef defines_h
#define defines_h

#if !( defined( ESP32 ) || defined( ESP8266 ))
  #error This code is designed to run on ESP32 or ESP8266 platform! Please check your Tools->Board setting.
#endif

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3


#if ( defined(ESP8266) )
  // For ESP8266
  #warning Use ESP8266 architecture
  #include <ESP8266mDNS.h>
  #define ETHERNET_USE_ESP8266
  #define BOARD_TYPE      ARDUINO_BOARD

#elif ( defined(ESP32) )
  // For ESP32
  #warning Use ESP32 architecture
  #define ETHERNET_USE_ESP32
  #define BOARD_TYPE      ARDUINO_BOARD

  #define W5500_RST_PORT   21

#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

//#define USE_UIP_ETHERNET   true
#define USE_UIP_ETHERNET   false

// Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
// In order to USE_ETHERNET_ESP8266
#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

  // To override the default CS/SS pin. Don't use unless you know exactly which pin to use
  // You can define here or customize for each board at same place with BOARD_TYPE
  // Check @ defined(SEEED_XIAO_M0)
  //#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15

  // Only one if the following to be true
  #define USE_ETHERNET_GENERIC  true
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false

  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC )
    #ifdef USE_CUSTOM_ETHERNET
      #undef USE_CUSTOM_ETHERNET
    #endif
    #define USE_CUSTOM_ETHERNET   false
  #endif

  #if USE_ETHERNET_GENERIC
    #if (ESP32)
      #include <soc/spi_pins.h>

      // Optional SPI2
      //#define USING_SPI2                          true

      #if USING_SPI2
        #define PIN_MISO          HSPI_IOMUX_PIN_NUM_MISO
        #define PIN_MOSI          HSPI_IOMUX_PIN_NUM_MOSI
        #define PIN_SCK           HSPI_IOMUX_PIN_NUM_CLK
        #define PIN_SS            HSPI_IOMUX_PIN_NUM_CS

        #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI2"

      #else

        #define PIN_MISO          MISO
        #define PIN_MOSI          MOSI
        #define PIN_SCK           SCK
        #define PIN_SS            SS

        #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI"

      #endif

    #else
      #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library"
    #endif

    #define ETHERNET_LARGE_BUFFERS

    #define _ETG_LOGLEVEL_                      1

    #include "Ethernet_Generic.h"
    #warning Using Ethernet_Generic lib

  #elif USE_ETHERNET_ESP8266
    #include "Ethernet_ESP8266.h"
    #warning Using Ethernet_ESP8266 lib
    #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library"
  #elif USE_ETHERNET_ENC
    #include "EthernetENC.h"
    #warning Using EthernetENC lib
    #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
  #elif USE_CUSTOM_ETHERNET
    //#include "Ethernet_XYZ.h"
    #include "EthernetENC.h"
    #warning Using Custom Ethernet library. You must include a library and initialize.
    #define SHIELD_TYPE           "Custom Ethernet using Ethernet_XYZ Library"
  #else
    #ifdef USE_ETHERNET_GENERIC
      #undef USE_ETHERNET_GENERIC
    #endif
    #define USE_ETHERNET_GENERIC   true
    #include "Ethernet_Generic.h"
    #warning Using default Ethernet_Generic lib
    #define SHIELD_TYPE           "W5x00 using default Ethernet_Generic Library"
  #endif

  // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
  // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
  // Otherwise, standard Ethernet library will be used for W5x00

#elif USE_UIP_ETHERNET
  #include "UIPEthernet.h"
  #warning Using UIPEthernet library
  #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
#endif      // #if !USE_UIP_ETHERNET

#include <EthernetWebServer_SSL.h>

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library"
#endif

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

// Google DNS Server IP
IPAddress myDns(8, 8, 8, 8);

#endif
