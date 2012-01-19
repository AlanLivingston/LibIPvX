#include "IPV6Address.h"


std::string IPV6Address::GetAddressString(){
	return this->GetStringFromBitset(this->bitset);
}

std::bitset<IPV6_ADDRESS_LENGTH> IPV6Address::GetAddressBitset(){
	return this->bitset;
}


std::string IPV6Address::GetStringFromBitset(const std::bitset<IPV6_ADDRESS_LENGTH> _bitset){
	std::string _addressString;
	for(int i = 0; i < IPV6_BLOCK_COUNT; i++){
		unsigned int blockValue = 0;
		int value = 32768;

		for(int j = 0; j < IPV6_BLOCK_SIZE; j++){
			if( _bitset[ (IPV6_BLOCK_SIZE * i) + j] == 1){
				blockValue += value;
			}

			value = value >> 1;
		}

		std::stringstream ss;
		ss << hex << blockValue;
		_addressString += ss.str();

		if(i != 8){
			_addressString += ":";
		}
	}


	return _addressString;
}



 
