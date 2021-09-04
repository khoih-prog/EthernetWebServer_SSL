/****************************************************************************************************************************
  WebClient_SSL.ino - Dead simple SSL WebClient for Ethernet shields
  
  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license
 *****************************************************************************************************************************/

// This sample sketch connects to SSL website (https://www.arduino.cc/asciilogo.txt)
// Generate trust_achors.h at https://openslab-osu.github.io/bearssl-certificate-utility/
  
#include "defines.h"

// You must have SSL Certificates here
#include "trust_anchors.h"

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// Raw IP address not accepted in SSL
//IPAddress server_host(104, 22, 48, 75);

const char      server_host[]   = "www.arduino.cc"; // leave this alone, change only above two
const uint16_t  server_port     = 443;

// Choose the analog pin to get semi-random data from for SSL
// Pick a pin that's not connected or attached to a randomish voltage source
const int rand_pin = A0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM);

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;

bool printWebData = true;  // set to false for better speed measurement

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStarting WebClient_SSL on "); Serial.print(BOARD_NAME);
  Serial.print(" " ); Serial.println(SHIELD_TYPE);
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);
  
  // Enable mutual TLS with SSLClient
  //ethClientSSL.setMutualAuthParams(mTLS);
  

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
  else
  {
    Serial.print("IP Address = ");
    Serial.println(Ethernet.localIP());
  }

#endif

  // give the Ethernet shield a second to initialize:
  delay(2000);

  Serial.print("Connecting to : ");
  Serial.print(server_host);
  Serial.print(", port : ");
  Serial.println(server_port);

  // if you get a connection, report back via serial:
  auto start = millis();

  // specify the server and port, 443 is the standard port for HTTPS
  if (sslClient.connect(server_host, server_port))
  {
    auto time = millis() - start;
    Serial.print("Connected to ");

#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET_ENC || USE_UIP_ETHERNET )
    Serial.println(client.remoteIP());  
#else    
    Serial.println(server_host); 
#endif
    
    Serial.print("Took: ");
    Serial.println(time);

    // Make a HTTP request:
    sslClient.println("GET /asciilogo.txt HTTP/1.1");
    sslClient.println("User-Agent: SSLClientOverEthernet");
    sslClient.print("Host: ");
    sslClient.println(server_host);
    sslClient.println("Connection: close");
    sslClient.println();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("Connection failed");
  }

  beginMicros = micros();

  
#if 1
  // For testing only to use micros() instead of analogRead()
  uint8_t rng_seeds[16];
  // take the bottom 8 bits of the analog read
  
  // KH mod to use micro()
  Serial.println("Using micros()");
  
  for (uint8_t i = 0; i < sizeof rng_seeds; i++)
  {
    rng_seeds[i] = static_cast<uint8_t>((uint16_t) micros() * (uint16_t) (micros() >> 8));
    Serial.print(rng_seeds[i], HEX);
    Serial.print(" ");
  }
  
  Serial.println("\nUsing analogRead()");
  
  for (uint8_t i = 0; i < sizeof rng_seeds; i++)
  {
    rng_seeds[i] = static_cast<uint8_t>(analogRead(rand_pin));
    Serial.print(rng_seeds[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
#endif
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

    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(" s, rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true)
    {
      delay(1);
    }
  }
}
