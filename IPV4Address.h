#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include "stdafx.h"
#include "ipvxstatic.h"
	
namespace libipvx 
{
	/****c* IP4Address/IP4Address
		 * NAME
		 *       IP4Address
		 * DESCRIPTION
		 *       LIBIPvX representation of an IPv4 address.
		 * PARAMETERS 
		 *       None.
		 * METHODS
		 *	std::string				GetAddressString();
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetAddressBitset();
		 *	std::string				GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);		
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);	
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetBroadcastAddressBitset();
		 *	std::string				GetBroadcastAddressString();	
		 *	char					GetClass();
		 *	std::string				GetDefaultNetmask();
		 *	std::bitset<IPV4_OCTET_LENGTH>		GetFirstOctetBitset();
		 *	int					GetFirstOctetDecimal();	
		 *	std::bitset<IPV4_OCTET_LENGTH>		GetFourthOctetBitset();
		 *	int					GetFourthOctetDecimal();
		 *	std::string				GetInverseNetmaskString();
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetInverseNetmaskBitset();
		 *	int					GetNetmaskBitLength();
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetNetmaskBitset();
		 *	std::string				GetNetmaskAddressString();
		 *	std::bitset<IPV4_OCTET_LENGTH>		GetOctetBitsetByIndex(const int indexOfOctet);	
		 *	int					GetOctetDecimalByIndex(const int indexOfOctet);	
		 *	std::bitset<IPV4_ADDRESS_LENGTH>	GetSubnetAddressBitset();		
		 *	std::string				GetSubnetAddress();
		 *	int					GetSecondOctetDecimal();
		 *	std::bitset<IPV4_OCTET_LENGTH>		GetSecondOctetBitset();
		 *	int					GetThirdOctetDecimal();
		 *	std::bitset<IPV4_OCTET_LENGTH>		GetThirdOctetBitset();
		 *	bool					IsBroadcastAddress();
		 *	bool					IsSubnetAddress();		
		 *	bool					IsSubnetted();
		 *	std::unique_ptr<IP4Address>		GetFirstAddressInRange();
		 *	std::unique_ptr<IP4Address>		GetLastAddressInRange();
		 *	int					GetNetmaskHostPortionBitLength();
		 * USAGE 
		 *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
		 *
		 *       std::cout << "Decimal value of octet at index 0 is" << address->GetOctetDecimalByIndex(0) << std::endl;
		 *	 prints: "10"
		 * SOURCE
		 */
	class IP4Address
	{

	public:
		IP4Address(std::string _address) {
			this->bitset = ConvertIPv4StringToSTLBitset(_address);
			this->netmask = this->GetDefaultNetmask();		
		}

		~IP4Address(void) {
		}

		std::string				netmask;
		std::string				GetAddressString();
		std::bitset<IPV4_ADDRESS_LENGTH>	GetAddressBitset();
		std::string				GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);		
		std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
		std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);	
		std::bitset<IPV4_ADDRESS_LENGTH>	GetBroadcastAddressBitset();
		std::string				GetBroadcastAddressString();	
		char					GetClass();
		std::string				GetDefaultNetmask();
		std::bitset<IPV4_OCTET_LENGTH>		GetFirstOctetBitset();
		int					GetFirstOctetDecimal();	
		std::bitset<IPV4_OCTET_LENGTH>		GetFourthOctetBitset();
		int					GetFourthOctetDecimal();
		std::string				GetInverseNetmaskString();
		std::bitset<IPV4_ADDRESS_LENGTH>	GetInverseNetmaskBitset();
		int					GetNetmaskBitLength();
		std::bitset<IPV4_ADDRESS_LENGTH>	GetNetmaskBitset();
		std::string				GetNetmaskAddressString();
		std::bitset<IPV4_OCTET_LENGTH>		GetOctetBitsetByIndex(const int indexOfOctet);	
		int					GetOctetDecimalByIndex(const int indexOfOctet);	
		std::bitset<IPV4_ADDRESS_LENGTH>	GetSubnetAddressBitset();		
		std::string				GetSubnetAddress();
		int					GetSecondOctetDecimal();
		std::bitset<IPV4_OCTET_LENGTH>		GetSecondOctetBitset();
		int					GetThirdOctetDecimal();
		std::bitset<IPV4_OCTET_LENGTH>		GetThirdOctetBitset();
		bool					IsBroadcastAddress();
		bool					IsSubnetAddress();		
		bool					IsSubnetted();
		std::unique_ptr<IP4Address>		GetFirstAddressInRange();
		std::unique_ptr<IP4Address>		GetLastAddressInRange();
		int					GetNetmaskHostPortionBitLength();
	private:
		std::bitset<IPV4_ADDRESS_LENGTH>	bitset;
	};
	 /*******/	
}
#endif
