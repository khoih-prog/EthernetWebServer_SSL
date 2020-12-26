/****************************************************************************************************************************
  Ethernet_URLEncoder.cpp - Dead simple HTTP WebClient.
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

#define _ETHERNET_WEBSERVER_LOGLEVEL_     0

#include "detail/Debug.h"
#include "Ethernet_HTTPClient/Ethernet_URLEncoder.h"

EthernetURLEncoderClass::EthernetURLEncoderClass()
{
}

EthernetURLEncoderClass::~EthernetURLEncoderClass()
{
}

String EthernetURLEncoderClass::encode(const char* str)
{
  return encode(str, strlen(str));
}

String EthernetURLEncoderClass::encode(const String& str)
{
  return encode(str.c_str(), str.length());
}

String EthernetURLEncoderClass::encode(const char* str, int length)
{
  String encoded;

  encoded.reserve(length);

  for (int i = 0; i < length; i++) 
  {
    char c = str[i];

    const char HEX_DIGIT_MAPPER[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if (isAlphaNumeric(c) || (c == '-') || (c == '.') || (c == '_') || (c == '~')) 
    {
      encoded += c;
    } 
    else 
    {
      char s[4];

      s[0] = '%';
      s[1] = HEX_DIGIT_MAPPER[(c >> 4) & 0xf];
      s[2] = HEX_DIGIT_MAPPER[(c & 0x0f)];
      s[3] = 0;

      encoded += s;
    }
  }

  return encoded;
}

EthernetURLEncoderClass EthernetURLEncoder;
