## EthernetWebServer_SSL

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer_SSL.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer_SSL.svg)](http://github.com/khoih-prog/EthernetWebServer_SSL/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Major Releases v1.7.0](#major-releases-v170)
  * [Releases v1.6.1](#releases-v161)
  * [Major Releases v1.6.0](#major-releases-v160)
  * [Major Releases v1.5.0](#major-releases-v150)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Releases v1.3.0](#releases-v130)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)

---
---

## Changelog

### Major Releases v1.7.0

1. Add support to **Portenta_H7** using [**Arduino mbed_portenta core**](https://github.com/arduino/ArduinoCore-mbed)
2. Reduce usage of Arduino String with std::string
3. Optimize library code and examples by using **reference-passing instead of value-passing**.
4. Update `Packages' Patches`
5. Add more ESP32/ESP8266 supporting code

### Releases v1.6.1

1. Add support to [QNEthernet Library](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet
2. Update examples with new features

### Major Releases v1.6.0

1. Add support to [QNEthernet Library](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet
2. Update examples with new features

### Major Releases v1.5.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core** v1.3.1+](https://github.com/earlephilhower/arduino-pico).
2. Update examples with new features

### Major Releases v1.4.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
2. Update examples with new features

### Releases v1.3.1

1. Clean-up all compiler warnings possible.
2. Add Table of Contents

### Releases v1.3.0

1. Add support to [NativeEthernet Library](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1

### Major Releases v1.2.0

1. Add high-level **HTTP and WebSockets Client** by merging [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)
2. Add many more examples for HTTP and WebSockets Client.
3. Add Version String.

### Releases v1.1.2

1. Add SSL debug feature.
2. Enhance examples.

### Releases v1.1.1

1. Permit sites with "Chain could not be linked to a trust anchor" such as mqtt.thingstream.io.
2. Add example MQTTS_ThingStream to demonstrate new feature


### Releases v1.1.0

1. Initial coding for SAMD21/SAMD51, SAM DUE, Teensy to support Ethernet shields using SSL.
2. Supporting W5x00 using Ethernet, EthernetLarge, Ethernet2 and Ethernet3 libraries
3. Supporting ENC28J60 using EthernetENC and UIPEthernet libraries


