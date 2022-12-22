/****************************************************************************************************************************
  mimetable.cpp - Dead simple web-server.
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
