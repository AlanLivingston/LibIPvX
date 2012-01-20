#ifndef IPVXSTATIC_H
#define IPVXSTATIC_H

#include "stdafx.h"

std::bitset<IPV4_ADDRESS_LENGTH>	ConvertIPv4StringToSTLBitset(const std::string _address);		
std::bitset<IPV4_OCTET_LENGTH>		ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal);
std::string				ConvertDecimalIntegerToEightBitBinaryString(const int _integer);

#endif
