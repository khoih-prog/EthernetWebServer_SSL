/****************************************************************************************************************************
  base64.h - c source to a base64 encoding algorithm implementation

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 *****************************************************************************************************************************/

#pragma once

// Reintroduce to prevent duplication compile error if other lib/core already has LIB64
// pragma once can't prevent that
#ifndef BASE64_H
#define BASE64_H

int base64_encode(const unsigned char* aInput, int aInputLen, unsigned char* aOutput, int aOutputLen);

#endif  // BASE64_H

