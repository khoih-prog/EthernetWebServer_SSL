/****************************************************************************************************************************
  multiFileProject.h
  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <EthernetWebServer_SSL.hpp>      // https://github.com/khoih-prog/EthernetWebServer_SSL

#include <EthernetHttpClient_SSL.h>       // https://github.com/khoih-prog/EthernetWebServer_SSL
