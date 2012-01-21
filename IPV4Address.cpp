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

/****m* IP4Address/GetNetmaskBitLength();
         * NAME
         *       GetNetmaskBitLength();
         * DESCRIPTION
         *       Returns the length (the number of sequential 'on' bits) of the bitset of the netmask address.
         * PARAMETERS
         *       None
         * RETURN VALUE
         *       int 
         * USAGE
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << "Bit length of netmask is: " << address->GetNetmaskBitLength() << std::endl;
         *       // prints "Bit length of netmask is: 8", which is the default bit length for class A ip4 addresses. 
	 *
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetNetmaskBitLength() 
{
	// Return the number of sequential 'on' bits. 
	return this->GetNetmaskBitset().count();
}
/*******/

/****m* IP4Address/GetNetmaskBitset();
         * NAME
         *       GetNetmaskBitset();
         * DESCRIPTION
         *       Returns the bitset of the netmask address.
         * PARAMETERS
         *       None
         * RETURN VALUE
         *       std::bitset<IPV4_ADDRESS_LENGTH>
         * USAGE
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
	 *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	 *	 address->netmask = "255.255.128.0";
         *       std::cout << "Netmask's bitset is " << address->GetNetmaskBitset() << std::endl;
         *       // Prints "Netmask's bitset is 00000000000000011111111111111111"
	 *
         *   	return 0;
         * }      
         * SOURCE
         */
std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetNetmaskBitset()
{	
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = ::ConvertIPv4StringToSTLBitset(this->netmask);

	return _bitset;
}
/*******/


std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetBitwiseBooleanANDResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) 
{
	return this->GetAddressBitset() & _bitset;
}

std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetAddressBitset() {
	return this->bitset;
}

