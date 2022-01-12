/****************************************************************************************************************************
  RequestHandlerImpl.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license
       
  Version: 1.7.4

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.3.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
  1.3.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
  1.4.0   K Hoang      13/05/2021 Add support to RP2040-based boards using Arduino mbed_rp2040 core
  1.5.0   K Hoang      15/05/2021 Add support to RP2040-based boards using Arduino-pico rp2040 core
  1.6.0   K Hoang      04/09/2021 Add support to QNEthernet Library for Teensy 4.1
  1.6.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
  1.7.0   K Hoang      19/12/2021 Reduce usage of Arduino String with std::string. Add support to Portenta H7 Ethernet
  1.7.1   K Hoang      25/12/2021 Fix bug relating to String
  1.7.2   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.7.3   K Hoang      11/01/2022 Fix libb64 compile error for ESP8266
  1.7.4   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
 *************************************************************************************************************************************/

#pragma once

#if !(ESP32 || ESP8266)
#include "RequestHandler.h"
#include "mimetable.h"

class FunctionRequestHandler : public RequestHandler
{
  public:

    FunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn, const String &uri, const HTTPMethod& method)
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
      if (path.endsWith(".html"))           return "text/html";
      else if (path.endsWith(".htm"))       return "text/html";
      else if (path.endsWith(".css"))       return "text/css";
      else if (path.endsWith(".txt"))       return "text/plain";
      else if (path.endsWith(".js"))        return "application/javascript";
      else if (path.endsWith(".png"))       return "image/png";
      else if (path.endsWith(".gif"))       return "image/gif";
      else if (path.endsWith(".jpg"))       return "image/jpeg";
      else if (path.endsWith(".ico"))       return "image/x-icon";
      else if (path.endsWith(".svg"))       return "image/svg+xml";
      else if (path.endsWith(".ttf"))       return "application/x-font-ttf";
      else if (path.endsWith(".otf"))       return "application/x-font-opentype";
      else if (path.endsWith(".woff"))      return "application/font-woff";
      else if (path.endsWith(".woff2"))     return "application/font-woff2";
      else if (path.endsWith(".eot"))       return "application/vnd.ms-fontobject";
      else if (path.endsWith(".sfnt"))      return "application/font-sfnt";
      else if (path.endsWith(".xml"))       return "text/xml";
      else if (path.endsWith(".pdf"))       return "application/pdf";
      else if (path.endsWith(".zip"))       return "application/zip";
      else if (path.endsWith(".gz"))        return "application/x-gzip";
      else if (path.endsWith(".appcache"))  return "text/cache-manifest";

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

