/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.8.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  ...
  1.7.0   K Hoang      19/12/2021 Reduce usage of Arduino String with std::string. Add support to Portenta H7 Ethernet
  1.7.1   K Hoang      25/12/2021 Fix bug relating to String
  1.7.2   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.7.3   K Hoang      11/01/2022 Fix libb64 compile error for ESP8266
  1.7.4   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
  1.7.5   K Hoang      02/03/2022 Fix decoding error bug
  1.7.6   K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  1.7.7   K Hoang      14/03/2022 Change licence from `MIT` to `GPLv3`
  1.7.8   K Hoang      29/03/2022 Sync with `SSLClient` v1.6.11
  1.8.0   K Hoang      05/04/2022 Use Ethernet_Generic library as default. Support SPI2 for ESP32
  1.8.1   K Hoang      09/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
 *****************************************************************************************************************************/
 
#pragma once

#ifndef __MIMETABLE_H__
#define __MIMETABLE_H__

namespace mime
{

enum type
{
  html,
  htm,
  css,
  txt,
  js,
  json,
  png,
  gif,
  jpg,
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
  gz,
  appcache,
  none,
  maxType
};

struct Entry
{
  const char endsWith[16]; 
  const char mimeType[32];
};

// Table of extension->MIME strings stored in PROGMEM, needs to be global due to GCC section typing rules
const Entry mimeTable[maxType] = 
{
    { ".html",      "text/html" },
    { ".htm",       "text/html" },
    { ".css",       "text/css" },
    { ".txt",       "text/plain" },
    { ".js",        "application/javascript" },
    { ".json",      "application/json" },
    { ".png",       "image/png" },
    { ".gif",       "image/gif" },
    { ".jpg",       "image/jpeg" },
    { ".ico",       "image/x-icon" },
    { ".svg",       "image/svg+xml" },
    { ".ttf",       "application/x-font-ttf" },
    { ".otf",       "application/x-font-opentype" },
    { ".woff",      "application/font-woff" },
    { ".woff2",     "application/font-woff2" },
    { ".eot",       "application/vnd.ms-fontobject" },
    { ".sfnt",      "application/font-sfnt" },
    { ".xml",       "text/xml" },
    { ".pdf",       "application/pdf" },
    { ".zip",       "application/zip" },
    { ".gz",        "application/x-gzip" },
    { ".appcache",  "text/cache-manifest" },
    { "",           "application/octet-stream" } 
};  //extern const Entry mimeTable[maxType];
}   // namespace mime

#endif  // __MIMETABLE_H__


