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


#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <assert.h>
#include <memory>

#include "ipvxlib.h"

// This program smoke tests LibIPvX. 

int _tmain(int argc, _TCHAR* argv[])
{
	std::auto_ptr<IP4Address> address(new IP4Address("10.1.5.2"));

	// Check that the default subnet mask has been assigned.
	assert( address->GetDefaultSubnetMask() == "255.255.255.0");
	std::cout << "Default subnet mask: " << address->GetDefaultSubnetMask() << std::endl;

	// Now set a subnet netmask - this replaces the default subnet mask.
	address->netmask = "255.255.128.0";

	// Display the binary of the IP's address space.
	std::cout << "Address binary: " << address->GetAddressBinary() << std::endl;

	// Display the subnet address.
	assert( address->GetSubnetAddress() == "10.1.0.0" );
	std::cout << "Subnet address: " <<  address->GetSubnetAddress() << std::endl;

	// Display the broadcast address.
	assert( address->GetBroadcastAddress() == "10.1.127.255" );
	std::cout << "Broadcast address: " << address->GetBroadcastAddress() << std::endl;

	assert( !address->IsBroadcastAddress() );
	if ( !address->IsBroadcastAddress() ) {
		std::cout << address->GetAddressString() << " is not a broadcast address." << std::endl;
	}

	assert( !address->IsSubnetAddress() );
	if ( !address->IsSubnetAddress() ) {
			std::cout << address->GetAddressString() << " is not a subnet address." << std::endl;
	}

	// Get the address as formatted decimal string.
	assert( address->GetAddressString() == "10.1.5.2" );
	std::cout << "IP: " << address->GetAddressString() << std::endl;

	// Get the netmask in CIDR notation.
	assert( address->GetNetmaskBitLength() == 17 );
	std::cout << "Netmask in CIDR notation: " << address->GetNetmaskBitLength() << std::endl;

	// Get each Octet's binary using an array.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ ) {
		std::cout << "Fetching Octet's binary in array at index " << i << ": " << address->GetOctetBinaryByIndex(i) << std::endl;
	}

	// Get each Octet's decimal using an array.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ ) {
		std::cout << "Fetching Octet's decimal in array at index " << i << ": " << address->GetOctetDecimalByIndex(i) << std::endl;
	}

	// Get the first Octet in binary.
	std::cout << "First octet's binary: " << address->GetFirstOctetBinary() << std::endl;

	// Get the first Octet in decimal.
	assert( address->GetFirstOctetDecimal() == 10);
	std::cout << "First octet's decimal: " << address->GetFirstOctetDecimal() << std::endl;

	// Get the second Octet in binary.
	std::cout << "Second octet's binary: " << address->GetSecondOctetBinary() << std::endl;

	// Get the second Octet in decimal.
	assert( address->GetSecondOctetDecimal() == 1);
	std::cout << "Second octet's decimal: " << address->GetSecondOctetDecimal() << std::endl;

	// Get the third Octet in binary.
	std::cout << "Third octet's binary: " << address->GetThirdOctetBinary() << std::endl;

	// Get the third Octet in decimal.
	assert( address->GetThirdOctetDecimal() == 5);
	std::cout << "Third octet's decimal: " << address->GetThirdOctetDecimal() << std::endl;

	// Get the fourth Octet in binary.	
	std::cout << "Fourth octet's binary: " << address->GetFourthOctetBinary() << std::endl;

	// Get the fourth Octet in decimal.
	assert( address->GetFourthOctetDecimal() == 2);
	std::cout << "Fourth octet's decimal: " << address->GetFourthOctetDecimal() << std::endl;

	// Get the IP Address's class.
	assert( address->GetClass() == IPV4_ADDRESS_CLASS_A );
	std::cout << "Address's class is: " << address->GetClass() << std::endl;

	while (address->HasNext()) {		
		std::cout << address->GetAddressString() << std::endl;	
		address = std::move(address->GetProceedingIP4AddressInRange());		
	}
	 
	return 0;
}


