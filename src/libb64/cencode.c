/****************************************************************************************************************************
  cencoder.c - c source to a base64 decoding algorithm implementation

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
  Licensed under MIT license
       
  Version: 1.7.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.3.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
  1.3.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
  1.4.0   K Hoang      13/05/2021 Add support to RP2040-based boards using Arduino mbed_rp2040 core
  1.5.0   K Hoang      15/05/2021 Add support to RP2040-based boards using Arduino-pico rp2040 core
  1.6.0   K Hoang      04/09/2021 Add support to QNEthernet Library for Teensy 4.1
  1.6.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
  1.7.0   K Hoang      19/12/2021 Reduce usage of Arduino String with std::string. Add support to Portenta H7 Ethernet
  1.7.1   K Hoang      25/12/2021 Fix bug relating to String
  1.7.2   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.7.3   K Hoang      11/01/2022 Fix libb64 compile error for ESP8266
 *****************************************************************************************************************************/
 
#if !(ESP32 || ESP8266)
 
#include "cencode.h"

const int CHARS_PER_LINE = 72;

void base64_init_encodestate(base64_encodestate* state_in)
{
  state_in->step = step_A;
  state_in->result = 0;
  state_in->stepcount = 0;
}

char base64_encode_value(char value_in)
{
  static const char* encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  if (value_in > 63)
    return '=';

  return encoding[(int)value_in];
}

int base64_encode_block(const char* plaintext_in, int length_in, char* code_out, base64_encodestate* state_in)
{
  const char* plainchar = plaintext_in;
  const char* const plaintextend = plaintext_in + length_in;
  char* codechar = code_out;
  char result;
  char fragment;

  result = state_in->result;

  switch (state_in->step)
  {
      while (1)
      {
      case step_A:
        if (plainchar == plaintextend)
        {
          state_in->result = result;
          state_in->step = step_A;
          return codechar - code_out;
        }

        fragment = *plainchar++;
        result = (fragment & 0x0fc) >> 2;
        *codechar++ = base64_encode_value(result);
        result = (fragment & 0x003) << 4;

      case step_B:
        if (plainchar == plaintextend)
        {
          state_in->result = result;
          state_in->step = step_B;
          return codechar - code_out;
        }

        fragment = *plainchar++;
        result |= (fragment & 0x0f0) >> 4;
        *codechar++ = base64_encode_value(result);
        result = (fragment & 0x00f) << 2;

      case step_C:
        if (plainchar == plaintextend)
        {
          state_in->result = result;
          state_in->step = step_C;
          return codechar - code_out;
        }

        fragment = *plainchar++;
        result |= (fragment & 0x0c0) >> 6;
        *codechar++ = base64_encode_value(result);
        result  = (fragment & 0x03f) >> 0;
        *codechar++ = base64_encode_value(result);

        ++(state_in->stepcount);

        if (state_in->stepcount == CHARS_PER_LINE / 4)
        {
          *codechar++ = '\n';
          state_in->stepcount = 0;
        }
      }
  }

  /* control should not reach here */
  return codechar - code_out;
}

int base64_encode_blockend(char* code_out, base64_encodestate* state_in)
{
  char* codechar = code_out;

  switch (state_in->step)
  {
    case step_B:
      *codechar++ = base64_encode_value(state_in->result);
      *codechar++ = '=';
      *codechar++ = '=';
      break;
    case step_C:
      *codechar++ = base64_encode_value(state_in->result);
      *codechar++ = '=';
      break;
    case step_A:
      break;
  }

  *codechar = 0x00;

  return codechar - code_out;
}

int base64_encode_chars(const char* plaintext_in, int length_in, char* code_out)
{
  base64_encodestate _state;
  base64_init_encodestate(&_state);
  int len = base64_encode_block(plaintext_in, length_in, code_out, &_state);

  return len + base64_encode_blockend((code_out + len), &_state);
}

#endif
