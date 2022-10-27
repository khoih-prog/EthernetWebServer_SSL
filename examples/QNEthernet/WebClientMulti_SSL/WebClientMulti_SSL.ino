/****************************************************************************************************************************
  WebClientMulti_SSL.ino - Dead simple SSL WebClient for Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 *****************************************************************************************************************************/

// This sketch connects to SSL websites (https://www.arduino.cc/asciilogo.txt) and (https://www.cloudflare.com/cdn-cgi/trace)
// Generate trustachors.h at https://openslab-osu.github.io/bearssl-certificate-utility/

#include "defines.h"

// You must have SSL Certificates here
#include "trustanchors.h"

// the two domains we want to query
char server1[] = "www.arduino.cc";
char server2[] = "www.cloudflare.com";
// and the queries we want to send to them
char query1[] = "GET /asciilogo.txt HTTP/1.1";
char query2[] = "GET /cdn-cgi/trace HTTP/1.1";

const uint16_t  server_port = 443;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM);

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
unsigned long loopCount = 0;

bool printWebData = true;  // set to false for better speed measurement

void connectSSL()
{
  static bool r = true;
  // cycle the server we want to connect to back and forth
  char* server;
  char* query;

  if (r)
  {
    server  = server1;
    query   = query1;
  }
  else
  {
    server  = server2;
    query   = query2;
  }

  r = !r;

  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  auto start = millis();

  if (sslClient.connect(server, server_port))
  {
    auto time = millis() - start;

    Serial.print("Took: ");
    Serial.println(time);

    // Make a HTTP request:
    sslClient.println(query);
    sslClient.println("User-Agent: SSLClientOverEthernet");
    sslClient.print("Host: ");
    sslClient.println(server);
    sslClient.println("Connection: close");
    sslClient.println();
    sslClient.flush();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  beginMicros = micros();
}

void initEthernet()
{
#if USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_QN_ETHERNET
  ET_LOGWARN(F("=========== USE_QN_ETHERNET ==========="));
#else
  ET_LOGWARN(F("========================="));
#endif

#if USE_NATIVE_ETHERNET

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  // give the Ethernet shield 2 seconds to initialize:
  delay(2000);

#else

#if USING_DHCP
  // Start the Ethernet connection, using DHCP
  Serial.print("Initialize Ethernet using DHCP => ");
  Ethernet.begin();
#else
  // Start the Ethernet connection, using static IP
  Serial.print("Initialize Ethernet using static IP => ");
  Ethernet.begin(myIP, myNetmask, myGW);
  Ethernet.setDNSServerIP(mydnsServer);
#endif

  if (!Ethernet.waitForLocalIP(5000))
  {
    Serial.println("Failed to configure Ethernet");

    if (!Ethernet.linkStatus())
    {
      Serial.println("Ethernet cable is not connected.");
    }

    // Stay here forever
    while (true)
    {
      delay(1);
    }
  }

  if (!Ethernet.waitForLink(5000))
  {
    Serial.println(F("Failed to wait for Link"));
  }
  else
  {
    Serial.print("IP Address = ");
    Serial.println(Ethernet.localIP());
  }

#endif
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while (!Serial);

  Serial.print("\nStarting WebClientMulti_SSL on ");
  Serial.print(BOARD_NAME);
  Serial.print(" " );
  Serial.println(SHIELD_TYPE);
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);

  // Enable mutual TLS with SSLClient
  //ethClientSSL.setMutualAuthParams(mTLS);


  initEthernet();

  // connect!
  connectSSL();
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = sslClient.available();

  if (len > 0)
  {
    byte buffer[80];

    if (len > 80)
      len = 80;

    sslClient.read(buffer, len);

    if (printWebData)
    {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }

    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the sslClient:
  if (!sslClient.connected())
  {
    endMicros = micros();

    Serial.println();
    Serial.println("Disconnecting.");
    sslClient.stop();

    Serial.print("LoopCount ");
    Serial.print(++loopCount);

    Serial.print(", Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(" s, rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // Reset
    byteCount = 0;

    //quick delay
    delay(10000);
    // connect again!
    connectSSL();
  }
}
