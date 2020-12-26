/****************************************************************************************************************************
  Ethernet_URLEncoder.h - Dead simple HTTP WebClient.
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
 
// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2019
// Released under Apache License, version 2.0

#pragma once

#include <Arduino.h>

#include "detail/Debug.h"


class EthernetURLEncoderClass
{
  public:
    EthernetURLEncoderClass();
    virtual ~EthernetURLEncoderClass();

    static String encode(const char* str);
    static String encode(const String& str);

  private:
    static String encode(const char* str, int length);
};

extern EthernetURLEncoderClass EthernetURLEncoder;
