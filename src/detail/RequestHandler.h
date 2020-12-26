/****************************************************************************************************************************
  RequestHandler.h - Dead simple web-server.
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

#ifndef ETW_UNUSED
  #define ETW_UNUSED(x) (void)(x)
#endif


class RequestHandler
{
  public:

    virtual ~RequestHandler() { }

    virtual bool canHandle(HTTPMethod method, String uri)
    {
      ETW_UNUSED(method);
      ETW_UNUSED(uri);
      
      return false;
    }

    virtual bool canUpload(String uri)
    {
      ETW_UNUSED(uri);
      
      return false;
    }

    virtual bool handle(EthernetWebServer& server, HTTPMethod requestMethod, String requestUri)
    {
      ETW_UNUSED(server);
      ETW_UNUSED(requestMethod);
      ETW_UNUSED(requestUri);
      
      return false;
    }

    virtual void upload(EthernetWebServer& server, String requestUri, HTTPUpload& upload) 
    {
      ETW_UNUSED(server);
      ETW_UNUSED(requestUri);
      ETW_UNUSED(upload);
    }

    RequestHandler* next()
    {
      return _next;
    }

    void next(RequestHandler* r)
    {
      _next = r;
    }

  private:

    RequestHandler* _next = nullptr;
};

