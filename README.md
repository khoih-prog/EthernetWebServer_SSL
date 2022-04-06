## EthernetWebServer_SSL

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer_SSL.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer_SSL.svg)](http://github.com/khoih-prog/EthernetWebServer_SSL/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this EthernetWebServer_SSL library](#why-do-we-need-this-ethernetwebserver_ssl-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Configuration Notes](#configuration-notes)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
  * [Important](#important)
  * [2. How to select another CS/SS pin to use](#2-how-to-select-another-csss-pin-to-use)
  * [3. How to use W5x00 with ESP8266](#3-how-to-use-w5x00-with-esp8266)
  * [4. How to increase W5x00 TX/RX buffer](#4-how-to-increase-w5x00-txrx-buffer)
  * [5. How to adjust sendContent_P() and send_P() buffer size](#5-how-to-adjust-sendcontent_p-and-send_p-buffer-size)
  * [6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library](#6-How-to-use-SPI2-for-ESP32-using-W5x00-and-Ethernet_Generic-Library)
* [WebServer and non TLS/SSL WebClient Usage](#webserver-and-non-tlsssl-webclient-usage)
  * [Init the CS/SS pin if use EthernetWrapper](#init-the-csss-pin-if-use-ethernetwrapper) 
  * [Class Constructor](#class-constructor)
  * [Basic Operation](#basic-operations)
  * [Advanced Options](#advanced-options)
  * [Other Function Calls](#other-function-calls)
* [TLS/SSL WebClient Usage](#tlsssl-webclient-usage)
  * [Overview](#overview) 
    * [1. Board and Network Peripheral Requirements](#1-board-and-network-peripheral-requirements)
    * [2. How to use Trust Anchors TA](#2-how-to-use-trust-anchors-ta)
    * [3. Note](#3-note)
* [How It Works](#how-it-works)
* [Other Features](#other-features)
  * [Logging](#logging) 
  * [Errors](#errors)
  * [Write Buffering](#write-buffering)
  * [Session Caching](#session-caching)
  * [mTLS](#mtls)
* [Implementation Notes](#implementation-notes)
  * [Seeding Random Data](#seeding-random-data) 
  * [Certificate Verification](#certificate-verification)
  * [Resources](#resources)
  * [Read Buffer Overflow](#read-buffer-overflow)
  * [Cipher Support](#cipher-support)
  * [Known Issues](#known-issues) 
* [Examples](#examples)
  * [WebServer, TLS/SSL Client Examples](#webserver-tlsssl-client-examples)
    * [ 1. AdvancedWebServer](examples/AdvancedWebServer)
    * [ 2. HelloServer](examples/HelloServer)
    * [ 3. HelloServer2](examples/HelloServer2)
    * [ 4. HttpBasicAuth](examples/HttpBasicAuth)
    * [ 5. MQTTClient_Auth](examples/MQTTClient_Auth)
    * [ 6. MQTTClient_Basic](examples/MQTTClient_Basic)
    * [ 7. MQTTClient_SSL](examples/MQTTClient_SSL)
    * [ 8. MQTTClient_SSL_Auth](examples/MQTTClient_SSL_Auth)
    * [ 9. MQTTClient_SSL_Complex](examples/MQTTClient_SSL_Complex)
    * [10. PostServer](examples/PostServer)
    * [11. SimpleAuthentication](examples/SimpleAuthentication)
    * [12. UdpNTPClient](examples/UdpNTPClient)
    * [13. UdpSendReceive](examples/UdpSendReceive)
    * [14. WebClient](examples/WebClient)
    * [15. WebClientMulti_SSL](examples/WebClientMulti_SSL)
    * [16. WebClientRepeating](examples/WebClientRepeating)
    * [17. WebClient_SSL](examples/WebClient_SSL)
    * [18. WebServer](examples/WebServer)
    * [19. **MQTTS_ThingStream**](examples/MQTTS_ThingStream).
    * [20. **MQTT_ThingStream**](examples/MQTT_ThingStream).
    * [21. **AdvancedWebServer_NativeEthernet**](examples/AdvancedWebServer_NativeEthernet)
    * [22. **WebClientMulti_SSL_NativeEthernet**](examples/WebClientMulti_SSL_NativeEthernet)
    * [23. **AWS_IoT**](examples/AWS_IoT) **New**
    * [24. multiFileProject](examples/multiFileProject) **New**
  * [HTTP and WebSocket Client New Examples](#http-and-websocket-client-new-examples)
    * [ 1. BasicAuthGet](examples/HTTPClient/BasicAuthGet)
    * [ 2. CustomHeader](examples/HTTPClient/CustomHeader)
    * [ 3. DweetGet](examples/HTTPClient/DweetGet)
    * [ 4. DweetPost](examples/HTTPClient/DweetPost)
    * [ 5. HueBlink](examples/HTTPClient/HueBlink)
    * [ 6. node_test_server](examples/HTTPClient/node_test_server)
    * [ 7. PostWithHeaders](examples/HTTPClient/PostWithHeaders)
    * [ 8. SimpleDelete](examples/HTTPClient/SimpleDelete)
    * [ 9. SimpleGet](examples/HTTPClient/SimpleGet)
    * [10. SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
    * [11. SimplePost](examples/HTTPClient/SimplePost)
    * [12. SimplePut](examples/HTTPClient/SimplePut)
    * [13. SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)
  * [New Examples for Teensy 4.1 QNEthernet](#new-examples-for-teensy-41-qnethernet)
    * [ 1. **AdvancedWebServer_QNEthernet**](examples/QNEthernet/AdvancedWebServer_QNEthernet)
    * [ 2. **MQTTClient_SSL**](examples/QNEthernet/MQTTClient_SSL)
    * [ 3. **MQTTClient_SSL_Auth**](examples/QNEthernet/MQTTClient_SSL_Auth)
    * [ 4. **MQTTClient_SSL_Complex**](examples/QNEthernet/MQTTClient_SSL_Complex)
    * [ 5. **MQTTS_ThingStream**](examples/QNEthernet/MQTTS_ThingStream)
    * [ 6. WebClientMulti_SSL](examples/QNEthernet/WebClientMulti_SSL)
    * [ 7. WebClient_SSL](examples/QNEthernet/WebClient_SSL)
* [Example AdvancedWebServer](#example-advancedwebserver)
  * [1. File AdvancedWebServer.ino](#1-file-advancedwebserverino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AdvancedWebServer on NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library](#1-advancedwebserver-on-nrf52840_feather_express-with-enc28j60-using-ethernetenc-library)
  * [2. ENC28J60_WM_Config on ESP32 with ENC28J60 using UIPEthernet Library](#2-enc28j60_wm_config-on-esp32-with-enc28j60-using-uipethernet-library)
  * [3. WebClientMulti_SSL on SAM DUE with W5x00 using Ethernet_Generic Library](#3-webclientmulti_ssl-on-sam-due-with-w5x00-using-Ethernet_Generic-library)
  * [4. WebClient_SSL on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library](#4-webclient_ssl-on-seeed_xiao_m0-with-w5x00-using-Ethernet_Generic-library)
  * [5. MQTTClient_SSL_Complex on SAM DUE with W5x00 using Ethernet_Generic Library](#5-mqttclient_ssl_complex-on-sam-due-with-w5x00-using-Ethernet_Generic-library)
  * [6. MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library](#6-mqtts_thingstream-on-seeed_xiao_m0-with-w5x00-using-Ethernet_Generic-library)
  * [7. MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#7-mqtts_thingstream-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [8. MQTTClient_SSL on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#8-mqttclient_ssl-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [9. AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#9-advancedwebserver-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [10. MQTTClient_SSL on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#10-mqttclient_ssl-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [11. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#11-advancedwebserver-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [12. AdvancedWebServer_QNEthernet on Teensy 4.1 using QNEthernet Library](#12-advancedwebserver_qnethernet-on-teensy-41-using-qnethernet-library)
  * [13. MQTTClient_SSL on Teensy 4.1 using QNEthernet Library](#13-mqttclient_ssl-on-teensy-41-using-qnethernet-library)
  * [14. WebClientMulti_SSL on Teensy 4.1 using QNEthernet Library](#14-webclientmulti_ssl-on-teensy-41-using-qnethernet-library)
  * [15. AdvancedWebServer on PORTENTA_H7_M7 using Portenta_Ethernet Library](#15-AdvancedWebServer-on-PORTENTA_H7_M7-using-Portenta_Ethernet-Library)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [EthernetWebServer_SSL library](https://github.com/khoih-prog/EthernetWebServer_SSL)

#### Features

This [EthernetWebServer_SSL library](https://github.com/khoih-prog/EthernetWebServer_SSL) is a simple yet complete TLS/SSL WebClient and non-TLS/SSL WebServer library for **Teensy, SAM DUE, Arduino SAMD21, Adafruit SAMD21/SAMD51, Adafruit nRF52, ESP32/ESP8266, STM32, etc.** boards using Ethernet shields. The functions are similar and compatible to those of [`ESP32 WebServer`](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) and [`ESP8266WebServer`](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) libraries to make life much easier to port sketches from ESP8266/ESP32.

The **RP2040-based boards, such as RASPBERRY_PI_PICO**, are currently supported using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core v1.3.1+](https://github.com/earlephilhower/arduino-pico).

This [EthernetWebServer_SSL library](https://github.com/khoih-prog/EthernetWebServer_SSL) adds [TLS 1.2](https://www.websecurity.digicert.com/security-topics/what-is-ssl-tls-https) functionality to EthernetClient, using BearSSL as an underlying TLS engine.

This [**EthernetWebServer_SSL library**](https://github.com/khoih-prog/EthernetWebServer_SSL), from v1.2.0, also provides high-level **HTTP and WebSocket Client** with the functions are similar and compatible to those of [**ArduinoHttpClient Library**](https://github.com/arduino-libraries/ArduinoHttpClient)

The library provides these features:

1. TCP Server and Client
2. UDP Server and Client
3. HTTP Server and HTTP/HTTPS Client
4. HTTPS GET and POST requests, provides argument parsing, handles one client at a time.
5. **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**. From v1.2.0.

Library is based on and modified from:

1. [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
2. [Ivan Grokhotkov's ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
3. [OPEnSLab-OSU's SSLClient v1.6.9](https://github.com/OPEnSLab-OSU/SSLClient)
4. [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)

The EthernetWebServer class, found in `EthernetWebServer.h` header, is a simple WebServer class, knowing how to handle HTTP requests such as GET and POST and can only support one one client at a time.

The EthernetSSLClient class, found in `SSLClient.h` header, is a simple WebClient class, knowing how to handle HTTP/HTTPS requests such as GET and POST and can only support one client at a time.

#### Currently supported Boards

This [**EthernetWebServer_SSL** library](https://github.com/khoih-prog/EthernetWebServer_SSL) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**. Currently SSL WebClient is not working.
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - SeeedStudio:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: WIO Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 6. **AVR Mega1280, 2560, ADK.**. SSL WebClient not supported yet. Check [Trivial sketch won't compile using Arduino 1.8.13](https://github.com/mike-matera/ArduinoSTL/issues/56)
 7. ESP32
 8. ESP8266. SSL WebClient not supported yet. Check [HTTPS GET request - ESP8266 - ENC28j60](https://github.com/OPEnSLab-OSU/SSLClient/issues/5)
 9. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
 
 10. **Portenta_H7**

#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
2. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
3. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
4. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library

5. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library


---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.9+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`ESP32 Core 2.0.2+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
10. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.0.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v1.13.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`ArduinoCore-fab-sam core v1.16.18-alpha2+`](https://github.com/qbolsee/ArduinoCore-fab-sam) for SAMD21/SAMD51-based boards. [![GitHub release](https://img.shields.io/github/release/qbolsee/ArduinoCore-fab-sam.svg)](https://github.com/qbolsee/ArduinoCore-fab-sam/releases/latest)
14. [`Functional-VLPP library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
15. Depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.0.0+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.2+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.11+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   - [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet.
   - [`QNEthernet Library version v0.13.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. **New**

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `EthernetWebServer_SSL`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL) for more detailed instructions

### Manual Install

1. Navigate to [EthernetWebServer_SSL](https://github.com/khoih-prog/EthernetWebServer_SSL) page.
2. Download the latest release `EthernetWebServer_SSL-main.zip`.
3. Extract the zip file to `EthernetWebServer_SSL-main` directory 
4. Copy the whole `EthernetWebServer_SSL-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**EthernetWebServer_SSL** library](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer_SSL) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer_SSL/installation). Search for EthernetWebServer_SSL in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.9) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.9). 

Supposing the Adafruit SAMD core version is 1.7.9. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.0.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.6.18-alpha2. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`

---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched Ethernet](https://github.com/khoih-prog/Ethernet)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched EthernetLarge](https://github.com/khoih-prog/EthernetLarge)

#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

You can also use the forked and modified library at [Patched Ethernet2](https://github.com/khoih-prog/Ethernet2)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

You can also use the forked and modified library at [Patched Ethernet3](https://github.com/khoih-prog/Ethernet3)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.13/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.13/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### Configuration Notes

#### 1. How to select which built-in Ethernet or shield to use

The easiest way is to use 

```cpp
#define USE_ETHERNET_WRAPPER    true
```

then select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet_Generic library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp

// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          true
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using UIPEthernet library:

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          true
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```


- To use another Ethernet library
For example, EthernetLarge library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       true

//Must be placed before #include <EthernetWebServer.h>
#include <EthernetLarge.h>
...

#include <EthernetWebServer.h>
```

- Only for Teensy 4.1, to use NativeEthernet library

```
#if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
      #define USE_QN_ETHERNET         false
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif      
  #elif defined(__MK66FX1M0__)
  ....
```

- Only for Teensy 4.1, to use another Ethernet library, for example Ethernet_Generic library

```
#if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #if defined(ARDUINO_TEENSY41)
    #define BOARD_TYPE      "TEENSY 4.1"
    // Use true for NativeEthernet Library, false if using other Ethernet libraries
    #define USE_NATIVE_ETHERNET     false
    #define USE_QN_ETHERNET         false
  #elif defined(ARDUINO_TEENSY40)
    #define BOARD_TYPE      "TEENSY 4.0"
  #else
    #define BOARD_TYPE      "TEENSY 4.x"
  #endif      
#elif defined(__MK66FX1M0__)
  ....
  
#define USE_UIP_ETHERNET        false

// Only one if the following to be true
#define USE_ETHERNET_GENERIC    true
#define USE_ETHERNET_ESP8266    false
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false  
```

- Only for Teensy 4.1, to use QNEthernet library

```
#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) ) 
  // For Teensy 4.1
  #define BOARD_TYPE      "TEENSY 4.1"
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true
#else
  #error Only Teensy 4.1 supported
#endif

#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

#define USE_UIP_ETHERNET        false
#define USE_ETHERNET_GENERIC    false
#define USE_ETHERNET_ESP8266    false 
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false

#if USE_NATIVE_ETHERNET
  #include "NativeEthernet.h"
  #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using NativeEthernet"
#elif USE_QN_ETHERNET
  #include "QNEthernet.h"
  using namespace qindesign::network;
  #warning Using QNEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using QNEthernet"  
#endif 
```

---

#### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---

#### 2. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not corect, the easiest way is to change is to use 

```cpp
#define USE_ETHERNET_WRAPPER    true
```

then select the CS/SS pin (e.g. 22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22
```

#### 3. How to use W5x00 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet_Generic, Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00

```cpp
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 4. How to increase W5x00 TX/RX buffer

- For **Ethernet_Generic** library only,  simply use as follows to have large buffer similar to EthernetLarge library
```
#define ETHERNET_LARGE_BUFFERS
```

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```

### 5. How to adjust sendContent_P() and send_P() buffer size

sendContent_P() and send_P() buffer size is set default at 4 Kbytes, and minimum is 256 bytes. If you need to change, just add a definition, e.g.:

```cpp
#define SENDCONTENT_P_BUFFER_SZ     2048
```

Note that the buffer size must be larger than 256 bytes. See [Sending GZIP HTML ~ 120kb+ (suggested enhancement)](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/3).


### 6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only,  simply use as follows to SPI2 for ESP32
```
#define USING_SPI2                          true
```



---
---

### WebServer and non TLS/SSL WebClient Usage

#### Init the CS/SS pin if use EthernetWrapper

```cpp
EthernetInit();
```

#### Class Constructor

```cpp
  EthernetWebServer server(80);
```

Creates the EthernetWebServer class object.

*Parameters:* 
 
host port number: ``int port`` (default is the standard HTTP port 80)

#### Basic Operations

**Starting the server**

```cpp
  void begin();
```

**Handling incoming client requests**

```cpp
  void handleClient();
```

**Disabling the server**

```cpp
  void close();
  void stop();
```

Both methods function the same

**Client request handlers**

```cpp
  void on();
  void addHandler();
  void onNotFound();
  void onFileUpload();	
```

Example:

```cpp
  server.on("/", handlerFunction);
  server.onNotFound(handlerFunction);   // called when handler is not assigned
  server.onFileUpload(handlerFunction); // handle file uploads
```

**Sending responses to the client**

```cpp
  void send();
  void send_P();
```

`Parameters:`

`code` - HTTP response code, can be `200` or `404`, etc.

`content_type` - HTTP content type, like `"text/plain"` or `"image/png"`, etc.

`content` - actual content body

#### Advanced Options

**Getting information about request arguments**

```cpp
  const String & arg();
  const String & argName();
  int args();
  bool hasArg();
```

`Function usage:`

`arg` - get request argument value, use `arg("plain")` to get POST body
	
`argName` - get request argument name
	
`args` - get arguments count
	
`hasArg` - check if argument exist


**Getting information about request headers**

```cpp
  const String & header();
  const String & headerName();
  const String & hostHeader();
  int headers();
  bool hasHeader();
``` 
`Function usage:`

`header` - get request header value

`headerName` - get request header name

`hostHeader` - get request host header if available, else empty string
  
`headers` - get header count
	
`hasHeader` - check if header exist


**Authentication**

```cpp
  bool authenticate();
  void requestAuthentication();
```

`Function usage:`

`authenticate` - server authentication, returns true if client is authenticated else false

`requestAuthentication` - sends authentication failure response to the client

`Example Usage:`

```cpp

  if(!server.authenticate(username, password)){
    server.requestAuthentication();
  }
```

#### Other Function Calls

```cpp
  const String & uri(); // get the current uri
  HTTPMethod  method(); // get the current method 
  WiFiClient client(); // get the current client
  HTTPUpload & upload(); // get the current upload
  void setContentLength(); // set content length
  void sendHeader(); // send HTTP header
  void sendContent(); // send content
  void sendContent_P(); 
  void collectHeaders(); // set the request headers to collect
  void serveStatic();
  size_t streamFile();
```

---

### TLS/SSL WebClient Usage

Have a look at marvellous documentation in [SSLClient](https://openslab-osu.github.io/SSLClient/index.html) for more information about the underlying EthernetSSLClient.

The following info is taken and modified from [SSLClient README](https://github.com/OPEnSLab-OSU/SSLClient/blob/master/README.md)

#### Overview

Using EthernetSSLClient is similar to using any other Arduino-based Client class. There are a few extra things, however, that you will need to get started:

##### 1. Board and Network Peripheral Requirements

Your board should have a lot of resources (>110kb flash and >7kb RAM), and your network peripheral should have a large internal buffer (>7kb).

##### 2. How to use Trust Anchors TA

You will need a header containing array of trust anchors ([trust_anchors](examples/WebClient_SSL/trust_anchors.h)), which are used to verify the SSL connection later on. **This file must generated for every project if connecting to different TLS/SSL WebServers.** Check out [TrustAnchors.md](./TrustAnchors.md#generating-trust-anchors) on how to generate this file for your project, and for more information about what a trust anchor is.


Once all those are ready, you can create an SSLClient object like this:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM)
```

Where:
* `EthernetClient` - The type of `client`
* `client` - An instance of the EthernetClient class you are using for EthernetSSLClient. It is important that this instance be stored *outside* the `EthernetSSLClient` declaration. 

For instance: 

```
EthernetSSLClient(EthernetClient() ...)
```

wouldn't work.

* TAs - The name of the trust anchor array created in step 2. If you generated a header using the tutorial this will probably be `TAs`.
* TAs_NUM -  The number of trust anchors in TAs. If you generated a header using the tutorial this will probably be `TAs_NUM`.


Given this client, simply use `EthernetSSLClient` as you would the base client class:

```C++
if (sslClient.connect(www.arduino.cc, 443))
{
  // Make a HTTP request:
  sslClient.println(GET /asciilogo.txt HTTP/1.1);
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
```

##### 3. Note

`sslClient.connect("www.arduino.cc", 443)` can take 5-15 seconds to finish. This an unavoidable consequence of the SSL protocol, and is detailed in [Implementation Notes](#resources).

For more information on `EthernetSSLClient`, check out the [examples](./examples), [API documentation](https://openslab-osu.github.io/SSLClient/index.html), or the rest of this README.

---

## How It Works

`EthernetSSLClient` was created to integrate SSL seamlessly with the Arduino infrastructure, and so it does just that: implementing the brilliant [BearSSL](https://bearssl.org/) as a proxy in front of any Arduino socket library. `BearSSL` is designed with low flash footprint in mind, and as a result does little verification of improper programming, relying on the developer to ensure the code is correct. Since `EthernetSSLClient` is built specifically for the Arduino ecosystem, most of `EthernetSSLClient`'s code adds those programming checks back in, making debugging a fast and simple process.

## Other Features

### Logging

`EthernetSSLClient` also allows for changing the debugging level by adding an additional parameter to the constructor:

```C++
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, 1, SSLClient::SSL_INFO);)
```

Logging is always outputted through the [Arduino Serial interface](https://www.arduino.cc/reference/en/language/functions/communication/serial/), so you'll need to setup Serial before you can view the SSL logs. Log levels are enumerated in ::DebugLevel. The log level is set to `SSL_WARN` by default.

### Errors

When `EthernetSSLClient` encounters an error, it will attempt to terminate the SSL session gracefully if possible, and then close the socket. Simple error information can be found from EthernetSSLClient::getWriteError(), which will return a value from the ::Error enum. For more detailed diagnostics, you can look at the serial logs, which will be displayed if the log level is at `SSL_ERROR` or lower.

### Write Buffering

As you may have noticed in the documentation for EthernetSSLClient::write, calling this function does not actually write to the network. Instead, you must call EthernetSSLClient::available or EthernetSSLClient::flush, which will detect that the buffer is ready and write to the network (see EthernetSSLClient::write for details).

This was implemented as a buffered function because examples in Arduino libraries will often write to the network like so:

```C++
EthernetClient client;
// ...
// connect to ardiuino.cc over ssl (port 443 for websites)
client.connect("www.arduino.cc", 443);
// ...
// write an http request to the network
client.write("GET /asciilogo.txt HTTP/1.1\r\n");
client.write("Host: arduino.cc\r\n");
client.write("Connection: close\r\n");
// wait for response
while (!client.available()) { /* ... */ }
// ...
```

Notice that every single write() call immediately writes to the network, which is fine with most network clients. With SSL, however, if we are encrypting and writing to the network every write() call, this will result in a lot of small encryption tasks. Encryption takes a lot of time and code, so to reduce the overhead of an SSL connection, SSLClient::write implicitly buffers until the developer states that they are waiting for data to be received with EthernetSSLClient::available. A simple example can be found below:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM)

// ...
// connect to arduino.cc over ssl (port 443 for websites)
sslClient.connect("www.arduino.cc", 443);
// ...
// add http request to the buffer
sslClient.write("GET /asciilogo.txt HTTP/1.1\r\n");
sslClient.write("Host: arduino.cc\r\n");
sslClient.write("Connection: close\r\n");

// write the bytes to the network, then wait for response
while (!sslClient.available());
// ...
```

If you would like to trigger a network write manually without using the EthernetSSLClient::available, you can also call EthernetSSLClient::flush, which will write all data and return when finished.

### Session Caching

As detailed in the [Resources section](#resources), `SSL` handshakes take an extended period (1-4sec) to negotiate. To remedy this problem, BearSSL is able to keep a [SSL session cache](https://bearssl.org/api1.html#session-cache) of the clients it has connected to. If `BearSSL` successfully resumes an `SSL` session, it can reduce connection time to 100-500ms.

In order to use `SSL` session resumption:

 * The website you are connecting to must support it. Support is widespread, but you can verify easily using the [SSLLabs tool](https://www.ssllabs.com/ssltest/).
 *  You must reuse the same `EthernetSSLClient` object (`SSL` Sessions are stored in the object itself).
 *  You must reconnect to the exact same server.

`EthernetSSLClient` automatically stores an IP address and hostname in each session, ensuring that if you call `connect("www.google.com")`, `EthernetSSLClient` will use the `SSL` session with that hostname. However, because some websites have multiple servers on a single IP address (github.com being an example), you may find that even if you are connecting to the same host the connection does not resume. This is a flaw in the SSL session protocol — though it has been resolved in `TLS 1.3`, the lack of widespread adoption of the new protocol prevents it from being used here. SSL sessions can also expire based on server criteria, which will result in a standard 4-10 second connection.

`SSL` sessions take a lot of memory to store, so by default `EthernetSSLClient` will only store one at a time. You can change this behavior by adding the following to your `EthernetSSLClient` declaration:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, SomeNumber);
```

Where `SomeNumber` is the number of sessions you would like to store. For example this declaration can store 3 sessions:

```C++
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, 3);
```

Sessions are managed internally using the `SSLSession::getSession` function. This function will cycle through sessions in a rotating order, allowing the session cache to continually overwrite old sessions. In general, it is a good idea to use a SessionCache size equal to the number of domains you plan on connecting to.

If you need to clear a session, you can do so using the `SSLSession::removeSession` function.

### mTLS

As of `v1.6.0`, `EthernetSSLClient` supports [mutual TLS authentication](https://developers.cloudflare.com/access/service-auth/mtls/). mTLS is a variant of TLS that verifies both the server and device identities before a connection, and is commonly used in IoT protocols as a secure layer (MQTT over TLS, HTTPS over TLS, etc.).

To use `mTLS with SSLClient` you will need to a client certificate and client private key associated with the server you are attempting to connect to.

Depending on your use case, you will either generate these yourself (ex. [Mosquito MQTT setup](http://www.steves-internet-guide.com/creating-and-using-client-certificates-with-mqtt-and-mosquitto/)), or have them generated for you (ex. [AWS IoT Certificate Generation](https://docs.aws.amazon.com/iot/latest/developerguide/create-device-certificate.html)). Given this cryptographic information, you can modify the standard `EthernetSSLClient` connection sketch to enable `mTLS authentication`:

```C++
...
/* Somewhere above setup() */

// The client certificate, can be PEM or DER format
// DER format will be an array of raw bytes, and PEM format will be a string
// PEM format is shown below
const char my_cert[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDpDCCAowCCQC7mCk5Iu3YmDANBgkqhkiG9w0BAQUFADCBkzELMAkGA1UEBhMC\n"
...
"-----END CERTIFICATE-----\n";

// The client private key, must be the same format as the client certificate
// Both RSA and ECC are supported, ECC is shown below
const char my_key[] = 
"-----BEGIN EC PRIVATE KEY-----\n"
...
"-----END EC PRIVATE KEY-----\n";

// This line will parse and store the above information so SSLClient can use it later
// Replace `fromPEM` with `fromDER` if you are using DER formatted certificates.
SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof(cert), my_key, sizeof(key));
EthernetSSLClient my_client(...);
...
void setup() {
    ...
    /* Before SSLClient connects */

    my_client.setMutualAuthParams(mTLS);
    ...
}
...
```

The client certificate must be formatted correctly (according to [BearSSL's specification](https://bearssl.org/apidoc/bearssl__pem_8h.html)) in order for mTLS to work. If the certificate is improperly formatted, SSLClient will attempt to make a regular TLS connection instead of an mTLS one, and fail to connect as a result. Because of this, if you are seeing errors similar to `"peer did not send certificate chain"` on your server, check that your certificate and key are formatted correctly (see [MQTT SSL possible?](https://github.com/OPEnSLab-OSU/SSLClient/issues/7#issuecomment-593704969)). For more information on SSLClient's mTLS functionality, please see the [SSLClientParameters documentation](https://openslab-osu.github.io/SSLClient/class_s_s_l_client_parameters.html).

Note that both the above client certificate information *as well as* the correct trust anchors associated with the server are needed for the connection to succeed. Trust anchors will typically be generated from the CA used to generate the server certificate. More information on generating trust anchors can be found in [TrustAnchors.md](./TrustAnchors.md). 

---
---

## Implementation Notes

Some ideas that didn't quite fit in the API documentation.

### Seeding Random Data

The SSL protocol requires that `EthernetSSLClient` generate some random bits before connecting with a server. `BearSSL` provides a random number generator but requires a [some entropy for a seed](https://bearssl.org/apidoc/bearssl__ssl_8h.html#a7d8e8de2afd49d6794eae02f56f81152). Normally this seed is generated by taking the microsecond time using the internal clock, however since most microcontrollers are not build with this feature another source must be found.

### Certificate Verification

`EthernetSSLClient` uses `BearSSL's` [minimal x509 verification engine](https://bearssl.org/x509.html#the-minimal-engine) to verify the certificate of an `SSL` connection. This engine requires the developer create a trust anchor array using values stored in trusted root certificates. Check out [TrustAnchors document](./TrustAnchors.md) for more details on this component of `EthernetSSLClient`.

`BearSSL` also features a [known certificate validation engine](https://bearssl.org/x509.html#the-known-key-engine), which only allows for a single domain in exchange for a significantly reduced resource usage (flash and CPU time). This functionality is planned to be implemented in the future.

### Resources

The `SSL` protocol recommends a device support many different encryption algorithms, as well as protocols for `SSL` itself. The complexity of both of those components results in many medium sized components forming an extremely large whole. Additionally, most embedded processors lack the sophisticated math hardware commonly found in a modern CPU, and as a result require more instructions to create the encryption algorithms SSL requires. This not only increases size but makes the algorithms slow and memory intensive.

If flash footprint is becoming a problem, there are numerous debugging strings (~3kb estimated) that can be removed from `SSLClient.h` and `SSLClient.cpp`.

### Read Buffer Overflow

`SSL` is a buffered protocol, and since most microcontrollers have limited resources (see [Resources](#resources)), `EthernetSSLClient` is limited in the size of its buffers. A common problem encountered with `SSL` connections is buffer overflow, caused by the server sending too much data at once. This problem is caused by the microcontroller being unable to copy and decrypt data faster than it is being received, forcing some data to be discarded. This usually puts `BearSSL` in an unrecoverable state, forcing `EthernetSSLClient` to close the connection with a write error. If you are experiencing frequent timeout problems, this could be the reason why. 

In order to remedy this problem, the device must be able to read the data faster than it is being received, or alternatively have a cache large enough to store the entire payload. Since `SSL's` encryption forces the device to read slowly, this means we must increase the cache size. Depending on your platform, there are a number of ways this can be done:

* Sometimes your communication shield will have an internal buffer, which can be expanded through the driver code. This is the case with the Arduino Ethernet library (in the form of the `MAX_SOCK_NUM` and `ETHERNET_LARGE_BUFFERS` macros), however the library must be modified for the change to take effect.
* `EthernetSSLClient` has an internal buffer EthernetSSLClient::m_iobuf, which can be expanded. `BearSSL` limits the amount of data that can be processed based on the stage in the SSL handshake, and so this will change will have limited usefulness. 
* In some cases, a website will send so much data that even with the above solutions, `EthernetSSLClient` will be unable to keep up (a website with a lot of HTML is an example). In these cases you will have to find another method of retrieving the data you need.
* If none of the above are viable, it is possible to implement your own Client class which has an internal buffer much larger than both the driver and `BearSSL`. This would require in-depth knowledge of programming and the communication shield you are working with, as well as a microcontroller with a significant amount of RAM.

### Cipher Support

By default, `EthernetSSLClient` supports only TLS1.2 and the ciphers listed in [TLS12_only_profile.c](./src/SSLClient/TLS12_only_profile.c) under `suites[]`, and the list is relatively small to keep the connection secure and the flash footprint down. These ciphers should work for most applications, however if for some reason you would like to use an older version of TLS or a different cipher, you can change the BearSSL profile being used by SSLClient to an [alternate one with support for older protocols](./src/SSLClient/bearssl/src/ssl/ssl_client_full.c). To do this, edit `EthernetSSLClient::EthernetSSLClient` to change these lines:

```C++
br_client_init_TLS12_only(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
// comment the above line and uncomment the line below if you're having trouble connecting over SSL
// br_ssl_client_init_full(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
```
to this:

```C++
// br_client_init_TLS12_only(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
// comment the above line and uncomment the line below if you're having trouble connecting over SSL
br_ssl_client_init_full(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
```
If for some unfortunate reason you need SSL 3.0 or SSL 2.0, you will need to modify the BearSSL profile to enable support. Check out the [BearSSL profiles documentation](https://bearssl.org/api1.html#profiles) and I wish you the best of luck.

### Known Issues

 * In some drivers (Ethernet), calls to `Client::flush` will hang if internet is available but there is no route to the destination. Unfortunately SSLClient cannot correct for this without modifying the driver itself, and as a result the recommended solution is ensuring you choose a driver with built-in timeouts to prevent freezing. Check [Calls to stop before connected cause lockups.](https://github.com/OPEnSLab-OSU/SSLClient/issues/13#issuecomment-643855923).
 
 * When using PubSubClient on the ESP32, a stack overflow will occur if the user does not flush the buffer immediately after writing. The cause of this issue is under active investigation. More information in issue [PubSubClient on ESP32 overflows the stack](https://github.com/OPEnSLab-OSU/SSLClient/issues/9).
 

---
---

### Examples:

#### WebServer, TLS/SSL Client Examples

 1. [AdvancedWebServer](examples/AdvancedWebServer)
 2. [HelloServer](examples/HelloServer)
 3. [HelloServer2](examples/HelloServer2)
 4. [HttpBasicAuth](examples/HttpBasicAuth)
 5. [MQTTClient_Auth](examples/MQTTClient_Auth)
 6. [MQTTClient_Basic](examples/MQTTClient_Basic)
 7. [MQTTClient_SSL](examples/MQTTClient_SSL)
 8. [MQTTClient_SSL_Auth](examples/MQTTClient_SSL_Auth)
 9. [MQTTClient_SSL_Complex](examples/MQTTClient_SSL_Complex)
10. [PostServer](examples/PostServer)
11. [SimpleAuthentication](examples/SimpleAuthentication)
12. [UdpNTPClient](examples/UdpNTPClient)
13. [UdpSendReceive](examples/UdpSendReceive)
14. [WebClient](examples/WebClient)
15. [WebClientMulti_SSL](examples/WebClientMulti_SSL)
16. [WebClientRepeating](examples/WebClientRepeating)
17. [WebClient_SSL](examples/WebClient_SSL)
18. [WebServer](examples/WebServer)
19. [**MQTTS_ThingStream**](examples/MQTTS_ThingStream).
20. [**MQTT_ThingStream**](examples/MQTT_ThingStream).
21. [**AdvancedWebServer_NativeEthernet**](examples/AdvancedWebServer_NativeEthernet).
22. [**WebClientMulti_SSL_NativeEthernet**](examples/WebClientMulti_SSL_NativeEthernet).
23. [**AWS_IoT**](examples/AWS_IoT). **New**
24. [multiFileProject](examples/multiFileProject) **New**

#### HTTP and WebSocket Client New Examples

 1. [BasicAuthGet](examples/HTTPClient/BasicAuthGet)
 2. [CustomHeader](examples/HTTPClient/CustomHeader)
 3. [DweetGet](examples/HTTPClient/DweetGet)
 4. [DweetPost](examples/HTTPClient/DweetPost)
 5. [HueBlink](examples/HTTPClient/HueBlink)
 6. [node_test_server](examples/HTTPClient/node_test_server)
 7. [PostWithHeaders](examples/HTTPClient/PostWithHeaders)
 8. [SimpleDelete](examples/HTTPClient/SimpleDelete)
 9. [SimpleGet](examples/HTTPClient/SimpleGet)
10. [SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
11. [SimplePost](examples/HTTPClient/SimplePost)
12. [SimplePut](examples/HTTPClient/SimplePut)
13. [SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)


#### New Examples for Teensy 4.1 QNEthernet

 1. [AdvancedWebServer_QNEthernet](examples/QNEthernet/AdvancedWebServer_QNEthernet)
 2. [**MQTTClient_SSL**](examples/QNEthernet/MQTTClient_SSL)
 3. [**MQTTClient_SSL_Auth**](examples/QNEthernet/MQTTClient_SSL_Auth)
 4. [**MQTTClient_SSL_Complex**](examples/QNEthernet/MQTTClient_SSL_Complex)
 5. [**MQTTS_ThingStream**](examples/QNEthernet/MQTTS_ThingStream)
 6. [WebClientMulti_SSL](examples/QNEthernet/WebClientMulti_SSL)
 7. [WebClient_SSL](examples/QNEthernet/WebClient_SSL)

---
---

### Example [AdvancedWebServer](examples/AdvancedWebServer)

#### 1. File [AdvancedWebServer.ino](examples/AdvancedWebServer/AdvancedWebServer.ino)

https://github.com/khoih-prog/EthernetWebServer_SSL/blob/4ddbf8a5be6fa7b00373b46b24aa50dbfa0fa2df/examples/AdvancedWebServer/AdvancedWebServer.ino#L44-L409


---

#### 2. File [defines.h](examples/AdvancedWebServer/defines.h)

https://github.com/khoih-prog/EthernetWebServer_SSL/blob/4ddbf8a5be6fa7b00373b46b24aa50dbfa0fa2df/examples/AdvancedWebServer/defines.h#L10-L473

---
---

### Debug Terminal Output Samples

#### 1. AdvancedWebServer on NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/pics/AdvancedWebServer.png">
</p>

```
Starting AdvancedWebServer on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 25
[ETHERNET_WEBSERVER] MISO: 24
[ETHERNET_WEBSERVER] SCK: 26
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 11
Connected! IP address: 192.168.2.96
HTTP EthernetWebServer is @ IP : 192.168.2.96
EthernetWebServer::handleClient: New Client
method:  GET
url:  /
search:
headerName: Host
headerValue: 192.168.2.113
headerName: Connection
headerValue: keep-alive
headerName: DNT
headerValue: 1
headerName: Upgrade-Insecure-Requests
headerValue: 1
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: Accept
headerValue: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  347
content =  <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer NRF52840_FEATHER</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer!</h2><h3>on NRF52840_FEATHER</h3><p>Uptime: 0 d 00:00:11</p><img src="/test.svg" /></body></html>
EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 347
Connection: close

EthernetWebServer::sendContent: Client.write content:  <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer NRF52840_FEATHER</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer_SSL!</h2><h3>on NRF52840_FEATHER</h3><p>Uptime: 0 d 00:00:11</p><img src="/test.svg" /></body></html>
EthernetWebServer::_handleRequest OK
EthernetWebServer::handleClient: Client disconnected
EthernetWebServer::handleClient: Don't keepCurrentClient
EthernetWebServer::handleClient: Client disconnected
EthernetWebServer::handleClient: New Client
method:  GET
url:  /test.svg
search:
headerName: Host
headerValue: 192.168.2.113
headerName: Connection
headerValue: keep-alive
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: DNT
headerValue: 1
headerName: Accept
headerValue: image/webp,image/apng,image/*,*/*;q=0.8
headerName: Referer
headerValue: http://192.168.2.113/
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /test.svg
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  1950
content =  <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="310" height="150">
<rect width="310" height="150" fill="rgb(250, 230, 210)" stroke-width="1" stroke="rgb(0, 0, 0)" />
<g stroke="black">
<line x1="10" y1="98" x2="20" y2="111" stroke-width="1" />
<line x1="20" y1="111" x2="30" y2="90" stroke-width="1" />
<line x1="30" y1="90" x2="40" y2="22" stroke-width="1" />
<line x1="40" y1="22" x2="50" y2="98" stroke-width="1" />
<line x1="50" y1="98" x2="60" y2="64" stroke-width="1" />
<line x1="60" y1="64" x2="70" y2="104" stroke-width="1" />
<line x1="70" y1="104" x2="80" y2="31" stroke-width="1" />
<line x1="80" y1="31" x2="90" y2="59" stroke-width="1" />
<line x1="90" y1="59" x2="100" y2="139" stroke-width="1" />
<line x1="100" y1="139" x2="110" y2="117" stroke-width="1" />
<line x1="110" y1="117" x2="120" y2="75" stroke-width="1" />
<line x1="120" y1="75" x2="130" y2="72" stroke-width="1" />
<line x1="130" y1="72" x2="140" y2="137" stroke-width="1" />
<line x1="140" y1="137" x2="150" y2="20" stroke-width="1" />
<line x1="150" y1="20" x2="160" y2="94" stroke-width="1" />
<line x1="160" y1="94" x2="170" y2="81" stroke-width="1" />
<line x1="170" y1="81" x2="180" y2="38" stroke-width="1" />
<line x1="180" y1="38" x2="190" y2="33" stroke-width="1" />
<line x1="190" y1="33" x2="200" y2="53" stroke-width="1" />
<line x1="200" y1="53" x2="210" y2="88" stroke-width="1" />
<line x1="210" y1="88" x2="220" y2="32" stroke-width="1" />
<line x1="220" y1="32" x2="230" y2="110" stroke-width="1" />
<line x1="230" y1="110" x2="240" y2="87" stroke-width="1" />
<line x1="240" y1="87" x2="250" y2="11" stroke-width="1" />
<line x1="250" y1="11" x2="260" y2="98" stroke-width="1" />
<line x1="260" y1="98" x2="270" y2="76" stroke-width="1" />
<line x1="270" y1="76" x2="280" y2="121" stroke-width="1" />
<line x1="280" y1="121" x2="290" y2="139" stroke-width="1" />
<line x1="290" y1="139" x2="300" y2="103" stroke-width="1" />
</g>
</svg>

EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: image/svg+xml
Content-Length: 1950
Connection: close
```

---

#### 2. ENC28J60_WM_Config on ESP32 with ENC28J60 using UIPEthernet Library

The terminal output of ESP32 running a [ENC28J60_WM_Config example](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/ENC28J60_WM_Config) of [BlynkEthernet_WM Library](https://github.com/khoih-prog/BlynkEthernet_WM)

```cpp
Start ENC28J60_WM_Config on ESP32
[38] EEPROMsz:1024
[38] CCSum=0x29f2,RCSum=0x29f2
[38] CrCCsum=0,CrRCsum=0
[38] Hdr=ENC28J60,BName=ESP32-ENC28J60-WM
[38] Svr=account.duckdns.org,Tok=token
[45] Svr1=account.ddns.net,Tok1=token1
[51] Prt=8080,SIP=blank
[53] MAC:FE-80-D6-B4-FC-EE
ENC28J60_CONTROL_CS =13
SS =5
SPI_MOSI =23
SPI_MISO =19
SPI_SCK =18
[5332] IP:192.168.2.103
[5332] bg:ECon.TryB
[5332] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[5343] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6454] Ready (ping: 37ms).
[6522] Connected to Blynk Server = account.duckdns.org, Token = token
[6522] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token, IP = 192.168.2.103
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```

---

#### 3. WebClientMulti_SSL on SAM DUE with W5x00 using Ethernet_Generic Library

The terminal output of **SAM DUE with W5x00 using Ethernet_Generic Library** running [WebClientMulti_SSL example](examples/WebClientMulti_SSL)

```
Start WebClientMulti_SSL on SAM DUE with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 75
[ETHERNET_WEBSERVER] MISO: 74
[ETHERNET_WEBSERVER] SCK: 76
[ETHERNET_WEBSERVER] SS: 10
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : SAM DUE , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:75
MISO:74
SCK:76
SS:10
=========================
Using mac index = 5
Connected! IP address: 192.168.2.81
Connecting to www.arduino.cc...
Took: 2399
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 09:37:58 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=d3528e024daf847cc558d2ba3205ee3d01605001078; expires=Thu, 10-Dec-20 09:37:58 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Access-Control-Allow-Origin: https://www.arduino.cc
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Accept,Authorization,Cache-Control,Content-Type,DNT,If-Modified-Since,Keep-Alive,Origin,User-Agent,X-Mx-ReqToken,X-Requested-With
Strict-Transport-Security: max-age=500; includeSubDomains
X-Frame-Options: SAMEORIGIN
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 06531dfd840000b65f100a1000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 5efecc42682cb65f-YWG

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3324 bytes in 0.3154 s, rate = 10.54 kbytes/second
Connecting to www.cloudflare.com...
Took: 207
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 09:38:03 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=dfa9b1dae33cb96315678c7c8c518f4c31605001083; expires=Thu, 10-Dec-20 09:38:03 GMT; path=/; domain=.www.cloudflare.com; HttpOnly; SameSite=Lax; Secure
Access-Control-Allow-Origin: *
Server: cloudflare
CF-RAY: 5efecc66fb77b65f-YWG
X-Frame-Options: SAMEORIGIN
Expires: Thu, 01 Jan 1970 00:00:01 GMT
Cache-Control: no-cache

bb
fl=168f4
h=www.cloudflare.com
ip=76.10.180.220
ts=1605001083.997
visit_scheme=https
uag=SSLClientOverEthernet
colo=YWG
http=http/1.1
loc=CA
tls=TLSv1.2
sni=plaintext
warp=off
gateway=off

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.

```

---

#### 4. WebClient_SSL on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library

The terminal output of **SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library** running [WebClient_SSL example](examples/WebClient_SSL)

```
Start WebClient_SSL on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 10
[ETHERNET_WEBSERVER] MISO: 9
[ETHERNET_WEBSERVER] SCK: 8
[ETHERNET_WEBSERVER] SS: 4
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : SEEED_XIAO_M0 , setCsPin: 1
=========================
Currently Used SPI pinout:
MOSI:10
MISO:9
SCK:8
SS:4
SPI_CS:1
=========================
Using mac index = 1
Connected! IP address: 192.168.2.102
Connecting to : www.arduino.cc, port : 443
Connected to www.arduino.cc
Took: 3551
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 07:59:21 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=dd7e2b24e26b05eb2d2e5793ac594c3611604995161; expires=Thu, 10-Dec-20 07:59:21 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Access-Control-Allow-Origin: https://www.arduino.cc
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Accept,Authorization,Cache-Control,Content-Type,DNT,If-Modified-Since,Keep-Alive,Origin,User-Agent,X-Mx-ReqToken,X-Requested-With
Strict-Transport-Security: max-age=500; includeSubDomains
X-Frame-Options: SAMEORIGIN
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 0652c3b5b60000f99d7e918000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 5efe3bcf881af99d-YYZ
alt-svc: h3-27=":443"; ma=86400, h3-28=":443"; ma=86400, h3-29=":443"; ma=86400

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3405 bytes in 0.2072 s, rate = 16.43 kbytes/second

```

---

#### 5. MQTTClient_SSL_Complex on SAM DUE with W5x00 using Ethernet_Generic Library

5. The terminal output of **SAM DUE with W5x00 using Ethernet_Generic Library** running [MQTTClient_SSL_Complex example](examples/MQTTClient_SSL_Complex)

```
Start MQTTClient_SSL_Complex on SAM DUE with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 75
[ETHERNET_WEBSERVER] MISO: 74
[ETHERNET_WEBSERVER] SCK: 76
[ETHERNET_WEBSERVER] SS: 10
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : SAM DUE , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:75
MISO:74
SCK:76
SS:10
=========================
Using mac index = 6
Connected! IP address: 192.168.2.71
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 7694
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 7694
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 15580
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 15580
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 20587
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Complex on SAM DUE, millis = 20587

```

---

#### 6. MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library

The terminal output of **SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library** running [MQTTS_ThingStream example](examples/MQTTS_ThingStream)

```
Start MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] Board : SEEED_XIAO_M0 , setCsPin: 1
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 10
[ETHERNET_WEBSERVER] MISO: 9
[ETHERNET_WEBSERVER] SCK: 8
[ETHERNET_WEBSERVER] SS: 4
[ETHERNET_WEBSERVER] =========================
You're connected to the network, IP = 192.168.2.102
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on SEEED_XIAO_M0 with W5x00 using Ethernet_Generic Library
```

---

#### 7. MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The terminal output of **MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library** running [MQTTS_ThingStream example](examples/MQTTS_ThingStream)

```
Start MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 3
[ETHERNET_WEBSERVER] MISO: 4
[ETHERNET_WEBSERVER] SCK: 2
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : MBED RASPBERRY_PI_PICO , setCsPin: 5
You're connected to the network, IP = 192.168.2.92
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
```

---

#### 8. MQTTClient_SSL on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The terminal output of **MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library** running [MQTTClient_SSL example](examples/MQTTClient_SSL)

```
Start MQTTClient_SSL on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 3
[ETHERNET_WEBSERVER] MISO: 4
[ETHERNET_WEBSERVER] SCK: 2
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : MBED RASPBERRY_PI_PICO , setCsPin: 5
=========================
Currently Used SPI pinout:
MOSI:3
MISO:4
SCK:2
SS:5
=========================
Using mac index = 17
Connected! IP address: 192.168.2.101
Attempting MQTTS connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on MBED RASPBERRY_PI_PICO
```

---


#### 9. AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/pics/AdvancedWebServer_Mbed_RPi_Pico.png">
</p>


```
Starting AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 3
[EWS] MISO: 4
[EWS] SCK: 2
[EWS] SS: 5
[EWS] =========================
[EWS] RPIPICO setCsPin: 5
=========================
Currently Used SPI pinout:
MOSI:3
MISO:4
SCK:2
SS:5
SPI_CS:5
=========================
Using mac index = 12
Connected! IP address: 192.168.2.95
HTTP EthernetWebServer is @ IP : 192.168.2.95
.[EWS] String Len = 0, extend to 2048
......... .......... .......... .......... .......... .......... .......... ..........
```

---

#### 10. MQTTClient_SSL on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The terminal output of **RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library** running [MQTTClient_SSL example](examples/MQTTClient_SSL)

```
Start MQTTClient_SSL on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 19
[ETHERNET_WEBSERVER] MISO: 16
[ETHERNET_WEBSERVER] SCK: 18
[ETHERNET_WEBSERVER] SS: 17
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 1
Connected! IP address: 192.168.2.105
Attempting MQTTS connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on RASPBERRY_PI_PICO
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on RASPBERRY_PI_PICO
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on RASPBERRY_PI_PICO
```

---


#### 11. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/pics/AdvancedWebServer_RPi_Pico.png">
</p>


```
Starting AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET_GENERIC ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 19
[ETHERNET_WEBSERVER] MISO: 16
[ETHERNET_WEBSERVER] SCK: 18
[ETHERNET_WEBSERVER] SS: 17
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 8
Connected! IP address: 192.168.2.99
HTTP EthernetWebServer is @ IP : 192.168.2.99
.[EWS] String Len = 0, extend to 2048
......... .......... .......... .......... .......... .......... .......... ..........

```

---


#### 12. AdvancedWebServer_QNEthernet on Teensy 4.1 using QNEthernet Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer_QNEthernet](examples/QNEthernet/AdvancedWebServer_QNEthernet) on **Teensy 4.1** using QNEthernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/pics/AdvancedWebServer_QNEthernet.png">
</p>

```
Starting AdvancedWebServer_QNEthernet on TEENSY 4.1 using QNEthernet
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
HTTP EthernetWebServer is @ IP : 192.168.2.222
.[EWS] String Len = 0, extend to 2048
......... .......... .......... .......... .......... .......... .......... ..........
```

---

#### 13. MQTTClient_SSL on TEENSY 4.1 using QNEthernet Library

The following are debug terminal output and screen shot when running example [MQTTClient_SSL](examples/QNEthernet/MQTTClient_SSL) on **Teensy 4.1** using QNEthernet Library


```
Starting MQTTClient_SSL on TEENSY 4.1 using QNEthernet
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
Attempting MQTTS connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on TEENSY 4.1
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on TEENSY 4.1
```

---


#### 14. WebClientMulti_SSL on TEENSY 4.1 using QNEthernet Library

The following are debug terminal output and screen shot when running example [WebClientMulti_SSL](examples/QNEthernet/WebClientMulti_SSL) on **Teensy 4.1** using QNEthernet Library


```
Starting WebClientMulti_SSL on TEENSY 4.1 using QNEthernet
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
Connecting to www.arduino.cc...
Took: 162
HTTP/1.1 200 OK
Date: Sat, 04 Sep 2021 14:45:12 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Strict-Transport-Security: max-age=500; includeSubDomains
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 6898000faee0f999-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400, h3-28=":443"; ma=86400, h3-27=":443"; ma=86400

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
LoopCount 1, Received 2876 bytes in 0.0002 s, rate = 12186.44 kbytes/second
```

---

#### 15. AdvancedWebServer on PORTENTA_H7_M7 using Portenta_Ethernet Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on **PORTENTA_H7_M7** using Portenta_Ethernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/pics/AdvancedWebServer_PortentaH7.png">
</p>

```

Starting AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
EthernetWebServer_SSL v1.8.0
[ETHERNET_WEBSERVER] ======== USE_PORTENTA_H7_ETHERNET ========
Using mac index = 2
Connected! IP address: 192.168.2.101
HTTP EthernetWebServer is @ IP : 192.168.2.101
.[EWS] String Len = 0, extend to 2048
......... .......... .......... .......... .......... .......... .......... ..........
```


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---

### Issues ###

Submit issues to: [EthernetWebServer_SSL issues](https://github.com/khoih-prog/EthernetWebServer_SSL/issues)

---

### TO DO

1. Bug Searching and Killing
2. Add TLS/SSL Server support
3. Support more types of boards using Ethernet shields.
4. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia
5. Add mDNS features.


### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.** non-SSL EthernetServer.
 5. Add support to SAM DUE.
 6. Add support to Ethernet W5x00, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/adafruit/Ethernet2), [`Ethernet3`](https://github.com/sstaub/Ethernet3) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 7. Add support to Ethernet ENC28J60, using [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
 8. Add support to ESP32 and ESP8266 non-SSL EthernetServer.
 9. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless
10. Add support to [`EthernetENC`](https://github.com/jandrassy/EthernetENC)
11. Add support to PROGMEM-related commands, such as sendContent_P() and send_P()
12. Add TLS/SSL Client support to SAMD21/SAMD51, SAM DUE, Teensy, ESP32, etc.
13. Add **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**
14. Add support to [NativeEthernet Library](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet
15. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
16. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
17. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
18. Add support to **Portenta_H7 boards**, using [**Arduino-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed).
19. Reduce usage of Arduino String with std::string
20. Optimize library code and examples by using **reference-passing instead of value-passing**.
21. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
22. Fix bug when using `QNEthernet` staticIP. 
23. Add staticIP option to `NativeEthernet` examples
24. Change licence from `MIT` to `GPLv3`
25. Sync with [SSLClient v1.6.11](https://github.com/OPEnSLab-OSU/SSLClient/releases/tag/v1.6.11)
26. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
27. Support **SPI2 for ESP32**
28. Rewrite library and add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project to fix `multiple-definitions` linker error


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from the good [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) and [ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) libraries.
2. [OPEnSLab-OSU](https://github.com/OPEnSLab-OSU) for [OPEnSLab-OSU's SSLClient](https://github.com/OPEnSLab-OSU/SSLClient)
3. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **U-Blox B302 running as nRF52840 and U-Blox B112 running as nRF52832**, has never been started and finished. Also see [ESP32-based U-BLOX NINA W102 running ENC28J60](https://u-blox-ethernet-ninaw.blogspot.com/).
4. [Adrian McEwen](https://github.com/amcewen) for [HttpClient Library](https://github.com/amcewen/HttpClient) on which the [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient) and this [EthernetWebServer library](https://github.com/khoih-prog/EthernetWebServer) are relied.
5. Thanks to [jimmie11](https://github.com/jimmie11) to report and suggest a fix in [Compile Error on Teensy 4.1 #14](https://github.com/khoih-prog/EthernetWebServer/issues/14) leading to the new version v1.3.0 to provide support to **Teensy 4.1** using [**NativeEthernet Library**](https://github.com/vjmuzik/NativeEthernet)
6. Thanks to [Shahram](https://github.com/Nourbakhsh-Rad) to report issue [multiple definition of base64 error with ver. 1.8.3 #44](https://github.com/khoih-prog/EthernetWebServer/issues/44) which was fixed in v1.7.3
7. Thanks to [Marcel Stör](https://github.com/marcelstoer) to report issue [Pull in OPEnSLab-OSU's SSLClient v1.6.11 #17](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/17) which was fixed in v1.7.8

<table>
  <tr>
    <td align="center"><a href="https://github.com/igrr"><img src="https://github.com/igrr.png" width="100px;" alt="igrr"/><br /><sub><b>⭐️ Ivan Grokhotkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/OPEnSLab-OSU"><img src="https://github.com/OPEnSLab-OSU.png" width="100px;" alt="OPEnSLab-OSU"/><br /><sub><b>⭐️ OPEnSLab-OSU</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/amcewen"><img src="https://github.com/amcewen.png" width="100px;" alt="amcewen"/><br /><sub><b>⭐️ Adrian McEwen</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/jimmie11"><img src="https://github.com/jimmie11.png" width="100px;" alt="jimmie11"/><br /><sub><b>jimmie11</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Nourbakhsh-Rad"><img src="https://github.com/Nourbakhsh-Rad.png" width="100px;" alt="Nourbakhsh-Rad"/><br /><sub><b>Shahram</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/marcelstoer"><img src="https://github.com/marcelstoer.png" width="100px;" alt="marcelstoer"/><br /><sub><b>Marcel Stör</b></sub></a><br /></td>
  </tr>
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang
