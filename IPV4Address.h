#include "StdAfx.h"

class IP4Address
{
public:
	IP4Address(std::string _address) {
		this->bitset = this->ConvertIPv4StringToSTLBitset(_address);
		this->netmask = this->GetDefaultNetmask();
	}

	~IP4Address(void) {
	}

	std::bitset<IPV4_ADDRESS_LENGTH>	bitset;
	std::string							netmask;
	std::bitset<IPV4_ADDRESS_LENGTH>	ConvertIPv4StringToSTLBitset(const std::string _address);		
	std::bitset<IPV4_OCTET_LENGTH>		ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal);
	std::string							GetAddressString();
	std::bitset<IPV4_ADDRESS_LENGTH>	GetAddressBitset();
	std::string							GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);		
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);		
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBroadcastAddressBitset();
	std::string							GetBroadcastAddress();	
	char								GetClass();	
	std::string							GetDefaultNetmask();
	std::bitset<IPV4_OCTET_LENGTH>		GetFirstOctetBitset();
	int									GetFirstOctetDecimal();	
	std::bitset<IPV4_OCTET_LENGTH>		GetFourthOctetBitset();
	int									GetFourthOctetDecimal();
	std::string							GetInverseNetmaskString();
	std::bitset<IPV4_ADDRESS_LENGTH>	GetInverseNetmaskBitset();
	int									GetNetmaskBitLength();
	std::bitset<IPV4_ADDRESS_LENGTH>	GetNetmaskBitset();
	std::string							GetNetmaskAddressString();
	std::bitset<IPV4_OCTET_LENGTH>		GetOctetBinaryByIndex(const int indexOfOctet);	
	int									GetOctetDecimalByIndex(const int indexOfOctet);	
	std::bitset<IPV4_ADDRESS_LENGTH>	GetSubnetAddressBitset();		
	std::string							GetSubnetAddress();
	int									GetSecondOctetDecimal();
	std::bitset<IPV4_OCTET_LENGTH>		GetSecondOctetBitset();
	int									GetThirdOctetDecimal();
	std::bitset<IPV4_OCTET_LENGTH>		GetThirdOctetBitset();
	bool								IsBroadcastAddress();
	bool								IsSubnetAddress();		
	bool								IsSubnetted();
	std::auto_ptr<IP4Address>			GetFirstAddressInRange();
	std::auto_ptr<IP4Address>			GetLastAddressInRange();
	int									GetNetmaskHostPortionBitLength();

private:
	std::string							ConvertDecimalIntegerToEightBitBinaryString(int _integer);
};