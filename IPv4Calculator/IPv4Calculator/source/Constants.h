#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <bitset>
#include <stdint.h>


const uint8_t OCTET_SIZE = 8;
const uint8_t AMOUNT_OF_DOTS = 3;
const uint8_t AMOUNT_OF_OCTETS = 4;
const uint8_t ADDITIONAL_REQUIRED_HOSTS = 2;

const uint8_t OCTET_MASK_BITSHIFTS[4] = { 24, 16, 8, 0 };

const std::bitset<32> OCTET_MASKS[4] = {
	static_cast<std::uint32_t>(255 << OCTET_MASK_BITSHIFTS[0]),
	static_cast<std::uint32_t>(255 << OCTET_MASK_BITSHIFTS[1]),
	static_cast<std::uint32_t>(255 << OCTET_MASK_BITSHIFTS[2]),
	static_cast<std::uint32_t>(255 << OCTET_MASK_BITSHIFTS[3])
};


#endif // CONSTANTS_H
