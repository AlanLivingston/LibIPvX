#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

#include "stdafx.h"
#include "ipvxstatic.h"

namespace libipvx 
{
	/****c* IP6Address/IP6Address
			 * NAME
			 *       IP6Addresss
			 * DESCRIPTION
			 *       LIBIPvX representation of an IPv6 address.
			 * PARAMETERS 
			 *       None.
			 * METHODS
			 *
			 * USAGE 
			 * SOURCE
			 */
	class IP6Address
	{
		public:
			IP6Address(std::string);
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
	/*******/
}

#endif