bool libipvx::IP4Address::IsSubnetted() {
	
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

std::string libipvx::IP4Address::GetSubnetAddress() {
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean AND result of the netmask's bitset value.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolANDbits = this->GetBitwiseBooleanANDResult(netmaskBits);	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolANDbits);
}


/****m* IP4Address/GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* NAME
	*	GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* DESCRIPTION
	*	Performs a bitwise NOT (flips) the bitset parameter and returns the result.
	* PARAMETERS 
	*	_bitset - the bitset to flip.
	* RETURN VALUE
	*	std::string 
	* USAGE	
        * #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
	*       std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	*	std::unique_ptr<IP4Address> _subnet(new IP4Address("255.255.128.0"));
 	*	std::bitset<IPV4_ADDRESS_LENGTH> _result = _address->GetBitwiseNOTResult(_subnet->GetAddressBitset());
	*
        *   	return 0;
        * }
	* SOURCE
	*/
std::string libipvx::IP4Address::GetAddressStringFromBitset(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset) 
{
	
	std::string _addressString;
	for ( int o = 0; o < IPV4_OCTET_COUNT; o++ ){
		
		int octet = 0;
		int val = 128;

		for ( int b = 0; b < IPV4_OCTET_LENGTH; b++) {

			if ( _bitset[( IPV4_OCTET_LENGTH * o) + b] == 1 && ((8 * o) + b) < _bitset.size()  ) {
				octet += val;
			}
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
/*******/

/****m* IP4Address/GetBroadcastAddressString();
	* NAME
	*	GetBroadcastAddressString();
	* DESCRIPTION
	*	Returns a string representation of the broadcast address in dotted decimal format.
	* PARAMETERS 
	*	None.
	* RETURN VALUE
	*	std::string
	* USAGE	
        * #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
	*       std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	*	_address->netmask = "255.255.128.0";
        *       std::cout << _address->GetBroadcastAddressString() << std::endl;
        *       // Prints the broadcast address  "10.1.127.255"
	*
        *   	return 0;
        * }
	* SOURCE
	*/
std::string libipvx::IP4Address::GetBroadcastAddressString() 
{
	// Covert the std::string netmask into a bitset.
	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ::ConvertIPv4StringToSTLBitset(this->netmask);

	// Get the bitwise boolean OR.
	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolORbits = this->GetBitwiseBooleanORResult(::GetBitwiseNOTResult(netmaskBits));	

	// Return the decimal formatted string.
	return this->GetAddressStringFromBitset(bitwiseBoolORbits);
}
/*******/

/****m* IP4Address/GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* NAME
	*	GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset);
	* DESCRIPTION
	*	Returns the bitset result from performing a bitwise boolean OR on the address's bitset with that of the bitset parameter.
	* PARAMETERS 
	*	const std::bitset<IPV4_ADDRESS_LENGTH> _bitset; 	
	*	bitset on which to perform the bitwise boolean OR again.
	* RETURN VALUE
	*	std::bitset<IPV4_ADDRESS_LENGTH>
	* USAGE	
        * #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
	*	// Get the netmask's bitset value.
	*	std::bitset<IPV4_ADDRESS_LENGTH> netmaskBits = ConvertIPv4StringToSTLBitset(this->netmask);
	*
	* 	// Perform bitwise boolean OR.
	*	std::bitset<IPV4_ADDRESS_LENGTH> bitwiseBoolORbits = this->GetBitwiseBooleanORResult(netmaskBits);	
	*
        *   	return 0;
        * }
	* SOURCE
	*/
std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetBitwiseBooleanORResult(const std::bitset<IPV4_ADDRESS_LENGTH> _bitset)
{
	return this->GetAddressBitset() | _bitset; 
}
/*******/

/****m* IP4Address/GetBroadcastAddressBitset();
         * NAME
         *       GetBroadcastAddressBitset();
         * DESCRIPTION
         *       Returns the bitset of the broadcast address.
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       std::bitset<IPV4_ADDRESS_LENGTH>
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 * 	 std::bitset<IPV4_ADDRESS_LENGTH> _bitset = _address->GetBroadcastAddressBitset();
    	 *
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetBroadcastAddressBitset() 
{
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = ::ConvertIPv4StringToSTLBitset(this->GetBroadcastAddressString());
	return _bitset;
}
/*******/

/****m* IP4Address/GetSubnetAddressBitset();
        * NAME
        *       GetSubnetAddressBitset();
        * DESCRIPTION
        *       Returns the bitset of the subnet address.
        * PARAMETERS 
        *       None        
        * RETURN VALUE
        *       std::bitset<IPV4_ADDRESS_LENGTH>
        * USAGE 
	* #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
        *       std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
        *       std::bitset<IPV4_ADDRESS_LENGTH> _bitset = _address->GetSubnetAddressBitset();
        *   	return 0;
        * }
        * SOURCE
        */
std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetSubnetAddressBitset() 
{
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = ::ConvertIPv4StringToSTLBitset(this->GetSubnetAddress());
	return _bitset;
}
/*******/

/****m* IP4Address/GetAddressString();
        * NAME
        *       GetAddressString(); 
        * DESCRIPTION
        *       Returns the decimal representation of the address in dotted decimal format e.g. "10.1.1.1" 
        * PARAMETERS 
        * 	None        
        * RETURN VALUE
        *       std::string
        * USAGE 
	* #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
        *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
        *       std::cout << address->GetAddressString() << std::endl;
	*	// prints "10.1.5.2"
        *   	return 0;
        * }	
        * SOURCE
        */
std::string libipvx::IP4Address::GetAddressString()
{
	return this->GetAddressStringFromBitset(this->bitset);
}
/*******/

/****m* IP4Address/IsBroadcastAddress();
	* NAME
	*	IsBroadcastAddress();
	* DESCRIPTION
	*	Returns true if the address is broadcast address of the range as per the netmask, false if not.
	* PARAMETERS 
	*	None.
	* RETURN VALUE
	*	bool
	* USAGE
	* #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
	*	std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	*	if ( address->IsBroadcastAddress() ) {
	*		std::cout << "Address is a broadcast." << std::endl;
	*	}	
        *   	return 0;
        * }	
	* SOURCE
	*/
bool libipvx::IP4Address::IsBroadcastAddress() 
{
	return ( this->GetBroadcastAddressBitset() == this->bitset ) ? true : false;	
}
/*******/	

/****m* IP4Address/IsSubnetAddress();	
	* NAME
	*	IsSubnetAddress();
	* DESCRIPTION
	*	Returns true if the address is the subnet address of the range as per the netmask, false if not. 
	* PARAMETERS 
	*	NONE	
	* RETURN VALUE
	*	bool
	* USAGE
	* #include "libipvx.h"
        * using namespace libipvx;
        * 
        * int main ()
        * {
	*	std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	*	if ( _address->IsSubnetted() ) {
	*		std::cout << "Address is subnet address of current range." << std::endl;
	*	}	
	*
        *   	return 0;
        * }	
	* SOURCE
	*/
bool libipvx::IP4Address::IsSubnetAddress() 
{
	return ( this->GetSubnetAddressBitset() == this->bitset ) ? true : false;
}
 /*******/	


/****m* IP4Address/GetOctetDecimalByIndex(const int indexOfOctet);
         * NAME
         *       GetOctetDecimalByIndex(const int indexOfOctet);
         * DESCRIPTION
         *       Gets the decimal value of the octet at the index specified by indexOfOctet.
         * PARAMETERS 
         *       The index (0..3) of the desired octet.    
         * RETURN VALUE
         *       int 
         * USAGE 
	 * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << "Decimal value of octet at index 0 is: " << address->GetOctetDecimalByIndex(0) << std::endl;
	 *	 prints: "Decimal value of octet at index 0 is: 10"
         *   	 return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetOctetDecimalByIndex(const int indexOfOctet) 
{
	std::bitset<IPV4_OCTET_LENGTH> bitset = this->GetOctetBitsetByIndex(indexOfOctet);

	int octetDecimal = 0;

	int max = 128;

	for ( size_t i = 0; i < IPV4_OCTET_LENGTH; i++ ) {
		if ( bitset[i] == 1 && i < bitset.size() ) {
			octetDecimal += max;			
		}
		max = max >> 1;
	}

	return octetDecimal;
}
/*******/

/****m* IP4Address/GetOctetBitsetByIndex(const int indexOfOctet);
         * NAME
         *       GetOctetBitsetByIndex(const int indexOfOctet);;
         * DESCRIPTION
         *       Returns the bitset of the octet at the index specified by indexOfOctet
         * PARAMETERS 
         *       The index (0..3) of the desired octet.
         * RETURN VALUE
         *       std::bitset<IPV4_OCTET_LENGTH>
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	std::bitset<IPV4_OCTET_LENGTH>  _bitset = _address->GetOctetBitsetByIndex(IPV4_FIRST_OCTET_INDEX);
	 *	// returns the first octet.
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_OCTET_LENGTH> libipvx::IP4Address::GetOctetBitsetByIndex(const int indexOfOctet) 
{
	std::bitset<IPV4_OCTET_LENGTH> _bitset;

	for ( size_t i = IPV4_FIRST_OCTET_INDEX; i < IPV4_OCTET_LENGTH; i++ ) {
		_bitset.set(i, this->bitset[ ( indexOfOctet * 8 ) + i] );
	}

	return _bitset;
}
/*******/

/****m* IP4Address/GetFirstOctetDecimal();
         * NAME
         *       GetFirstOctetDecimal()
         * DESCRIPTION
         *       Returns the first octet's decimal value.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       int
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	int _dec = _address->GetFirstOctetDecimal();
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetFirstOctetDecimal() 
{
	int _dec = this->GetOctetDecimalByIndex(IPV4_FIRST_OCTET_INDEX);
	return _dec;
}
/*******/

/****m* IP4Address/GetSecondOctetDecimal();
         * NAME
         *       GetSecondOctetDecimal()
         * DESCRIPTION
         *       Returns the second octet's decimal value.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       int
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	int _dec = _address->GetSecondOctetDecimal();
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetSecondOctetDecimal() 
{
	int _dec = this->GetOctetDecimalByIndex(IPV4_SECOND_OCTET_INDEX);
	return _dec;
}
/*******/

/****m* IP4Address/GetThirdOctetDecimal();
         * NAME
         *       GetThirdOctetDecimal()
         * DESCRIPTION
         *       Returns the third octet's decimal value.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       int
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	int _dec = _address->GetThirdOctetDecimal();
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetThirdOctetDecimal() 
{
	int _dec = this->GetOctetDecimalByIndex(IPV4_THIRD_OCTET_INDEX);
	return _dec;
}
/*******/

/****m* IP4Address/GetFourthOctetDecimal();
         * NAME
         *       GetFourthOctetDecimal()
         * DESCRIPTION
         *       Returns the fourth octet's decimal value.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       int
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	int _dec = _address->GetFourthOctetDecimal();
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetFourthOctetDecimal() 
{
	int _dec = this->GetOctetDecimalByIndex(IPV4_FOURTH_OCTET_INDEX);
	return _dec;
}
/*******/

/****m* IP4Address/GetFirstOctetBitset();
         * NAME
         *       GetFirstOctetBitset()
         * DESCRIPTION
         *       Returns the first octet's bitset.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::bitset<IPV4_OCTET_LENGTH> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	std::bitset<IPV4_OCTET_LENGTH> _oct = address->GetFirstOctetBitset();
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_OCTET_LENGTH> libipvx::IP4Address::GetFirstOctetBitset() 
{
	std::bitset<IPV4_OCTET_LENGTH> _oct = this->GetOctetBitsetByIndex(IPV4_FIRST_OCTET_INDEX);
	return _oct;
}
/*******/

/****m* IP4Address/GetSecondOctetBitset();
         * NAME
         *       GetSecondOctetBitset()
         * DESCRIPTION
         *       Returns the second octet's bitset.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::bitset<IPV4_OCTET_LENGTH> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	std::bitset<IPV4_OCTET_LENGTH> _oct = address->GetSecondOctetBitset();
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_OCTET_LENGTH> libipvx::IP4Address::GetSecondOctetBitset() 
{
	std::bitset<IPV4_OCTET_LENGTH> _oct = this->GetOctetBitsetByIndex(IPV4_SECOND_OCTET_INDEX);
	return _oct;
}
/*******/

/****m* IP4Address/GetThirdOctetBitset();
         * NAME
         *       GetThirdOctetBitset()
         * DESCRIPTION
         *       Returns the third octet's bitset.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::bitset<IPV4_OCTET_LENGTH> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	std::bitset<IPV4_OCTET_LENGTH> _oct = _address->GetThirdOctetBitset();
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_OCTET_LENGTH> libipvx::IP4Address::GetThirdOctetBitset() 
{
	std::bitset<IPV4_OCTET_LENGTH> _oct = this->GetOctetBitsetByIndex(IPV4_THIRD_OCTET_INDEX);
	return _oct;
}
/*******/

/****m* IP4Address/GetFourthOctetBitset();
         * NAME
         *       GetFourthOctetBitset()
         * DESCRIPTION
         *       Returns the fourth octet's bitset.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::bitset<IPV4_OCTET_LENGTH> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	std::bitset<IPV4_OCTET_LENGTH> _oct = _address->GetFourthOctetBitset();
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_OCTET_LENGTH> libipvx::IP4Address::GetFourthOctetBitset() 
{
	std::bitset<IPV4_OCTET_LENGTH> _oct = this->GetOctetBitsetByIndex(IPV4_FOURTH_OCTET_INDEX);
	return _oct;
}
/*******/

/****m* IP4Address/GetDefaultNetmask();
         * NAME
         *       GetDefaultNetmask();
         * DESCRIPTION
         *       Returns the address's default netmask in dotted decimal format..
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       std::string
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
         *       std::cout << "Default netmask is: " << _address->GetDefaultNetmask() << std::endl;
         *       // prints "Default netmask is: 255.0.0.0" 	
 	 *
         *   	return 0;
         * }
         * SOURCE
         */
std::string libipvx::IP4Address::GetDefaultNetmask() 
{
	if ( this->GetClass() == IPV4_ADDRESS_CLASS_A) {
		return IPV4_CLASS_A_DEFAULT_SUBNET_MASK;
	}
	else if ( this->GetClass() == IPV4_ADDRESS_CLASS_B ) {
		return IPV4_CLASS_B_DEFAULT_SUBNET_MASK;
	}
	else if ( this->GetClass() == IPV4_ADDRESS_CLASS_C ) {
		return IPV4_CLASS_C_DEFAULT_SUBNET_MASK;
	}
}
/*******/

/****m* IP4Address/GetClass();
         * NAME
         *       GetClass();
         * DESCRIPTION
         *       Returns the class of the address.
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       char
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << "Address class is: " << address->GetClass() << std::endl;
         *       // prints "Address class is: A" 	
 	 *
         *   	return 0;
         * }
         * SOURCE
         */
char libipvx::IP4Address::GetClass() 
{	
	// Check the first octet for the whereabouts of the first zero bit in the first octet as this is indicative the class.
		
	if ( this->GetFirstOctetBitset()[0] == false ) 
	{
		// if first bit is zero, then address is class A.
		return IPV4_ADDRESS_CLASS_A;		
	}
	else if ( this->GetFirstOctetBitset()[1] == false ) 
	{
		// if second bit is zero, then address is class B.
		return IPV4_ADDRESS_CLASS_B;		
	}
	else if ( this->GetFirstOctetBitset()[2] == false ) 
	{
		// if third bit is zero, then address is class C.
		return IPV4_ADDRESS_CLASS_C;		
	}
	else if ( this->GetFirstOctetBitset()[3] == false ) 
	{
		// if fourth bit is zero, then address is class D.
		return IPV4_ADDRESS_CLASS_D;		
	}	
	else 
	{
		// if fifth bit is zero, then address is class E.
		return  IPV4_ADDRESS_CLASS_E;		
	}
}
/*******/

/****m* IP4Address/GetNetmaskAddressString();
         * NAME
         *       GetNetmaskAddressString();
         * DESCRIPTION
         *       Returns a string of the netmask in dotted decimal format.
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       std::string
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << "Netmask is: " << address->GetNetmaskAddressString() << std::endl;
         *       // prints "Netmask is: 255.0.0.0" 	
 	 *
         *   	return 0;
         * }
         * SOURCE
         */
std::string libipvx::IP4Address::GetNetmaskAddressString() 
{
	return this->netmask;
}
/*******/

/****m* IP4Address/GetInverseNetmaskString();
         * NAME
         *       GetInverseNetmaskString();
         * DESCRIPTION
         *       Returns a string of the netmask inverse in dotted decimal format.
         * PARAMETERS 
         *       None.        
         * RETURN VALUE
         *       std::string
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *       std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *       std::cout << "Netmask inverse is: " << address->GetInverseNetmaskString() << std::endl;
         *       // prints "Netmask inverse is: 0.255.255.255" 	
 	 *
         *   	return 0;
         * }
         * SOURCE
         */
std::string libipvx::IP4Address::GetInverseNetmaskString()
{
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetInverseNetmaskBitset();
	return this->GetAddressStringFromBitset(_bitset);
}
/*******/

/****m* IP4Address/GetInverseNetmaskBitset();
         * NAME
         *       GetInverseNetmaskBitset();
         * DESCRIPTION
         *       Returns the bitset of the netmask inverse.
         * PARAMETERS 
         *       None        
         * RETURN VALUE
         *       std::bitset<IPV4_ADDRESS_LENGTH> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
         *      std::bitset<IPV4_ADDRESS_LENGTH> _bitset = address->GetInverseNetmaskString();
         *   	return 0;
         * }
         * SOURCE
         */
std::bitset<IPV4_ADDRESS_LENGTH> libipvx::IP4Address::GetInverseNetmaskBitset() 
{
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = ::ConvertIPv4StringToSTLBitset(this->GetNetmaskAddressString());
	_bitset.flip();	
	return _bitset;
}
/*******/

/****m* IP4Address/GetFirstAddressInRange();
         * NAME
         *       GetFirstAddressInRange();
         * DESCRIPTION
         *       Returns a unique_ptr to an IP4Address object representing the first address of the range. 
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::unique_ptr<libipvx::IP4Address> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	 *	address->netmask = "255.255.128.0";
         *      std::unique_ptr<IP4Address> firstAddress = address->GetFirstAddressInRange();
	 *	std::cout << "First address in range is: " << firstAddress->GetAddressString() << std::endl;
	 *	// prints "First address in range is: 10.1.0.1"
         *   	return 0;
         * }
         * SOURCE
         */
std::unique_ptr<libipvx::IP4Address> libipvx::IP4Address::GetFirstAddressInRange() {
	
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
/*******/

/****m* IP4Address/GetLastAddressInRange();
         * NAME
         *       GetLastAddressInRange();
         * DESCRIPTION
         *       Returns a unique_ptr to an IP4Address object representing the last address of the range. 
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       std::unique_ptr<libipvx::IP4Address> 
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));
	 *	address->netmask = "255.255.128.0";
         *      std::unique_ptr<IP4Address> lastAddress = address->GetFirstAddressInRange();
	 *	std::cout << "Last address in range is: " << lastAddress->GetAddressString() << std::endl;
	 *	// prints "Last address in range is: 10.1.127.254"
         *   	return 0;
         * }
         * SOURCE
         */
std::unique_ptr<libipvx::IP4Address> libipvx::IP4Address::GetLastAddressInRange() 
{
	// Get the bitset of the broadcast address.
	std::bitset<IPV4_ADDRESS_LENGTH> _bitset = this->GetBroadcastAddressBitset();

	// Toggle the last bit off.
	_bitset.set(IPV4_ADDRESS_LENGTH -1, false);

	// Get the dotted decimal address string.
	std::string _addressString = this->GetAddressStringFromBitset(_bitset);

	std::unique_ptr<IP4Address> _addr(new IP4Address(_addressString));
	_addr->netmask = this ->GetNetmaskAddressString();
	return _addr;
}
/*******/

/****m* IP4Address/GetNetmaskHostPortionBitLength();
         * NAME
         *       GetNetmaskHostPortionBitLength();
         * DESCRIPTION
         *       Returns the bit length of the host portion of netmask.
         * PARAMETERS 
         *       None.
         * RETURN VALUE
         *       int
         * USAGE 
         * #include "libipvx.h"
         * using namespace libipvx;
         * 
         * int main ()
         * {
         *      std::unique_ptr<IP4Address> _address(new IP4Address("10.1.5.2"));
	 *	_address->netmask = "255.255.128.0";
	 *	std::cout << "Bit length of host portion of netmask is: " << _address->GetNetmaskHostPortionBitLength() << std::endl;
	 *	// prints "Bit length of host portion of netmask is: 9"
         *   	return 0;
         * }
         * SOURCE
         */
int libipvx::IP4Address::GetNetmaskHostPortionBitLength() 
{
	// Get the natural netmask.
	std::string _netmask = this->GetDefaultNetmask();

	// Get its bitset equivalent.
	std::bitset<IPV4_ADDRESS_LENGTH> _netmaskBitset = ::ConvertIPv4StringToSTLBitset(_netmask);
		
	// Minus the length of the current netmask\'s bitset from the natural netmask\'s bitset.	
	int hostBitsLen = this->GetNetmaskBitLength() - _netmaskBitset.count();
	return hostBitsLen;
}
/*******/
