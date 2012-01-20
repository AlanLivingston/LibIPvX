/*
  Copyright (C) 2012  The FOSS Project

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

#include "IPV4Address.h"

int IP4Address::GetNetmaskBitLength() 
/****f* LibIPvX/GetNetmaskBitLength();
         * NAME
         *       GetNetmaskBitLength();
         * DESCRIPTION
         *       Returns the length (the number of sequential 'on' bits) of the bitset of the netmask address.
         * PARAMETERS
         *       None
         * RETURN VALUE
         *       int 
         * USAGE
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << address->GetNetmaskBitLength() << std::endl;
         *       // prints "8", which is the default netmask for class A addresses. 
         * SOURCE
         */
{
	return this->GetNetmaskBitset().count();
}
/*******/

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetNetmaskBitset() 
/****f* LibIPvX/GetNetmaskBitset();
         * NAME
         *       GetNetmaskBitset();
         * DESCRIPTION
         *       Returns the bitset of the netmask address.
         * PARAMETERS
         *       None
         * RETURN VALUE
         *       std::bitset<IPV4_ADDRESS_LENGTH>
         * USAGE
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	 *	 address->netmask = "255.255.128.0";
         *       std::cout << "Netmask's bitset is " << address->GetNetmaskBitset() << std::endl;
         *       // Prints "Netmask's bitset is 00000000000000011111111111111111"
         * SOURCE
         */
{	
	// Grab the netmask's dotted decimal representation and convert it to an STL bitset.

	return ConvertIPv4StringToSTLBitset(this->netmask);
}
/*******/

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

std::string IP4Address::GetSubnetAddress() {
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean AND result of the netmask's bitset value.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolANDbits = this->GetBitwiseBooleanANDResult(netmaskBits);	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolANDbits);
}

