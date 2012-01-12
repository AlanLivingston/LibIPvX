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