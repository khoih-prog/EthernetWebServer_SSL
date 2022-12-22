/****************************************************************************************************************************
  RequestHandlerImpl.h - Dead simple web-server.
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

#ifndef REQUEST_HANDLER_IMPL_H
#define REQUEST_HANDLER_IMPL_H

#if !(ESP32 || ESP8266)
#include "RequestHandler.h"
#include "mimetable.h"

class FunctionRequestHandler : public RequestHandler
{
  public:

    FunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn,
                           const String &uri, const HTTPMethod& method)
      : _fn(fn)
      , _ufn(ufn)
      , _uri(uri)
      , _method(method)
    {
    }

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (_method != HTTP_ANY && _method != requestMethod)
        return false;

      if (requestUri == _uri)
        return true;

      if (_uri.endsWith("/*"))
      {
        String _uristart = _uri;
        _uristart.replace("/*", "");

        if (requestUri.startsWith(_uristart))
          return true;
      }

      return false;
    }

    bool canUpload(const String& requestUri) override
    {
      if (!_ufn || !canHandle(HTTP_POST, requestUri))
        return false;

      return true;
    }

    bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri) override
    {
      ETW_UNUSED(server);

      if (!canHandle(requestMethod, requestUri))
        return false;

      _fn();
      return true;
    }

    void upload(EthernetWebServer& server, const String& requestUri, const HTTPUpload& upload) override
    {
      ETW_UNUSED(server);
      ETW_UNUSED(upload);

      if (canUpload(requestUri))
        _ufn();
    }

  protected:
    EthernetWebServer::THandlerFunction _fn;
    EthernetWebServer::THandlerFunction _ufn;
    String      _uri;
    HTTPMethod  _method;
};

class StaticRequestHandler : public RequestHandler
{
  public:

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (requestMethod != HTTP_GET)
        return false;

      if ((_isFile && requestUri != _uri) || !requestUri.startsWith(_uri))
        return false;

      return true;
    }

#if USE_NEW_WEBSERVER_VERSION

    static String getContentType(const String& path)
    {
      using namespace mime;
      char buff[sizeof(mimeTable[0].mimeType)];

      // Check all entries but last one for match, return if found
      for (size_t i = 0; i < sizeof(mimeTable) / sizeof(mimeTable[0]) - 1; i++)
      {
        strcpy(buff, mimeTable[i].endsWith);

        if (path.endsWith(buff))
        {
          strcpy(buff, mimeTable[i].mimeType);
          return String(buff);
        }
      }

      // Fall-through and just return default type
      strcpy(buff, mimeTable[sizeof(mimeTable) / sizeof(mimeTable[0]) - 1].mimeType);
      return String(buff);
    }

#else

    static String getContentType(const String& path)
    {
      if (path.endsWith(".html"))
        return "text/html";
      else if (path.endsWith(".htm"))
        return "text/html";
      else if (path.endsWith(".css"))
        return "text/css";
      else if (path.endsWith(".txt"))
        return "text/plain";
      else if (path.endsWith(".js"))
        return "application/javascript";
      else if (path.endsWith(".png"))
        return "image/png";
      else if (path.endsWith(".gif"))
        return "image/gif";
      else if (path.endsWith(".jpg"))
        return "image/jpeg";
      else if (path.endsWith(".ico"))
        return "image/x-icon";
      else if (path.endsWith(".svg"))
        return "image/svg+xml";
      else if (path.endsWith(".ttf"))
        return "application/x-font-ttf";
      else if (path.endsWith(".otf"))
        return "application/x-font-opentype";
      else if (path.endsWith(".woff"))
        return "application/font-woff";
      else if (path.endsWith(".woff2"))
        return "application/font-woff2";
      else if (path.endsWith(".eot"))
        return "application/vnd.ms-fontobject";
      else if (path.endsWith(".sfnt"))
        return "application/font-sfnt";
      else if (path.endsWith(".xml"))
        return "text/xml";
      else if (path.endsWith(".pdf"))
        return "application/pdf";
      else if (path.endsWith(".zip"))
        return "application/zip";
      else if (path.endsWith(".gz"))
        return "application/x-gzip";
      else if (path.endsWith(".appcache"))
        return "text/cache-manifest";

      return "application/octet-stream";
    }

#endif

  protected:

    String _uri;
    String _path;
    String _cache_header;
    bool _isFile;
    size_t _baseUriLength;
};

#else
#include "ESP_RequestHandlersImpl.h"
#endif

#endif  // REQUEST_HANDLER_IMPL_H