std::string IP4Address::GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) {
	
	std::string _addressString;
	for ( int o = 0; o < IPV4_OCTET_COUNT; o++ ){
		
		int octet = 0;
		int val = 128;

		for ( int b = 0; b < IPV4_OCTET_LENGTH; b++) {

			if ( _bitset[( IPV4_OCTET_LENGTH * o) + b] == 1 && ((8 * o) + b) < _bitset.size()  ) {
				octet += val;
			}
			//Shift by 1 same as /= 2
			val = val >> 1;
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

std::string IP4Address::GetBroadcastAddressString() 
/****f* LibIPvX/GetBroadcastAddressString();
	* NAME
	*	GetBroadcastAddressString();
	* DESCRIPTION
	*	Returns a string representation of the broadcast address in dotted decimal format.
	* PARAMETERS 
	*	None.
	* RETURN VALUE
	*	std::string
	* USAGE	
	*       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
        *       std::cout << address->GetBroadcastAddressString() << std::endl;
        *       // Prints the broadcast address  "10.1.127.255"
	* SOURCE
	*/
{
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean OR.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolORbits = this->GetBitwiseBooleanORResult(this->GetBitwiseNOTResult(netmaskBits));	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolORbits);
}
/*******/

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset)
/****f* LibIPvX/GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	* NAME
	*	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> bitset);
	* DESCRIPTION
	*	Returns the bitset result from performing a bitwise boolean OR on the address's bitset with that of the bitset parameter.
	* PARAMETERS 
	*	const std::bitset<IPV4_ADDRESS_LENGTH> bitset; 	
	*	bitset on which to perform the bitwise boolean OR again.
	* RETURN VALUE
	*	std::bitset<IPV4_ADDRESS_LENGTH>
	* USAGE	
	*	// Get the netmask's bitset value.
	*	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ConvertIPv4StringToSTLBitset(this->netmask);
	*
	* 	// Perform bitwise boolean OR.
	*	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolORbits = this->GetBitwiseBooleanORResult(netmaskBits);	
	* SOURCE
	*/
{
	return this->GetAddressBitset() | bitset; 
}
/*******/

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetBroadcastAddressBitset() 
/****f* LibIPvX/GetBroadcastAddressBitset();
         * NAME
         *       GetBroadcastAddressBitset();
         * DESCRIPTION
         *       Returns the bitset of the broadcast address.
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       std::bitset<IPV4_ADDRESS_LENGTH>
         * USAGE 
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << address->GetBroadcastAddressBitset() << std::endl;
         *       // prints the bitset value of the broadcast address of ip address 10.1.5.2. 
         * SOURCE
         */
{
	return ConvertIPv4StringToSTLBitset(this->GetBroadcastAddressString());
}
/*******/

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetSubnetAddressBitset() 
/****f* LibIPvX/GetSubnetAddressBitset();
        * NAME
        *       GetSubnetAddressBitset();
        * DESCRIPTION
        *       Returns the bitset of the subnet address.
        * PARAMETERS 
        *       None        
        * RETURN VALUE
        *       std::bitset<IPV4_ADDRESS_LENGTH>
        * USAGE 
        *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
        *       std::cout << address->GetSubnetAddressBitset() << std::endl;
        *       // prints the bitset value of the subnet address of ip address 10.1.5.2. 
        * SOURCE
        */
{
	return ConvertIPv4StringToSTLBitset(this->GetSubnetAddress());
}
/*******/

std::string IP4Address::GetAddressString() 
/****f* LibIPvX/GetAddressString();
        * NAME
        *       GetAddressString(); 
        * DESCRIPTION
        *       Returns the decimal representation of the address in dotted string format e.g. "10.1.1.1" 
        * PARAMETERS 
        * 	None        
        * RETURN VALUE
        *       std::string
        * USAGE 
        *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
        *       std::cout << address->GetAddressString() << std::endl;
	*	// prints "10.1.5.2"
        * SOURCE
        */
{
	return this->GetAddressStringFromBitset(this->bitset);
}
/*******/

bool IP4Address::IsBroadcastAddress() 
/****f* LibIPvX/IsBroadcastAddress();
	* NAME
	*	IsBroadcastAddress();
	* DESCRIPTION
	*	Retusn true if the address is broadcast address of the range as per the netmask, false if not.
	* PARAMETERS 
	*	None	
	* RETURN VALUE
	*	bool
	* USAGE	
	*	std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	*	if ( address->IsBroadcastAddress() ) {
	*		std::cout << "Address is a broadcast." << std::endl;
	*	}	
 	*	// prints "Address is a broadcast."
	* SOURCE
	*/
{
	return ( this->GetBroadcastAddressBitset() == this->bitset ) ? true : false;	
}
/*******/	

bool IP4Address::IsSubnetAddress() 
/****f* LibIPvX/IsSubnetAddress();	
	* NAME
	*	IsSubnetAddress();
	* DESCRIPTION
	*	Returns true if the address is the subnet address of the range as per the netmask, false if not. 
	* PARAMETERS 
	*	NONE	
	* RETURN VALUE
	*	bool
	* EXAMPLE	
	*	std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	*	if ( address->IsSubnetted() ) {
	*		std::cout << "Address is subnet address of current range." << std::endl;
	*	}	
	*	// prints "Address is subnet address of current range." 
	* SOURCE
	*/
{
	return ( this->GetSubnetAddressBitset() == this->bitset ) ? true : false;
}
 /*******/	

int IP4Address::GetOctetDecimalByIndex(const int indexOfOctet) 
/****f* LibIPvX/GetOctetDecimalByIndex(const int indexOfOctet);
         * NAME
         *       GetOctetDecimalByIndex(const int indexOfOctet);
         * DESCRIPTION
         *       Gets the decimal value of the octet at the index specified by indexOfOctet.
         * PARAMETERS 
         *       The index (0..3) of the desired octet.    
         * RETURN VALUE
         *       int 
         * USAGE 
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *
         *       std::cout << "Decimal value of octet at index 0 is" << address->GetOctetDecimalByIndex(0) << std::endl;
	 *	 prints: "10"
         * SOURCE
         */
{
	std::bitset<IPV4_OCTET_LENGTH> bitset = this->GetOctetBinaryByIndex(indexOfOctet);

	int octetDecimal = 0;

	int max = 128;

	for ( size_t i = 0; i < IPV4_OCTET_LENGTH; i++ ) {
		if ( bitset[i] == 1 && i < bitset.size() ) {
			octetDecimal += max;			
		}
		//Shift right 1 same as /= 2 more effecient
		max = max >> 1;
	}

	return octetDecimal;
}
/*******/

std::bitset<IPV4_OCTET_LENGTH> IP4Address::GetOctetBinaryByIndex(const int indexOfOctet) 
/****f* LibIPvX/GetOctetBinaryByIndex(const int indexOfOctet);

	* NAME
	*	GetOctetBinaryByIndex(const int indexOfOctet);
	* DESCRIPTION
	*	Returns the bitset of the octet at the index specified by indexOfOctet.

	* PARAMETERS 
	*	The index (0..3) of the desired octet.
	* RETURN VALUE
	*	std::bitset<IPV4_OCTET_LENGTH>
	* USAGE	
        *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
        *       std::cout << "Bitset value of octet at index 0 is" << address->GetOctetDecimalByIndex(0) << std::endl;
	*	prints: "10"
	* SOURCE
	*/
{
	std::bitset<IPV4_OCTET_LENGTH> _bitset;

	for ( size_t i = IPV4_FIRST_OCTET_INDEX; i < IPV4_OCTET_LENGTH; i++ ) {
		_bitset.set(i, this->bitset[ ( indexOfOctet * 8 ) + i] );
	}

	return _bitset;
}
/*******/

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
		
	if ( this->GetFirstOctetBitset()[0] == false ) {
		// if first bit is zero, then address is class A.
		return IPV4_ADDRESS_CLASS_A;		
	}
	else if ( this->GetFirstOctetBitset()[1] == false ) {
		// if second bit is zero, then address is class B.
		return IPV4_ADDRESS_CLASS_B;		
	}
	else if ( this->GetFirstOctetBitset()[2] == false ) {
		// if third bit is zero, then address is class C.
		return IPV4_ADDRESS_CLASS_C;		
	}
	else if ( this->GetFirstOctetBitset()[3] == false ) {
		// if fourth bit is zero, then address is class D.
		return IPV4_ADDRESS_CLASS_D;		
	}	
	else if ( this->GetFirstOctetBitset()[4] == false ) {
		// if fifth bit is zero, then address is class E.
		return  IPV4_ADDRESS_CLASS_E;		
	}
	
	return 'X'; // yelp! nothing can possible (sic) go wrong...well gee, that's the first thing that's gone wrong.
}

