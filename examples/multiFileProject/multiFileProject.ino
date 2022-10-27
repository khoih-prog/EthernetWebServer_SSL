/****************************************************************************************************************************
  multiFileProject.ino
  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define ETHERNET_WEBSERVER_SSL_VERSION_MIN_TARGET      "EthernetWebServer_SSL v1.9.3"
#define ETHERNET_WEBSERVER_SSL_VERSION_MIN             1009003

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <EthernetWebServer_SSL.h>      // https://github.com/khoih-prog/EthernetWebServer_SSL

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(500);

  Serial.println("\nStart multiFileProject");
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);

#if defined(ETHERNET_WEBSERVER_SSL_VERSION_MIN)

  if (ETHERNET_WEBSERVER_SSL_VERSION_INT < ETHERNET_WEBSERVER_SSL_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(ETHERNET_WEBSERVER_SSL_VERSION_MIN_TARGET);
  }

#endif

  Serial.print("You're OK now");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
