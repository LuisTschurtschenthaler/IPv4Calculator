#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <bitset>
#include <stdint.h>


const std::string REGEX_IP_V4 = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";
const std::string REGEX_CIDR = "^([8-9]|1[0-9]|2[0-9]|30)$";
const std::string REGEX_SUBNET_SIZE = "^[0-9]{1,4}$";
const std::string REGEX_YES_NO = "^[ynYN]$";


const uint8_t OCTET_SIZE = 8;
const uint8_t AMOUNT_OF_DOTS = 3;
const uint8_t AMOUNT_OF_OCTETS = 4;
const uint8_t ADDITIONAL_REQUIRED_HOSTS = 2;

const uint8_t OCTET_MASK_BITSHIFTS[4] = { 24, 16, 8, 0 };

const std::bitset<32> OCTET_MASKS[4] = {
	(255 << OCTET_MASK_BITSHIFTS[0]),
	(255 << OCTET_MASK_BITSHIFTS[1]),
	(255 << OCTET_MASK_BITSHIFTS[2]),
	(255 << OCTET_MASK_BITSHIFTS[3])
};


#endif // CONSTANTS_H
