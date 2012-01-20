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
		int					GetFirstHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetFirstHextetBitset();
		int					GetSecondHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetSecondHextetBitset();
		int					GetThirdHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetThirdHextetBitset();
		int					GetFourthHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetFourthHextetBitset();
		int					GetFifthHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetFifthHextetBitset();
		int					GetSixthHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetSixthHextetBitset();
		int					GetSeventhHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetSeventhHextetDecimal();
		int					GetEigthHextetDecimal();
		std::bitset<IPV6_Hextet_SIZE>		GetEigthHextetBitset();
		int					GetHextetDecimalByIndex(int);	
		std::bitset<IPV6_Hextet_SIZE>		GetHextetBitsetByIndex(int);
	private:
		std::bitset<IPV6_ADDRESS_LENGTH>	bitset;
		std::string				netmask;
};




#endif
