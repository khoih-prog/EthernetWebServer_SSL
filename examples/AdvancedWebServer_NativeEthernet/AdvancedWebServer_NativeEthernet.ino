/****************************************************************************************************************************
  AdvancedWebServer_NativeEthernet.h - Dead simple web-server for Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL

  Copyright (c) 2015, Majenko Technologies
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Majenko Technologies nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************************************/
/*
   The Arduino board communicates with the shield using the SPI bus. This is on digital pins 11, 12, and 13 on the Uno
   and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used as SS. On the Mega, the hardware SS pin, 53,
   is not used to select the Ethernet controller chip, but it must be kept as an output or the SPI interface won't work.
*/

#include "defines.h"

EthernetWebServer server(80);

int reqCount = 0;                // number of requests received

void handleRoot()
{
#define BUFFER_SIZE     512

  char temp[BUFFER_SIZE];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>AdvancedWebServer %s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>Hi from EthernetWebServer_SSL!</h2>\
<h3>on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
<img src=\"/test.svg\" />\
</body>\
</html>", BOARD_NAME, BOARD_NAME, day, hr % 24, min % 60, sec % 60);

  server.send(200, F("text/html"), temp);
}

void handleNotFound()
{
  String message = F("File Not Found\n\n");

  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, F("text/plain"), message);
}

#define ORIGINAL_STR_LEN        2048

void drawGraph()
{
  static String out;
  static uint16_t previousStrLen = ORIGINAL_STR_LEN;

  if (out.length() == 0)
  {
    ET_LOGWARN1(F("String Len = 0, extend to"), ORIGINAL_STR_LEN);
    out.reserve(ORIGINAL_STR_LEN);
  }

  out = F( "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"310\" height=\"150\">\n" \
           "<rect width=\"310\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"3\" stroke=\"rgb(0, 0, 0)\" />\n" \
           "<g stroke=\"blue\">\n");

  char temp[70];

  int y = rand() % 130;

  for (int x = 10; x < 300; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }

  out += F("</g>\n</svg>\n");

  ET_LOGDEBUG1(F("String Len = "), out.length());

  if (out.length() > previousStrLen)
  {
    ET_LOGERROR3(F("String Len > "), previousStrLen, F(", extend to"), out.length() + 48);

    previousStrLen = out.length() + 48;

    out.reserve(previousStrLen);
  }
  else
  {
    server.send(200, "image/svg+xml", out);
  }
}

void setup(void)
{
  Serial.begin(115200);

  while (!Serial);

  Serial.print("\nStarting AdvancedWebServer_NativeEthernet on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);

  // start the ethernet connection and the server:
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  Serial.print(F("Using mac index = "));
  Serial.println(index);

#if USING_STATIC_IP
  // Static IP
  //Ethernet.begin(mac, ip, gateway, subnet);
  Ethernet.begin(mac[index], ip);

  delay(2000);
#else
  // DHCP
  Ethernet.begin(mac[index]);

  delay(1000);
#endif

  Serial.print(F("EthernetWebServer started @ IP address: "));
  Serial.println(Ethernet.localIP());

  // give the Ethernet shield 2 seconds to initialize:
  delay(2000);

  server.on(F("/"), handleRoot);
  server.on(F("/test.svg"), drawGraph);
  server.on(F("/inline"), []()
  {
    server.send(200, F("text/plain"), F("This works as well"));
  });

  server.onNotFound(handleNotFound);
  server.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(Ethernet.localIP());
}

void heartBeatPrint(void)
{
  static int num = 1;

  Serial.print(F("."));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     10000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void loop(void)
{
  server.handleClient();
  check_status();
}