std::string	IP4Address::GetNetmaskAddressString() {
	return this->netmask;
}

std::string	IP4Address::GetInverseNetmaskString(){
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetInverseNetmaskBitset();
	return this->GetAddressStringFromBitset(_bitset);
}

std::bitset<IPV4_ADDRESS_LENGTH> IP4Address::GetInverseNetmaskBitset() {
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = ConvertIPv4StringToSTLBitset(this->GetNetmaskAddressString());
	_bitset.flip();	
	return _bitset;
}

std::unique_ptr<IP4Address> IP4Address::GetFirstAddressInRange() {
	
	// Get the bitset of the subnet address.
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetSubnetAddressBitset();

	// Toggle the last bit.
	_bitset.set(IPV4_ADDRESS_LENGTH -1, true);

	// Get the address string.
	std::string _addressString = this->GetAddressStringFromBitset(_bitset);

	std::unique_ptr<IP4Address> _addr(new IP4Address(_addressString));
	_addr->netmask = this ->GetNetmaskAddressString();
	return _addr;
}

std::unique_ptr<IP4Address> IP4Address::GetLastAddressInRange() {
	// Get the bitset of the broadcast address.
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetBroadcastAddressBitset();

	// Toggle the last bit off.
	_bitset.set(IPV4_ADDRESS_LENGTH -1, false);

	// Get the address string.
	std::string _addressString = this->GetAddressStringFromBitset(_bitset);

	std::unique_ptr<IP4Address> _addr(new IP4Address(_addressString));
	_addr->netmask = this ->GetNetmaskAddressString();
	return _addr;
}

int	IP4Address::GetNetmaskHostPortionBitLength() {
	int hostSize = IPV4_ADDRESS_LENGTH - this->GetNetmaskBitLength();
	return hostSize;
}
