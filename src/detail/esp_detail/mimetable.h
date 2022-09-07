/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.9.2

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
 *****************************************************************************************************************************/

#pragma once

#ifndef __ESP_MIMETABLE_H__
#define __ESP_MIMETABLE_H__

#if (ESP32 || ESP8266)

#include "WString.h"

namespace mime_esp
{
  enum type
  {
    html,
    htm,
    txt,
  #ifndef MIMETYPE_MINIMAL    // allow to compile with only the strict minimum of mime-types
    css,
    js,
    json,
    png,
    gif,
    jpg,
    jpeg,
    ico,
    svg,
    ttf,
    otf,
    woff,
    woff2,
    eot,
    sfnt,
    xml,
    pdf,
    zip,
    appcache,
  #endif // MIMETYPE_MINIMAL
    gz,
    none,
    maxType
  };
  
  struct Entry
  {
    const char * endsWith;
    const char * mimeType;
  };
  
  extern const Entry mimeTable[maxType];
  
  String getContentType(const String& path);
}

#endif    // #if (ESP32 || ESP8266)
#endif    // #ifndef __ESP_MIMETABLE_H__
