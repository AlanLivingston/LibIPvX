#include "IPV6Address.h"


std::string IP6Address::GetAddressString(){
	return this->GetStringFromBitset(this->bitset);
}

std::bitset<IPV6_ADDRESS_LENGTH> IP6Address::GetAddressBitset(){
	return this->bitset;
}


std::string IP6Address::GetStringFromBitset(const std::bitset<IPV6_ADDRESS_LENGTH> _bitset){
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


int IP6Address::GetFirstBlockDecimal(){
	return this->GetBlockDecimalByIndex(0);
}

int IP6Address::GetSecondBlockDecimal(){
	return this->GetBlockDecimalByIndex(1);
}

int IP6Address::GetThirdBlockDecimal(){
	return this->GetBlockDecimalByIndex(2);
}

int IP6Address::GetFourthBlockDecimal(){
	return this->GetBlockDecimalByIndex(3);
}

int IP6Address::GetFifthBlockDecimal(){
	return this->GetBlockDecimalByIndex(4);
}

int IP6Address::GetSixthBlockDecimal(){
	return this->GetBlockDecimalByIndex(5);
}

int IP6Address::GetSeventhBlockDecimal(){
	return this->GetBlockDecimalByIndex(6);
}

int GetEigthBlockDecimal(){
	return this->GetBlockDecimalByIndex(7);
}



std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetFirstBlockBitset(){
	return this->GetBlockBitsetByIndex(0);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetSecondBlockBitset(){
	return this->GetBlockBitsetByIndex(1);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetThirdBlockBitset(){
	return this->GetBlockBitsetByIndex(2);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetFourthBlockBitset(){
	return this->GetBlockBitsetByIndex(3);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetFifthBlockBitset(){
	return this->GetBlockBitsetByIndex(4);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetSixthBlockBitset(){
	return this->GetBlockBitsetByIndex(5);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetSeventhBlockBitset(){
	return this->GetBlockBitsetByIndex(6);
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetEigthBlockBitset(){
	return this->GetBlockBitsetByIndex(7);
}




int IP6Address::GetBlockDecimalByIndex(int index){
	int decimalValue = 0;
	int value = 32768;
	for(int i = 0; i < IPV6_BLOCK_SIZE; i++){
		if(this->bitset[i] == 1 && i < bitset.size()){
			decimalValue += value;
		}
		value = value >> 1;
	}
	return decimalValue;
}

std::bitset<IPV6_BLOCK_SIZE> IP6Address::GetBlockBitsetByIndex(int index){
	std::bitset<IPV6_BLOCK_SIZE> bitset;
	for(int i = 0; i < IPV6_BLOCK_SIZE; i++){
		_bitset.set(i, this->bitset[ (index * IPV6_BLOCK_SIZE) + i]);
	}
	return _bitset;
} 
