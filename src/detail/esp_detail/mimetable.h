/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.7.8

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
