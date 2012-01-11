/*
  Copyright (C) 2012  Daniel Neil Hodder

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <string>
#include <bitset>
#include <math.h>
#include <memory>

#define IPV4_ADDRESS_LENGTH 32
#define IPV4_OCTET_LENGTH 8
#define IPV4_OCTET_COUNT 4
#define IPV4_FIRST_OCTET_INDEX 0
#define IPV4_SECOND_OCTET_INDEX 1
#define IPV4_THIRD_OCTET_INDEX 2
#define IPV4_FOURTH_OCTET_INDEX 3
#define IPV4_MAX_DECIMAL_VALUE 255
#define IPV4_ADDRESS_CLASS_A 'A'
#define IPV4_ADDRESS_CLASS_B 'B'
#define IPV4_ADDRESS_CLASS_C 'C'
#define IPV4_CLASS_A_DEFAULT_SUBNET_MASK "255.0.0.0"
#define IPV4_CLASS_B_DEFAULT_SUBNET_MASK "255.255.0.0"
#define IPV4_CLASS_C_DEFAULT_SUBNET_MASK "255.255.255.0"

class IP4Address
{
public:
	IP4Address(std::string _address) {
		this->addrSpace = this->ConvertIPv4StringToSTLBitset(_address);
		this->netmask = this->GetDefaultSubnetMask();
	}

	~IP4Address(void) {
	}

	std::bitset<IPV4_ADDRESS_LENGTH>	addrSpace;
	std::string							netmask;
	std::bitset<IPV4_ADDRESS_LENGTH>	ConvertIPv4StringToSTLBitset(const std::string _address);		
	std::bitset<IPV4_OCTET_LENGTH>		ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal);
	std::string							GetAddressString();
	std::bitset<IPV4_ADDRESS_LENGTH>	GetAddressBinary();
	std::string							GetAddressStringFromBinary(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);		
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);		
	std::bitset<IPV4_ADDRESS_LENGTH>	GetBroadcastAddressBinary();
	std::string							GetBroadcastAddress();	
	char								GetClass();	
	std::string							GetDefaultSubnetMask();
	std::bitset<IPV4_OCTET_LENGTH>		GetFirstOctetBinary();
	int									GetFirstOctetDecimal();	
	std::bitset<IPV4_OCTET_LENGTH>		GetFourthOctetBinary();
	int									GetFourthOctetDecimal();
	int									GetNetmaskBitLength();
	IP4Address							GetPreceedingIP4AddressInRange();
	std::auto_ptr<IP4Address> 			GetProceedingIP4AddressInRange();
	std::bitset<IPV4_OCTET_LENGTH>		GetOctetBinaryByIndex(const int indexOfOctet);	
	int									GetOctetDecimalByIndex(const int indexOfOctet);	
	std::bitset<IPV4_ADDRESS_LENGTH>	GetSubnetAddressBinary();		
	std::string							GetSubnetAddress();
	int									GetSecondOctetDecimal();
	std::bitset<IPV4_OCTET_LENGTH>		GetSecondOctetBinary();
	int									GetThirdOctetDecimal();
	std::bitset<IPV4_OCTET_LENGTH>		GetThirdOctetBinary();
	bool								IncrementOctet(int indexOfOctet);
	bool								IsBroadcastAddress();
	bool								IsSubnetAddress();		
	bool								HasNext();
	bool								IsSubnetted();

private:
	std::string							ConvertDecimalIntegerToEightBitBinaryString(int _integer);
};