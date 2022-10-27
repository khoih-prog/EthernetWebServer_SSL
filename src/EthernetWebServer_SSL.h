/****************************************************************************************************************************
  EthernetWebServer_SSL.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL

  Version: 1.9.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  ...
  1.8.0   K Hoang      05/04/2022 Use Ethernet_Generic library as default. Support SPI2 for ESP32
  1.8.1   K Hoang      09/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  1.8.2   K Hoang      27/04/2022 Change from `arduino.cc` to `arduino.tips` in examples
  1.9.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  1.9.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  1.9.2   K Hoang      07/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  1.9.3   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
 *****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_SSL_H
#define ETHERNET_WEBSERVER_SSL_H

#define ETHERNET_WEBSERVER_SSL_VERSION          "EthernetWebServer_SSL v1.9.3"

#define ETHERNET_WEBSERVER_SSL_VERSION_MAJOR    1
#define ETHERNET_WEBSERVER_SSL_VERSION_MINOR    9
#define ETHERNET_WEBSERVER_SSL_VERSION_PATCH    3

#define ETHERNET_WEBSERVER_SSL_VERSION_INT      1009003

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #if defined(ETHERNET_USE_PORTENTA_H7)
    #undef ETHERNET_USE_PORTENTA_H7
  #endif
  #define ETHERNET_USE_PORTENTA_H7        true

  #if defined(USE_NEW_WEBSERVER_VERSION)
    #undef USE_NEW_WEBSERVER_VERSION
  #endif
  #define USE_NEW_WEBSERVER_VERSION   false

  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Use mbed-portenta architecture for PORTENTA_H7 from EthernetWebServer_SSL
  #endif
#endif
/////////////////////////////////////////////////////////////////////////

#if USE_UIP_ETHERNET
#if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
  #warning Using UIPEthernet library from EthernetWebServer
#endif
#elif USE_CUSTOM_ETHERNET
#if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
  #warning Using Custom Ethernet library from EthernetWebServer. You must include a library or error
#endif
#elif !( ETHERNET_USE_PORTENTA_H7 || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || \
         USE_NATIVE_ETHERNET || USE_QN_ETHERNET)
#include <Ethernet_Generic.h>

#if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
  #warning Using Ethernet_Generic library from EthernetWebServer
#endif
#endif

/////////////////////////////////////////////////////////////////////////

#include "EthernetWebServer_SSL.hpp"
#include "EthernetWebServer_SSL-impl.h"
#include "Parsing_SSL-impl.h"

/////////////////////////////////////////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_SSL_H
