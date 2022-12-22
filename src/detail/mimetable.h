/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL

  Version: 1.10.0

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
  1.10.0  K Hoang      22/12/2022 Fix compile errors for new ESP32 core v2.0.6
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


