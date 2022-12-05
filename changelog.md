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


* [Changelog](#changelog)
  * [Releases v1.9.3](#releases-v193)
  * [Releases v1.9.2](#releases-v192)
  * [Releases v1.9.1](#releases-v191)
  * [Releases v1.9.0](#releases-v190)
  * [Releases v1.8.2](#releases-v182)
  * [Releases v1.8.1](#releases-v181)
  * [Releases v1.8.0](#releases-v180)
  * [Releases v1.7.8](#releases-v178)
  * [Releases v1.7.7](#releases-v177)
  * [Releases v1.7.6](#releases-v176)
  * [Releases v1.7.5](#releases-v175)
  * [Releases v1.7.4](#releases-v174)
  * [Releases v1.7.3](#releases-v173)
  * [Releases v1.7.2](#releases-v172)
  * [Releases v1.7.1](#releases-v171)
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

### Releases v1.9.3

1. Add support to Seeeduino nRF52840-based boards such as **Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core
2. Add astyle using `allman` style. Restyle the library
3. Display warning only when `_ETHERNET_WEBSERVER_LOGLEVEL_` > 3
4. Update examples
5. Update `Packages' Patches` to add Seeeduino `nRF52` core

### Releases v1.9.2

1. Slow SPI clock for old `W5100` shield or `SAMD Zero`
2. Use correct Debug Terminal `Serial` for so-called **SAMD21 Zero** boards from Arduino as well as Adafruit
3. Update `Packages' Patches`

### Releases v1.9.1

1. Auto-select SPI(s) `SS/CS` pins according to board package if available
2. Update `Packages' Patches`

### Releases v1.9.0

1. Add support to SPI1, SPI2 for Teensy using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
2. Add support to custom SPI for Mbed RP2040, Portenta-H7, etc. using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
3. Add examples [AdvancedWebServer_Teensy4x_SPI1](examples/AdvancedWebServer_Teensy4x_SPI1) to demo new feature
4. Add examples [AdvancedWebServer_RP2040_SPI1](examples/AdvancedWebServer_RP2040_SPI1) to demo new feature

### Releases v1.8.2

1. Change from `arduino.cc` to `arduino.tips` in examples
2. Add `lib_ldf_mode = chain+` in `platformio.ini`

### Releases v1.8.1

1. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
2. Rewrite all the examples to support new features
3. Update `Packages' Patches`

### Releases v1.8.0

1. Use new [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
2. Rewrite to avoid `multiple-definitions` linker error for multiple-file project
3. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
4. Update `Packages' Patches`

### Releases v1.7.8

1. Sync with [SSLClient v1.6.11](https://github.com/OPEnSLab-OSU/SSLClient/releases/tag/v1.6.11). Check [Pull in OPEnSLab-OSU's SSLClient v1.6.11 #17](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/17)
2. Add example [AWS_IoT](examples/AWS_IoT)
3. Change default SS pin for RP2040 using [ArduinoCore-mbed core](https://github.com/arduino/ArduinoCore-mbed) to 17 from 5 to be the same as [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
4. Update `Packages' Patches`

### Releases v1.7.7

1. Change license from `MIT` to `GPLv3`. Check [Licensing of SSLClient #16](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/16)


### Releases v1.7.6

1. Fix bug when using `QNEthernet` staticIP. Check [QNEthernet and NativeEthernet staticIP not working with WS Server #39](https://github.com/khoih-prog/WebSockets2_Generic/issues/39)
2. Simplify and add staticIP option to `NativeEthernet` examples.
3. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
4. Add `Packages' Patches` for [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
5. Update `Packages' Patches`

### Releases v1.7.5

1. Fix decoding error bug when using special `&` in data fields. Check [Decoding Error. two times called urlDecode in Parsing-impl.h. #17](https://github.com/khoih-prog/WiFiWebServer/issues/17)
2. Update `Packages' Patches`

### Releases v1.7.4

1. Fix libb64 `fallthrough` compile warning

### Releases v1.7.3

1. Fix libb64 compile error for ESP8266. Check [multiple definition of base64 error with ver. 1.8.3 #44](https://github.com/khoih-prog/EthernetWebServer/issues/44)
2. Update `Packages' Patches`

### Releases v1.7.2

1. Fix wrong http status header bug. Check [fix for wrong http status header #42](https://github.com/khoih-prog/EthernetWebServer/pull/42)
2. Fix authenticate issue caused by libb64

### Releases v1.7.1

1. Fix bug related to String in library and examples

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


