/****************************************************************************************************************************
  mimetable.cpp - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.8.2

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
  1.8.2   K Hoang      27/04/2022 Change from `arduino.cc` to `arduino.tips` in examples
 *****************************************************************************************************************************/

#if (ESP32 || ESP8266)

#include "mimetable.h"
#include "pgmspace.h"
#include "WString.h"

namespace mime_esp
{
  static const char kHtmlSuffix[]     PROGMEM = ".html";
  static const char kHtmSuffix[]      PROGMEM = ".htm";
  static const char kTxtSuffix[]      PROGMEM = ".txt";
  
  #ifndef MIMETYPE_MINIMAL
  static const char kCssSuffix[]      PROGMEM = ".css";
  static const char kJsSuffix[]       PROGMEM = ".js";
  static const char kJsonSuffix[]     PROGMEM = ".json";
  static const char kPngSuffix[]      PROGMEM = ".png";
  static const char kGifSuffix[]      PROGMEM = ".gif";
  static const char kJpgSuffix[]      PROGMEM = ".jpg";
  static const char kJpegSuffix[]     PROGMEM = ".jpeg";
  static const char kIcoSuffix[]      PROGMEM = ".ico";
  static const char kSvgSuffix[]      PROGMEM = ".svg";
  static const char kTtfSuffix[]      PROGMEM =  ".ttf";
  static const char kOtfSuffix[]      PROGMEM = ".otf";
  static const char kWoffSuffix[]     PROGMEM = ".woff";
  static const char kWoff2Suffix[]    PROGMEM = ".woff2";
  static const char kEotSuffix[]      PROGMEM = ".eot";
  static const char kSfntSuffix[]     PROGMEM = ".sfnt";
  static const char kXmlSuffix[]      PROGMEM = ".xml";
  static const char kPdfSuffix[]      PROGMEM = ".pdf";
  static const char kZipSuffix[]      PROGMEM = ".zip";
  static const char kAppcacheSuffix[] PROGMEM = ".appcache";
  #endif // MIMETYPE_MINIMAL
  
  static const char kGzSuffix[]       PROGMEM = ".gz";
  static const char kDefaultSuffix[]  PROGMEM = "";
  
  static const char kHtml[]           PROGMEM = "text/html";
  static const char kTxt[]            PROGMEM = "text/plain";
  
  #ifndef MIMETYPE_MINIMAL
  static const char kCss[]            PROGMEM = "text/css";
  static const char kJs[]             PROGMEM = "application/javascript";
  static const char kJson[]           PROGMEM = "application/json";
  static const char kPng[]            PROGMEM = "image/png";
  static const char kGif[]            PROGMEM = "image/gif";
  static const char kJpg[]            PROGMEM = "image/jpeg";
  static const char kJpeg[]           PROGMEM = "image/jpeg";
  static const char kIco[]            PROGMEM = "image/x-icon";
  static const char kSvg[]            PROGMEM = "image/svg+xml";
  static const char kTtf[]            PROGMEM = "application/x-font-ttf";
  static const char kOtf[]            PROGMEM = "application/x-font-opentype";
  static const char kWoff[]           PROGMEM = "application/font-woff";
  static const char kWoff2[]          PROGMEM = "application/font-woff2";
  static const char kEot[]            PROGMEM = "application/vnd.ms-fontobject";
  static const char kSfnt[]           PROGMEM = "application/font-sfnt";
  static const char kXml[]            PROGMEM = "text/xml";
  static const char kPdf[]            PROGMEM = "application/pdf";
  static const char kZip[]            PROGMEM = "application/zip";
  static const char kAppcache[]       PROGMEM = "text/cache-manifest";
  #endif // MIMETYPE_MINIMAL
  
  static const char kGz[]             PROGMEM = "application/x-gzip";
  static const char kDefault[]        PROGMEM = "application/octet-stream";
  
  const Entry mimeTable[maxType]      PROGMEM =
  {
    { kHtmlSuffix,      kHtml },
    { kHtmSuffix,       kHtml },
    { kTxtSuffix,       kTxt },
  #ifndef MIMETYPE_MINIMAL
    { kCssSuffix,       kCss },
    { kJsSuffix,        kJs },
    { kJsonSuffix,      kJson },
    { kPngSuffix,       kPng },
    { kGifSuffix,       kGif },
    { kJpgSuffix,       kJpg },
    { kJpegSuffix,      kJpeg },
    { kIcoSuffix,       kIco },
    { kSvgSuffix,       kSvg },
    { kTtfSuffix,       kTtf },
    { kOtfSuffix,       kOtf },
    { kWoffSuffix,      kWoff },
    { kWoff2Suffix,     kWoff2 },
    { kEotSuffix,       kEot },
    { kSfntSuffix,      kSfnt },
    { kXmlSuffix,       kXml },
    { kPdfSuffix,       kPdf },
    { kZipSuffix,       kZip },
    { kAppcacheSuffix,  kAppcache },
  #endif // MIMETYPE_MINIMAL
    { kGzSuffix,        kGz },
    { kDefaultSuffix,   kDefault }
  };
  
  String getContentType(const String& path) 
  {
    for (size_t i = 0; i < maxType; i++) 
    {
      if (path.endsWith(FPSTR(mimeTable[i].endsWith))) 
      {
        return String(FPSTR(mimeTable[i].mimeType));
      }
    }
    
    // Fall-through and just return default type
    return String(FPSTR(kDefault));
  }

}   // namespace mime_esp

#endif
