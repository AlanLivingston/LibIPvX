
#pragma once

#include "ipvxlib.h"

class IPvXStatic {
public:
	static std::bitset<IPV4_ADDRESS_LENGTH>		IPvXStatic::ConvertIPv4StringToSTLBitset(const std::string _address);		
	static std::bitset<IPV4_OCTET_LENGTH>		IPvXStatic::ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal);
	std::string									ConvertDecimalIntegerToEightBitBinaryString(const int _integer);
};	

std::bitset<IPV4_ADDRESS_LENGTH>		IPvXStatic::ConvertIPv4StringToSTLBitset(const std::string _address)  {
	// Index of each peroid in address string.
	// expected format, dec.dec.dec.dec;
	size_t _dot1 = _address.find(".");
	size_t _dot2 = _address.find(".", ( _dot1 + 1 ) );
	size_t _dot3 = _address.find(".", ( _dot2 + 1 ) );
			
	int octet1 = atoi(_address.substr(0, _dot1).c_str());
	int octet2 = atoi(_address.substr((_dot1 + 1), _dot2).c_str());
	int octet3 = atoi(_address.substr((_dot2 + 1), _dot3).c_str());
	int octet4 = atoi(_address.substr((_dot3 + 1), _address.length()).c_str());

	// convert each octet's decimal value to binary and save in string.	
	std::string _binString = "";
	_binString = IPvXStatic::ConvertDecimalIntegerToEightBitBinaryString(octet1);
	_binString += IPvXStatic::ConvertDecimalIntegerToEightBitBinaryString(octet2);
	_binString += IPvXStatic::ConvertDecimalIntegerToEightBitBinaryString(octet3);
	_binString += IPvXStatic::ConvertDecimalIntegerToEightBitBinaryString(octet4);

	std::bitset<IPV4_ADDRESS_LENGTH> addrBits;

	// loop to access each octet in the ipv4 address string.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ )
	{
		// loop to access each bit in indexed octet.
		for ( size_t b = 0; b < IPV4_OCTET_LENGTH; b++ ) {
			
			// Set bit to bool value at same index within the _address string
			bool bit = (_binString.at( (i * 8) + b ) == 1) ? true : false;
			addrBits.set((i * 8) + b, bit);
		}
	}

	return addrBits;
}

std::bitset<IPV4_OCTET_LENGTH>			IPvXStatic::ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal){
	std::bitset<IPV4_OCTET_LENGTH> octetBitset;
	
	std::string octetString = this->ConvertDecimalIntegerToEightBitBinaryString(_OctetDecimal);

	// loop to access each bit in indexed octet.
	for ( size_t b = 0; b < IPV4_OCTET_LENGTH; b++ ) {
		// Set bit to bool value at same index within the _address string
		bool bit = ( octetString.at(b) == 1) ? true : false;
		octetBitset.set(b, bit);
	}

	return octetBitset;
}

std::string IPvXStatic::ConvertDecimalIntegerToEightBitBinaryString(const int _integer) {
	std::string _binaryString;
	int tempInt = _integer;
	while ( tempInt > 0 ) {
		_binaryString += tempInt % 2;
		tempInt /= 2;
	}

	// Insert 0s into the start of the string until it's 8 bits in length.
	while ( _binaryString.length() < 8 ) {
		std::string zeroString;
		int zero = 10 % 2;
		zeroString += zero;
		_binaryString.append(zeroString);
	}

	// reverse the string to properly represent an binary ip address space.
	// damn std::string andlittle-endianess! just tricking ;)
	std::reverse(_binaryString.begin() , _binaryString.end());

	return _binaryString;
}