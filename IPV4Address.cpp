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

#include "IPv4Address.h"

int IP4Address::GetNetmaskBitLength() {
	return this->GetNetmaskBitset().count();
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetNetmaskBitset() {
	return this->ConvertIPv4StringToSTLBitset(this->netmask);
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset) {
	return this->GetAddressBitset() & bitset;
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetAddressBitset() {
	return this->bitset;
}

bool IP4Address::IsSubnetted() {
	
	// Determine if we're subnetting by comparing the number of bits
	// in the netmask to the address class.

	if (( this->GetClass() == IPV4_ADDRESS_CLASS_A ) &&
		( this->GetNetmaskBitLength() == IPV4_CLASS_A_DEFAULT_SUBNET_LENGTH )) {
		return false;
	}

	if (( this->GetClass() == IPV4_ADDRESS_CLASS_B ) &&
		( this->GetNetmaskBitLength() == IPV4_CLASS_B_DEFAULT_SUBNET_LENGTH )) {
		return false;
	}

	if (( this->GetClass() == IPV4_ADDRESS_CLASS_C ) &&
		( this->GetNetmaskBitLength() == IPV4_CLASS_C_DEFAULT_SUBNET_LENGTH )) {
		return false;
	}

	return true;
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::ConvertIPv4StringToSTLBitset(const std::string _address) {
	// Index of each peroid in address string.
	// expected format, dec.dec.dec.dec;
	size_t _dot1 = _address.find(".");
	size_t _dot2 = _address.find(".", ( _dot1 + 1 ) );
	size_t _dot3 = _address.find(".", ( _dot2 + 1 ) );
			
	int octet1 = atoi(_address.substr(0, _dot1).c_str());
	int octet2 = atoi(_address.substr((_dot1 + 1), _dot2).c_str());
	int octet3 = atoi(_address.substr((_dot2 + 1), _dot3).c_str());
	int octet4 = atoi(_address.substr((_dot3 + 1), _address.length()).c_str());

	// convert each octet's decimal value to binary and save in string.
	std::string _binString = "";
	_binString = this->ConvertDecimalIntegerToEightBitBinaryString(octet1);
	_binString += this->ConvertDecimalIntegerToEightBitBinaryString(octet2);
	_binString += this->ConvertDecimalIntegerToEightBitBinaryString(octet3);
	_binString += this->ConvertDecimalIntegerToEightBitBinaryString(octet4);

	std::bitset<IPV4_ADDRESS_LENGTH> addrBits;

	// loop to access each octet in the ipv4 address string.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ )
	{
		// loop to access each bit in indexed octet.
		for ( size_t b = 0; b < IPV4_OCTET_LENGTH; b++ ) {
			
			// Set bit to bool value at same index within the _address string
			bool bit = (_binString.at( (i * 8) + b ) == 1) ? true : false;
			addrBits.set((i * 8) + b, bit);
		}
	}

	return addrBits;
}

std::string IP4Address::GetSubnetAddress() {
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = this->ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean AND.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolANDbits = this->GetBitwiseBooleanANDResult(netmaskBits);	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolANDbits);
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::ConvertSingleOctetFromDecimalToSTLBitset(const int _OctetDecimal) {
	std::bitset<IPV4_OCTET_LENGTH> octetBitset;
	
	std::string octetString = this->ConvertDecimalIntegerToEightBitBinaryString(_OctetDecimal);

	// loop to access each bit in indexed octet.
	for ( size_t b = 0; b < IPV4_OCTET_LENGTH; b++ ) {
		// Set bit to bool value at same index within the _address string
		bool bit = ( octetString.at(b) == 1) ? true : false;
		octetBitset.set(b, bit);
	}

	return octetBitset;
}

std::string IP4Address::GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) {
	
	std::string _addressString;
	for ( int o = 0; o < IPV4_OCTET_COUNT; o++ ){
		
		int octet = 0;
		int val = 128;

		for ( int b = 0; b < IPV4_OCTET_LENGTH; b++) {

			if ( _bitset.at( ( 8 * o) + b) == 1) {
				octet += val;
			}

			val /= 2;
		}
		
		std::stringstream ss;
		ss << octet;
		_addressString += ss.str();

		if ( o != 3 ) {
			_addressString += ".";
		}
	}

	return _addressString;
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBitwiseNOTResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) {
	std::bitset<IPV4_ADDRESS_LENGTH> tempBitset = _bitset;
	return tempBitset.flip();
}

std::string IP4Address::GetBroadcastAddress() {
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = this->ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean OR.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolORbits = this->GetBitwiseBooleanORResult(this->GetBitwiseNOTResult(netmaskBits));	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolORbits);
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset)
{
	return this->GetAddressBitset() | bitset; 
}

std::string IP4Address::ConvertDecimalIntegerToEightBitBinaryString(const int _integer) {
	std::string _binaryString;
	int tempInt = _integer;
	while ( tempInt > 0 ) {
		_binaryString += tempInt % 2;
		tempInt /= 2;
	}

	// Insert 0s into the start of the string until it's 8 bits in length.
	while ( _binaryString.length() < 8 ) {
		std::string zeroString;
		int zero = 10 % 2;
		zeroString += zero;
		_binaryString.append(zeroString);
	}

	// reverse the string to properly represent an binary ip address space.
	// damn std::string andlittle-endianess! just tricking ;)
	std::reverse(_binaryString.begin() , _binaryString.end());

	return _binaryString;
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBroadcastAddressBitset() {
	return this->ConvertIPv4StringToSTLBitset(this->GetBroadcastAddress());
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetSubnetAddressBitset() {
		return this->ConvertIPv4StringToSTLBitset(this->GetSubnetAddress());
}

std::string IP4Address::GetAddressString() {
	return this->GetAddressStringFromBitset(this->bitset);
}

bool IP4Address::IsBroadcastAddress() {
	return ( this->GetBroadcastAddressBitset() == this->bitset ) ? true : false;	
}

bool IP4Address::IsSubnetAddress() {
	return ( this->GetSubnetAddressBitset() == this->bitset ) ? true : false;
}

int IP4Address::GetOctetDecimalByIndex(const int indexOfOctet) {
	std::bitset<IPV4_OCTET_LENGTH> bitset = this->GetOctetBinaryByIndex(indexOfOctet);

	int octetDecimal = 0;

	int max = 128;

	for ( size_t i = 0; i < IPV4_OCTET_LENGTH; i++ ) {
		if ( bitset.at(i) == 1 ) {
			octetDecimal += max;			
		}
		max /= 2;
	}

	return octetDecimal;
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetOctetBinaryByIndex(const int indexOfOctet) {

	std::bitset<IPV4_OCTET_LENGTH> bitset;

	for ( size_t i = IPV4_FIRST_OCTET_INDEX; i < IPV4_OCTET_LENGTH; i++ ) {
		bitset.set(i, this->bitset.at( ( indexOfOctet * 8 ) + i) );
	}

	return bitset;
}

int	IP4Address::GetFirstOctetDecimal() {

	return this->GetOctetDecimalByIndex(IPV4_FIRST_OCTET_INDEX);
}

int	IP4Address::GetSecondOctetDecimal() {

	return this->GetOctetDecimalByIndex(IPV4_SECOND_OCTET_INDEX);
}

int	IP4Address::GetThirdOctetDecimal() {

	return this->GetOctetDecimalByIndex(IPV4_THIRD_OCTET_INDEX);
}

int	IP4Address::GetFourthOctetDecimal() {

	return this->GetOctetDecimalByIndex(IPV4_FOURTH_OCTET_INDEX);
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetFirstOctetBitset() {

	return this->GetOctetBinaryByIndex(IPV4_FIRST_OCTET_INDEX);
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetSecondOctetBitset() {

	return this->GetOctetBinaryByIndex(IPV4_SECOND_OCTET_INDEX);
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetThirdOctetBitset() {

	return this->GetOctetBinaryByIndex(IPV4_THIRD_OCTET_INDEX);
}

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetFourthOctetBitset() {

	return this->GetOctetBinaryByIndex(IPV4_FOURTH_OCTET_INDEX);
}

std::string IP4Address::GetDefaultNetmask() {
	if ( this->GetClass() == IPV4_ADDRESS_CLASS_A) {
		return IPV4_CLASS_A_DEFAULT_SUBNET_MASK;
	}
	else if ( this->GetClass() == IPV4_ADDRESS_CLASS_B ) {
		return IPV4_CLASS_B_DEFAULT_SUBNET_MASK;
	}
	else if ( this->GetClass() == IPV4_ADDRESS_CLASS_C ) {
		return IPV4_CLASS_C_DEFAULT_SUBNET_MASK;
	}
	else {
		return "Probably an invalid IP class.";
	}
}

char IP4Address::GetClass() {
	
	// Check the first octet for the whereabouts of the zero bit
	// as this is indicative the class.
		
	if ( this->GetFirstOctetBitset().at(0) == false ) {
		// if first bit is zero, then address is class A.
		return IPV4_ADDRESS_CLASS_A;		
	}
	else if ( this->GetFirstOctetBitset().at(1) == false ) {
		// if second bit is zero, then address is class B.
		return IPV4_ADDRESS_CLASS_B;		
	}
	else if ( this->GetFirstOctetBitset().at(2) == false ) {
		// if third bit is zero, then address is class C.
		return IPV4_ADDRESS_CLASS_C;		
	}
	else if ( this->GetFirstOctetBitset().at(3) == false ) {
		// if fourth bit is zero, then address is class D.
		return IPV4_ADDRESS_CLASS_D;		
	}	
	else if ( this->GetFirstOctetBitset().at(4) == false ) {
		// if fifth bit is zero, then address is class E.
		return  IPV4_ADDRESS_CLASS_E;		
	}
	
	return 'X'; // yelp! nothing can possible (sic) go wrong...that's the first thing that's gone wrong.
}

std::string	IP4Address::GetNetmaskAddressString() {
	return this->netmask;
}

std::string	IP4Address::GetInverseNetmaskString(){
	std::bitset<IPV4_ADDRESS_LENGTH> bitset = this->GetInverseNetmaskBitset();
	return this->GetAddressStringFromBitset(bitset);
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetInverseNetmaskBitset() {
	std::bitset<IPV4_ADDRESS_LENGTH> bitset = this->ConvertIPv4StringToSTLBitset(this->GetNetmaskAddressString());
	bitset.flip();	
	return bitset;
}

std::auto_ptr<IP4Address> IP4Address::GetFirstAddressInRange() {
	
	// Get the bitset of the subnet address.
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetSubnetAddressBitset();

	// Toggle the last bit.
	_bitset.set(IPV4_ADDRESS_LENGTH -1, true);

	// Get the address string.
	std::string _addressString = this->GetAddressStringFromBitset(_bitset);

	std::auto_ptr<IP4Address> _addr(new IP4Address(_addressString));
	_addr->netmask = this ->GetNetmaskAddressString();
	return _addr;
}

std::auto_ptr<IP4Address> IP4Address::GetLastAddressInRange() {
	// Get the bitset of the broadcast address.
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetBroadcastAddressBitset();

	// Toggle the last bit off.
	_bitset.set(IPV4_ADDRESS_LENGTH -1, false);

	// Get the address string.
	std::string _addressString = this->GetAddressStringFromBitset(_bitset);

	std::auto_ptr<IP4Address> _addr(new IP4Address(_addressString));
	_addr->netmask = this ->GetNetmaskAddressString();
	return _addr;
}

int	IP4Address::GetNetmaskHostPortionBitLength() {
	int hostSize = IPV4_ADDRESS_LENGTH - this->GetNetmaskBitLength();
	return hostSize;
}
