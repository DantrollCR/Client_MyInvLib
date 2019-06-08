//
// Created by dantroll on 08/06/19.
//

#ifndef CLIENT_MYINVLIB_BASE64_H
#define CLIENT_MYINVLIB_BASE64_H



#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


#endif //CLIENT_MYINVLIB_BASE64_H
