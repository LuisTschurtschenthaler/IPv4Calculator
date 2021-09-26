#include <iostream>

#include "IPNetwork.h"
#include "Constants.h"

#include "IPCalculator.h"


std::string getIP() {
	std::string ip = "";
	
	do {
		std::getline(std::cin, ip);
	} while(!std::regex_match(ip, REGEX_IP_V_4));

	return ip;
}

uint8_t getCIDR() {
	std::string cidr = "";
	
	do {
		std::getline(std::cin, cidr);
	} while(!std::regex_match(cidr, REGEX_CIDR));

	return std::atoi(cidr.c_str());
}

std::string getNextSubnetSize() {
	std::string size = "";

	do {
		std::getline(std::cin, size);
	} while(!std::regex_match(size, REGEX_SUBNET_SIZE));

	return size;
}


int main() {
	std::string ip = "192.168.2.234"; // getIP();
	uint8_t cidr = 24; // getCIDR();
	
	IPCalculator::setIPNetwork(new IPNetwork(ip, cidr));

	IPCalculator::addSubnet("Brixen", 185);
	IPCalculator::addSubnet("Bozen", 12);
	IPCalculator::addSubnet("Bruneck", 31);
	IPCalculator::addSubnet("Innichen", 205);

	IPCalculator::calculate();

	std::cin.ignore();
	return 0;
}
