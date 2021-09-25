#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <regex>
#include <bitset>

#include "Constants.h"


const std::regex _regexIPv4 = std::regex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
const std::regex _regexMask = std::regex("^([8-9]|1[0-9]|2[0-9]|30)$");
const std::regex _regexSubnetSize = std::regex("^[0-9]{1,4}$");


std::string getIP() {
	std::string ip = "";
	
	do {
		std::getline(std::cin, ip);
	} while(!std::regex_match(ip, _regexIPv4));

	return ip;
}

uint8_t getCIDR() {
	std::string cidr = "";
	
	do {
		std::getline(std::cin, cidr);
	} while(!std::regex_match(cidr, _regexMask));

	return std::atoi(cidr.c_str());
}

std::string getNextSubnetSize() {
	std::string size = "";

	do {
		std::getline(std::cin, size);
	} while(!std::regex_match(size, _regexSubnetSize));

	return size;
}



class IPNetwork {

private:
	using Bits = std::bitset<32>;


private:
	uint8_t _cidr = 0;
	Bits _address, _subnetmask, _wildcard;
	Bits _networkID, _broadcast;
	Bits _firstHost, _lastHost;
	uint32_t _availableHosts;


public:
	IPNetwork(const std::string& address, const uint8_t& cidr)
		: _cidr(cidr) {

		_address = _stringToBits(address);
		_subnetmask = ~(0xFFFFFFFF >> cidr);

		_wildcard = (~_subnetmask);
		_networkID = (_address & _subnetmask);
		_broadcast = (_networkID | _wildcard);

		_firstHost = (_networkID.to_ulong() + 1);
		_lastHost = (_broadcast.to_ulong() - 1);

		_availableHosts = (std::pow(2, (32 - _cidr)) - 2);

		std::cout << _address << std::endl;
		std::cout << _subnetmask << std::endl;

		std::cout << "Entered IP: \t\t" << _bitsToString(_address) << " " << std::to_string( _cidr )<< std::endl;
		std::cout << std::endl;
		std::cout << "Network ID: \t\t" << _bitsToString(_networkID) << std::endl;
		std::cout << "Subnetmask/Wildcard: \t" << _bitsToString(_subnetmask) << " / " << _bitsToString(_wildcard) << std::endl;
		std::cout << std::endl;
		std::cout << "Range: \t\t\t" << _bitsToString(_firstHost) << " - " << _bitsToString(_lastHost) << std::endl;
		std::cout << "Broadcast: \t\t" << _bitsToString(_broadcast) << std::endl;
		std::cout << "Available hosts: \t" << _availableHosts << std::endl;
	}


private:
	Bits _stringToBits(const std::string& str) {
		std::stringstream ss(str);

		int i = 0;
		std::string temp;

		uint8_t octets[4];
		while(std::getline(ss, temp, '.'))
			octets[i++] = std::atoi(temp.c_str());

		Bits bits;
		for(size_t i = 0; i < AMOUNT_OF_OCTETS; i++)
			bits |= std::bitset<32>(octets[i] << OCTET_MASK_BITSHIFTS[i]) & OCTET_MASKS[i];

		return bits;
	}

	std::string _bitsToString(const Bits& bits) {
		std::string result = "";

		for(int i = 0; i <= AMOUNT_OF_DOTS; i++) {
			result += std::to_string(((bits & OCTET_MASKS[i]) >> OCTET_MASK_BITSHIFTS[i]).to_ulong());
			if(i != AMOUNT_OF_DOTS) result += ".";
		}

		return result;
	}

};


int main() {
	std::string ip = "192.168.2.234"; // getIP();
	uint8_t cidr = 2; // getCIDR();
	
	IPNetwork network(ip, cidr);


	std::cin.ignore();
	return 0;
}
