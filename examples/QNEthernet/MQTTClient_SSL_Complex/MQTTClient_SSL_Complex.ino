/****************************************************************************************************************************
  MQTTClient_SSL_Complex.ino - Dead simple SSL MQTT Client for Ethernet shields

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 *****************************************************************************************************************************/

/*
  Basic MQTT example (with SSL!)
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - publishes {Hello from MQTTClient_SSL on SAM DUE, millis = xxxxx} to the topic [MQTT_Pub]
  - subscribes to the topic [MQTT_Sub], printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  You will need to populate "certificates.h" with your trust anchors
  (see https://github.com/OPEnSLab-OSU/SSLClient/blob/master/TrustAnchors.md)
  and my_cert/my_key with your certificate/private key pair
  (see https://github.com/OPEnSLab-OSU/SSLClient#mtls).
*/

#include "defines.h"

#include "certificates.h"     // This file must be regenerated at https://openslab-osu.github.io/bearssl-certificate-utility/
#include <PubSubClient.h>

const char my_cert[]  = "FIXME";
const char my_key[]   = "FIXME";

SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof my_cert, my_key, sizeof my_key);

const char* mqttServer = "broker.emqx.io";        // Broker address

const char *ID        = "MQTTClient_SSL-Client";  // Name of our device, must be unique
const char *TOPIC     = "MQTT_Pub";               // Topic to subcribe to
const char *subTopic  = "MQTT_Sub";               // Topic to subcribe to

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

EthernetClient    ethClient;
EthernetSSLClient ethClientSSL(ethClient, TAs, (size_t)TAs_NUM);

PubSubClient client(mqttServer, 8883, callback, ethClientSSL);

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqttServer);

    // Attempt to connect
    if (client.connect(ID))
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from MQTTClient_SSL_Complex on " + String(BOARD_NAME);

      client.publish(TOPIC, data.c_str());

      //Serial.println("Published connection message successfully!");
      //Serial.print("Subcribed to: ");
      //Serial.println(subTopic);
      
      // ... and resubscribe
      client.subscribe(subTopic);
      // for loopback testing
      client.subscribe(TOPIC);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStarting MQTTClient_SSL_Complex on "); Serial.print(BOARD_NAME);
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

  // give the Ethernet shield 2 seconds to initialize:
  delay(5000);
}

#define MQTT_PUBLISH_INTERVAL_MS       5000L

void loop()
{
  static unsigned long now;
  
  if (!client.connected())
  {
    reconnect();
  }

  // Sending Data
  now = millis();

  if (now - lastMsg > MQTT_PUBLISH_INTERVAL_MS)
  {
    lastMsg = now;

    String data = "Hello from MQTTClient_SSL_Complex on " + String(BOARD_NAME) + ", millis = " + String(millis());

    if (!client.publish(TOPIC, data.c_str()))
    {
      Serial.println("Message failed to send.");
    }

    Serial.print("Message Send : " + String(TOPIC) + " => ");
    Serial.println(data);
  }
  
  client.loop();
}
