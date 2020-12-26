/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license
       
  Version: 1.3.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.3.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
  1.3.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
 *****************************************************************************************************************************/
 
#pragma once

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
};
//extern const Entry mimeTable[maxType];
}

