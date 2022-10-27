/****************************************************************************************************************************
  MQTTS_ThingStream.ino - Dead simple SSL MQTT Client for Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
 *****************************************************************************************************************************/

/*
  Basic MQTT example (with SSL!)
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - publishes {Hello from MQTTS_ThingStream on NUCLEO_F767ZI} to the topic [STM32_Pub]
  - subscribes to the topic [STM32_Sub], printing out any messages
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

#define USING_THINGSTREAM_IO      false   //true

#if USING_THINGSTREAM_IO

  const char *MQTT_PREFIX_TOPIC   = "esp32-sniffer/";
  const char *MQTT_ANNOUNCE_TOPIC = "/status";
  const char *MQTT_CONTROL_TOPIC  = "/control";
  const char *MQTT_BLE_TOPIC      = "/ble";

  // GOT FROM ThingsStream!
  const char *MQTT_SERVER     = "mqtt.thingstream.io";
  const char *MQTT_USER       = "MQTT_USER";
  const char *MQTT_PASS       = "MQTT_PASS";
  const char *MQTT_CLIENT_ID  = "MQTT_CLIENT_ID";

  String topic    = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;
  String subTopic = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;

#else
  const char* MQTT_SERVER = "broker.emqx.io";        // Broker address

  const char*  ID         = "MQTTClient_SSL-Client";  // Name of our device, must be unique
  String      topic       = "STM32_Pub";              // Topic to subcribe to
  String      subTopic    = "STM32_Sub";              // Topic to subcribe to

#endif

void mqtt_receive_callback(char* topic, byte* payload, unsigned int length);

const int   MQTT_PORT           = 8883; //if you use SSL //1883 no SSL

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors


EthernetClient    ethClient;
EthernetSSLClient ethClientSSL(ethClient, TAs, (size_t)TAs_NUM, 1, EthernetSSLClient::SSL_NONE);
// Debug, max_sessions = 1, debug = SSL_INFO
//EthernetSSLClient ethClientSSL(ethClient, TAs, (size_t)TAs_NUM, 1, EthernetSSLClient::SSL_INFO);

PubSubClient client(MQTT_SERVER, MQTT_PORT, mqtt_receive_callback, ethClientSSL);

/*
   Called whenever a payload is received from a subscribed MQTT topic
*/
void mqtt_receive_callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("MQTT Message receive [");
  Serial.print(topic);
  Serial.print("] ");

  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}


void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.println(MQTT_SERVER);

    // Attempt to connect

#if USING_THINGSTREAM_IO
    int connect_status = client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS, topic.c_str(), 2, false, "");
#else
    int connect_status = client.connect(ID);
#endif

    if (connect_status)
    {
      Serial.println("...connected");

      // Once connected, publish an announcement...
      String data = "Hello from MQTTS_ThingStream on " + String(BOARD_NAME);

      client.publish(topic.c_str(), data.c_str());

      Serial.println("Published connection message successfully!");

      Serial.print("Subcribed to: ");
      Serial.println(subTopic);

      // ... and resubscribe
      client.subscribe(subTopic.c_str());
      // for loopback testing
      client.subscribe(topic.c_str());
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

  Serial.print("\nStarting MQTTS_ThingStream on ");
  Serial.print(BOARD_NAME);
  Serial.print(" " );
  Serial.println(SHIELD_TYPE);
  Serial.println(ETHERNET_WEBSERVER_SSL_VERSION);

  // Enable mutual TLS with SSLClient
  //ethClientSSL.setMutualAuthParams(mTLS);


  initEthernet();

  // Note - the default maximum packet size is 256 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  //client.setBufferSize(256);

  Serial.println("***************************************");
  Serial.println(topic);
  Serial.println("***************************************");
}

#define MQTT_PUBLISH_INTERVAL_MS      5000L

String data         = "Hello from MQTTS_ThingStream on " + String(BOARD_NAME) + " with " + String(SHIELD_TYPE);
const char *pubData = data.c_str();

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

    if (!client.publish(topic.c_str(), pubData))
    {
      Serial.println("Message failed to send.");
    }

    Serial.print("MQTT Message Send : " + topic + " => ");
    Serial.println(data);
  }

  client.loop();
}
