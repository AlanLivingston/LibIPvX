#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

#include "stdafx.h"
#include "ipvxstatic.h"

class IP6Address{
	public:
		IP6Address(std::string) {
			this->bitset = ConvertIPv6StringToSTLBitset(_address);
			this->netmask = this->GetDefaultNetMask();
		}

		~IP6Address(){}


		std::string				GetAddressString();
		std::bitset<IPV6_ADDRESS_LENGTH>	GetAddressBitset();
		std::string				GetStringFromBitset();
		int					GetFirstBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetFirstBlockBitset();
		int					GetSecondBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetSecondBlockBitset();
		int					GetThirdBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetThirdBlockBitset();
		int					GetFourthBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetFourthBlockBitset();
		int					GetFifthBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetFifthBlockBitset();
		int					GetSixthBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetSixthBlockBitset();
		int					GetSeventhBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetSeventhBlockDecimal();
		int					GetEigthBlockDecimal();
		std::bitset<IPV6_BLOCK_SIZE>		GetEigthBlockBitset();
		int					GetBlockDecimalByIndex(int);	
		std::bitset<IPV6_BLOCK_SIZE>		GetBlockBitsetByIndex(int);
	private:
		std::bitset<IPV6_ADDRESS_LENGTH>	bitset;
		std::string				netmask;
};




#endif
