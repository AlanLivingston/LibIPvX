// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <assert.h>
#include <memory>
#include <algorithm>
#include <sstream>
#include <bitset>

// TODO: reference additional headers your program requires here

#define IPV4_ADDRESS_LENGTH 32
#define IPV4_SUBNET_LENGTH 32
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
#define IPV4_ADDRESS_CLASS_D 'D'
#define IPV4_ADDRESS_CLASS_E 'E'
#define IPV4_CLASS_A_DEFAULT_SUBNET_MASK "255.0.0.0"
#define IPV4_CLASS_B_DEFAULT_SUBNET_MASK "255.255.0.0"
#define IPV4_CLASS_C_DEFAULT_SUBNET_MASK "255.255.255.0"
#define IPV4_CLASS_A_DEFAULT_SUBNET_LENGTH 8
#define IPV4_CLASS_B_DEFAULT_SUBNET_LENGTH 16
#define IPV4_CLASS_C_DEFAULT_SUBNET_LENGTH 24

#define IPV6_ADDRESS_LENGTH 128
#define IPV6_HECTET_SIZE 16
#define IPV6_HECTET_COUNT 8

#endif
