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

#include "ipvxlib.h"

// This program smoke tests the LibIPvX library.
int main(int argc, char** argv)
{
	std::cout << "        _____ ______  _____  _____  _    _ _     _" << std::endl; 
	std::cout << " |        |   |_____]   |   |_____]  \\  /   \\___/ " << std::endl; 
	std::cout << " |_____ __|__ |_____] __|__ |         \\/   _/   \\_" << std::endl; 
 

	std::cout << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << "Starting LIBIPvX smoke tests." << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << std::endl;

	std::unique_ptr<IP4Address> address(new IP4Address("10.1.5.2"));

	// Check that the default netmask has been assigned - this value is automatically
	// assigned by the constructor to address->netmask and is overwritten when you specify
	// a subnet mask manually.

	assert( address->GetNetmaskAddressString() == IPV4_CLASS_A_DEFAULT_SUBNET_MASK);

	// As we haven't specified one, it's the default netmask of the address's class.
	assert( address->GetNetmaskAddressString() == address->GetDefaultNetmask());
	std::cout << "Default subnet mask: " << address->GetDefaultNetmask() << std::endl;
	std::cout << std::endl;
	
	// We're using a default netmask, therefore we're not subnetting.
	assert( !address->IsSubnetted() );
	if ( !address->IsSubnetted() ) {
		std::cout << "IP Address: " << address->GetAddressString() << " with mask " << address->netmask << " is not subnetted." << std::endl;
	}
	std::cout << std::endl;
	
	// Now set a subnet netmask - this replaces the default subnet mask.
	address->netmask = "255.255.128.0";
	std::cout << "Applying mask " << address->netmask << std::endl;
	assert(address->GetNetmaskAddressString() == "255.255.128.0");
	std::cout << std::endl;

	// We're not using a default netmask, therefore we're subnetting.
	assert( address->IsSubnetted() );
	if ( address->IsSubnetted() ) {
		std::cout << "IP Address: " << address->GetAddressString() << " with mask " << address->netmask << " is subnetted." << std::endl;
	}
	std::cout << std::endl;

	// Get inverse netmask.
	assert( address->GetInverseNetmaskString() == "0.0.127.255");
	std::cout << "Get Inverse netmask string: " << address->GetInverseNetmaskString() << std::endl;
	std::cout << std::endl;

	// Display the binary of the IP's address space.
	std::cout << "Address binary: " << address->GetAddressBitset() << std::endl;
	std::cout << std::endl;
	
	// Display the subnet address.
	assert( address->GetSubnetAddress() == "10.1.0.0" );
	std::cout << "Subnet address: " <<  address->GetSubnetAddress() << std::endl;
	std::cout << std::endl;
	
	// Display the broadcast address.
	assert( address->GetBroadcastAddressString() == "10.1.127.255" );
	std::cout << "Broadcast address: " << address->GetBroadcastAddressString() << std::endl;
	std::cout << std::endl;
	
	// Is this address a broadcast address, no.
	assert( !address->IsBroadcastAddress() );
	if ( !address->IsBroadcastAddress() ) {
		std::cout << address->GetAddressString() << " is not a broadcast address." << std::endl;
	}
	std::cout << std::endl;
	
	// Is this address a subnet address, no.
	assert( !address->IsSubnetAddress() );
	if ( !address->IsSubnetAddress() ) {
			std::cout << address->GetAddressString() << " is not a subnet address." << std::endl;
	}
	std::cout << std::endl;
	
	// Get the first address available in the current range.
	std::unique_ptr<IP4Address> _firstAddr = address->GetFirstAddressInRange();
	assert(_firstAddr->GetAddressString() == "10.1.0.1");
	std::cout << "First address in current range: " <<_firstAddr->GetAddressString() << std::endl;
	std::cout << std::endl;

	// Get the last address available in the current range.
	std::unique_ptr<IP4Address> _lastAddr = address->GetLastAddressInRange();
	assert(_lastAddr->GetAddressString() == "10.1.127.254");
	std::cout << "Last address in current range: " <<_lastAddr->GetAddressString() << std::endl;
	std::cout << std::endl;

	// Get the address as formatted decimal string.
	assert( address->GetAddressString() == "10.1.5.2" );
	std::cout << "IP: " << address->GetAddressString() << std::endl;
	std::cout << std::endl;
	
	// Get the netmask in CIDR notation.
	assert( address->GetNetmaskBitLength() == 17 );
	std::cout << "Netmask in CIDR notation: " << address->GetNetmaskBitLength() << std::endl;
	std::cout << std::endl;
	
	// Get each Octet's binary using an array.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ ) {
		std::cout << "Fetching Octet's binary in array at index " << i << ": " << address->GetOctetBinaryByIndex(i) << std::endl;
	}
	std::cout << std::endl;
	
	// Get each Octet's decimal using an array.
	for ( size_t i = 0; i < IPV4_OCTET_COUNT; i++ ) {
		std::cout << "Fetching Octet's decimal in array at index " << i << ": " << address->GetOctetDecimalByIndex(i) << std::endl;
	}
	std::cout << std::endl;
	
	// Get the first Octet in binary.
	std::cout << "First octet's binary: " << address->GetFirstOctetBitset() << std::endl;
	std::cout << std::endl;
	
	// Get the first Octet in decimal.
	assert( address->GetFirstOctetDecimal() == 10);
	std::cout << "First octet's decimal: " << address->GetFirstOctetDecimal() << std::endl;
	std::cout << std::endl;
	
	// Get the second Octet in binary.
	std::cout << "Second octet's binary: " << address->GetSecondOctetBitset() << std::endl;
	std::cout << std::endl;
	
	// Get the second Octet in decimal.
	assert( address->GetSecondOctetDecimal() == 1);
	std::cout << "Second octet's decimal: " << address->GetSecondOctetDecimal() << std::endl;
	std::cout << std::endl;
	
	// Get the third Octet in binary.
	std::cout << "Third octet's binary: " << address->GetThirdOctetBitset() << std::endl;
	std::cout << std::endl;
	
	// Get the third Octet in decimal.
	assert( address->GetThirdOctetDecimal() == 5);
	std::cout << "Third octet's decimal: " << address->GetThirdOctetDecimal() << std::endl;
	std::cout << std::endl;
	
	// Get the fourth Octet in binary.	
	std::cout << "Fourth octet's binary: " << address->GetFourthOctetBitset() << std::endl;
	std::cout << std::endl;

	// Get the fourth Octet in decimal.
	assert( address->GetFourthOctetDecimal() == 2);
	std::cout << "Fourth octet's decimal: " << address->GetFourthOctetDecimal() << std::endl;
	std::cout << std::endl;

	// Get the IP Address's class.
	assert( address->GetClass() == IPV4_ADDRESS_CLASS_A );
	std::cout << "Address class is: " << address->GetClass() << std::endl;
	std::cout << std::endl;

	// Get bit length of host portion of the netmask.
	assert( address->GetNetmaskHostPortionBitLength() == 15 );
	std::cout << "Bit length of host portion of netmask is: " << address->GetNetmaskHostPortionBitLength()  << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***************************" << std::endl;
	std::cout << "All tests were successful." << std::endl;
	std::cout << "***************************" << std::endl;


	return 0;
}


