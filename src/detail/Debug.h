/****************************************************************************************************************************
  Debug.h - Dead simple Ethernet web-server.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.9.0

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
  1.9.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
 *****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_DEBUG_H
#define ETHERNET_WEBSERVER_DEBUG_H

#include <stdio.h>

#ifdef DEBUG_ETHERNET_WEBSERVER_PORT
#define ET_DEBUG_OUTPUT DEBUG_ETHERNET_WEBSERVER_PORT
#else
#define ET_DEBUG_OUTPUT Serial
#endif

// Change _ETHERNET_WEBSERVER_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ETHERNET_WEBSERVER_LOGLEVEL_
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#endif

///////////////////////////////////////

const char EWS_MARK[]  = "[EWS] ";
const char EWS_SPACE[] = " ";
const char EWS_LINE[]  = "========================================\n";

#define EWS_PRINT_MARK   EWS_PRINT(EWS_MARK)
#define EWS_PRINT_SP     EWS_PRINT(EWS_SPACE)
#define EWS_PRINT_LINE   EWS_PRINT(EWS_LINE)

#define EWS_PRINT        ET_DEBUG_OUTPUT.print
#define EWS_PRINTLN      ET_DEBUG_OUTPUT.println

///////////////////////////////////////

#define ET_LOGERROR(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGERROR_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGERROR0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT(x); }
#define ET_LOGERROR1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGERROR2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGERROR3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGWARN(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGWARN_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGWARN0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT(x); }
#define ET_LOGWARN1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGWARN2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGWARN3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGINFO(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGINFO_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGINFO0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT(x); }
#define ET_LOGINFO1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGINFO2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGINFO3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGDEBUG(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGDEBUG_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGDEBUG0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT(x); }
#define ET_LOGDEBUG1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGDEBUG2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGDEBUG3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_DEBUG_H

