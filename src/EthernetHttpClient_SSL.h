/****************************************************************************************************************************
  EthernetHttpClient_SSL.h - Dead simple HTTP WebClient.
  For Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.7.7

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
 *****************************************************************************************************************************/

// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2016
// Released under Apache License, version 2.0

#pragma once

#include <Arduino.h>

#include "detail/Debug.h"
#include "Ethernet_HTTPClient/Ethernet_HttpClient.h"
#include "Ethernet_HTTPClient/Ethernet_WebSocketClient.h"
#include "Ethernet_HTTPClient/Ethernet_URLEncoder.h"

