/****************************************************************************************************************************
  base64.cpp - cpp source to a base64 encoding algorithm implementation

  EthernetWebServer_SSL is a library for the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL
       
  Version: 1.7.8

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for SAMD21/SAMD51, nRF52, SAM DUE to support Ethernet shields using SSL.
                                  Supporting W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
  ...
  1.7.0   K Hoang      19/12/2021 Reduce usage of Arduino String with std::string. Add support to Portenta H7 Ethernet
  1.7.1   K Hoang      25/12/2021 Fix bug relating to String
  1.7.2   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.7.3   K Hoang      11/01/2022 Fix libb64 compile error for ESP8266
  1.7.4   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
  1.7.5   K Hoang      02/03/2022 Fix decoding error bug
  1.7.6   K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  1.7.7   K Hoang      14/03/2022 Change licence from `MIT` to `GPLv3`
  1.7.8   K Hoang      29/03/2022 Sync with `SSLClient` v1.6.11
 *****************************************************************************************************************************/

#include "base64.h"

/* Simple test program
#include <stdio.h>
void main()
{
    char* in = "amcewen";
    char out[22];

    b64_encode(in, 15, out, 22);
    out[21] = '\0';

    printf(out);
}
*/

int base64_encode(const unsigned char* aInput, int aInputLen, unsigned char* aOutput, int aOutputLen)
{
    // Work out if we've got enough space to encode the input
    // Every 6 bits of input becomes a byte of output
    if (aOutputLen < (aInputLen*8)/6)
    {
        // FIXME Should we return an error here, or just the length
        return (aInputLen*8)/6;
    }

    // If we get here we've got enough space to do the encoding

    const char* b64_dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (aInputLen == 3)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4|(aInput[1]>>4)];
        aOutput[2] = b64_dictionary[(aInput[1]&0x0F)<<2|(aInput[2]>>6)];
        aOutput[3] = b64_dictionary[aInput[2]&0x3F];
    }
    else if (aInputLen == 2)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4|(aInput[1]>>4)];
        aOutput[2] = b64_dictionary[(aInput[1]&0x0F)<<2];
        aOutput[3] = '=';
    }
    else if (aInputLen == 1)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4];
        aOutput[2] = '=';
        aOutput[3] = '=';
    }
    else
    {
        // Break the input into 3-byte chunks and process each of them
        int i;
        for (i = 0; i < aInputLen/3; i++)
        {
            base64_encode(&aInput[i*3], 3, &aOutput[i*4], 4);
        }
        if (aInputLen % 3 > 0)
        {
            // It doesn't fit neatly into a 3-byte chunk, so process what's left
            base64_encode(&aInput[i*3], aInputLen % 3, &aOutput[i*4], aOutputLen - (i*4));
        }
    }

    return ((aInputLen+2)/3)*4;
}

