#include "ipvxstatic.h"


/****f* LibIPvX/GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* NAME
	*	GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* DESCRIPTION
	*	Performs a bitwise NOT (flips) on the bitset parameter and returns the result.
	* PARAMETERS 
	*	_bitset - the bitset to flip.
	* RETURN VALUE
	*	std::bitset<IPV4_ADDRESS_LENGTH> 
	* USAGE	
        * #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
        *   	return 0;
        * }
	* SOURCE
	*/
std::bitset<IPV4_ADDRESS_LENGTH> GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) 
{
	std::bitset<IPV4_ADDRESS_LENGTH> tempBitset = _bitset;
	return tempBitset.flip();
}
/*******/

std::bitset<IPV4_ADDRESS_LENGTH> ConvertIPv4StringToSTLBitset(const std::string _address)  {
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
	_binString = ConvertDecimalIntegerToEightBitBinaryString(octet1);
	_binString += ConvertDecimalIntegerToEightBitBinaryString(octet2);
	_binString += ConvertDecimalIntegerToEightBitBinaryString(octet3);
	_binString += ConvertDecimalIntegerToEightBitBinaryString(octet4);

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

std::bitset<IPV4_OCTET_LENGTH> ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal){
	std::bitset<IPV4_OCTET_LENGTH> octetBitset;
	
	std::string octetString = ConvertDecimalIntegerToEightBitBinaryString(_OctetDecimal);

	// loop to access each bit in indexed octet.
	for ( size_t b = 0; b < IPV4_OCTET_LENGTH; b++ ) {
		// Set bit to bool value at same index within the _address string
		bool bit = ( octetString.at(b) == 1) ? true : false;
		octetBitset.set(b, bit);
	}

	return octetBitset;
}

std::string ConvertDecimalIntegerToEightBitBinaryString(const int _integer) {
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

