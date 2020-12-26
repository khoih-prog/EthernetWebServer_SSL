/* Copyright 2019 OSU OPEnS Lab

   Permission is hereby granted, free of charge, to any person obtaining a copy of this
   software and associated documentation files (the "Software"), to deal in the Software
   without restriction, including without limitation the rights to use, copy, modify,
   merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to the following
   conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
   PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
   SSLClientParameters.cpp

   This file contains a simple utility class to store parameters about an SSL Session
   for reuse later.
*/

#include "SSLClient/SSLClientParameters.h"

struct ssl_pem_decode_state 
{
  std::vector<char>* vect;
  size_t index = 0;
};

static void ssl_pem_decode_callback(void *dest_ctx, const void *src, size_t len) 
{
  ssl_pem_decode_state* ctx = static_cast<ssl_pem_decode_state*>(dest_ctx);
  
  for (size_t i = 0; i < len; i++) 
    ctx->vect->emplace_back(static_cast<const char*>(src)[i]);
    
  // update index
  ctx->index += len;
}

/**
   Utility function to create a vector of the DER encoded bytes from a PEM
   certificate. Useful if we would like to decode certificates that have
   been transmitted over the internet.
   @param data PEM certificate bytes, including the "BEGIN" and "END" statements.
   @param len Number of characters to process, MUST include a whole certificate.
   @return A vector of bytes representing the certificate in DER format.
*/
static std::vector<char> make_vector_pem(const char* data, const size_t len) 
{
  if (data == nullptr || len < 80) 
    return {};
    
  // initialize the bearssl PEM context
  br_pem_decoder_context pctx;
  br_pem_decoder_init(&pctx);
  
  // create a temporary vector
  std::vector<char> temp;
  // initialize the DER storage context
  ssl_pem_decode_state state;
  state.vect = &temp;
  state.index = 0;
  
  // set the byte reciever
  br_pem_decoder_setdest(&pctx, &ssl_pem_decode_callback, &state);
  
  // start decoding!
  int br_state = 0;
  size_t index = 0;
  
  do 
  {
    index += br_pem_decoder_push(&pctx, static_cast<const void*>(&data[index]), len - index);
    br_state = br_pem_decoder_event(&pctx);
    
    // if we found the begining object, reserve the vector based on the remaining relavent bytes
    if (br_state == BR_PEM_BEGIN_OBJ) 
    {
      // 22 = five dashes for header and footer + four newlines - character difference between `BEGIN` and `END`
      const size_t relavant_bytes_base64 = len - (2 * strlen(br_pem_decoder_name(&pctx)) + 22);
      temp.reserve(relavant_bytes_base64 * 3 / 4);
    }
  } while (br_state != BR_PEM_ERROR && br_state != BR_PEM_END_OBJ && len != index);
  
  // error check
  if (br_state == BR_PEM_ERROR) 
  {
    // set data to error
    temp.clear();
  }
  
  // else we're good!
  return temp;
}

/**
   Use the br_skey api family to decode a private key into the important numbers.
   This function supports both RSA and EC private keys, and returns a context
   which can be used by BearSSL later to authenticate with mTLS.
   @param der DER encoded certificate, as a vector of bytes.
   @returns context used by BearSSL to store information about the keys. You can
   use the br_skey_* family of APIs to access information from this context.
*/
static br_skey_decoder_context make_key_from_der(const std::vector<char>& der) 
{
  br_skey_decoder_context out;
  br_skey_decoder_init(&out);
  br_skey_decoder_push(&out, der.data(), der.size());
  
  return out;
}

/* See SSLClientParams.h */
SSLClientParameters::SSLClientParameters(const char* cert, const size_t cert_len, const char* key, const size_t key_len, bool is_der)
  : m_cert(is_der ? std::vector<char>(cert, cert + cert_len) : make_vector_pem(cert, cert_len))
  , m_cert_struct{ const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(m_cert.data())), m_cert.size() }
  , m_key_struct( make_key_from_der( is_der ? std::vector<char>(key, key + key_len) : make_vector_pem(key, key_len) ) ) 
{}

/* See SSLClientParams.h */
SSLClientParameters SSLClientParameters::fromPEM(const char* cert_pem, const size_t cert_len, const char* key_pem, const size_t key_len) 
{
  return SSLClientParameters(cert_pem, cert_len, key_pem, key_len, false);
}

/* See SSLClientParams.h */
SSLClientParameters SSLClientParameters::fromDER(const char* cert_der, const size_t cert_len, const char* key_der, const size_t key_len) 
{
  return SSLClientParameters(cert_der, cert_len, key_der, key_len, true);
}
