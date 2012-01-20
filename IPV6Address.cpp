#include "IPV6Address.h"


std::string IP6Address::GetAddressString(){
	return this->GetStringFromBitset(this->bitset);
}

std::bitset<IPV6_ADDRESS_LENGTH> IP6Address::GetAddressBitset(){
	return this->bitset;
}


std::string IP6Address::GetStringFromBitset(const std::bitset<IPV6_ADDRESS_LENGTH> _bitset){
	std::string _addressString;
	for(int i = 0; i < IPV6_HECTET_COUNT; i++){
		unsigned int hectetValue = 0;
		int value = 32768;

		for(int j = 0; j < IPV6_HECTET_SIZE; j++){
			if( _bitset[ (IPV6_HECTET_SIZE * i) + j] == 1){
				hectetValue += value;
			}

			value = value >> 1;
		}

		std::stringstream ss;
		ss << hex << hectetValue;
		_addressString += ss.str();

		if(i != 8){
			_addressString += ":";
		}
	}

	return _addressString;
}




int IP6Address::GetBlockDecimalByIndex(int index){
	int decimalValue = 0;
	int value = 32768;
	for(int i = 0; i < IPV6_HECTET_SIZE; i++){
		if(this->bitset[i] == 1 && i < bitset.size()){
			decimalValue += value;
		}
		value = value >> 1;
	}
	return decimalValue;
}

std::bitset<IPV6_HECTET_SIZE> IP6Address::GetBlockBitsetByIndex(int index){
	std::bitset<IPV6_HECTET_SIZE> bitset;
	for(int i = 0; i < IPV6_HECTET_SIZE; i++){
		_bitset.set(i, this->bitset[ (index * IPV6_HECTET_SIZE) + i]);
	}
	return _bitset;
} 
