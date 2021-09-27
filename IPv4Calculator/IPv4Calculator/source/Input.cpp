#include "pch.h"
#include "Input.h"
#include "Constants.h"


std::string Input::getIP() {
	std::string ip = "";

	do {
		std::getline(std::cin, ip);
	} while(!std::regex_match(ip, REGEX_IP_V_4));

	return ip;
}

uint8_t Input::getCIDR() {
	std::string cidr = "";

	do {
		std::getline(std::cin, cidr);
	} while(!std::regex_match(cidr, REGEX_CIDR));

	return std::atoi(cidr.c_str());
}

std::string Input::getSubnetName() {
	std::string name = "";

	do {
		std::getline(std::cin, name);
	} while(name == "");

	return name;
}

uint64_t Input::getSubnetSize() {
	std::string size = "";

	do {
		std::getline(std::cin, size);
	} while(!std::regex_match(size, REGEX_SUBNET_SIZE));

	return std::atoi(size.c_str());
}

bool Input::shouldContinue() {
	std::string input = "";

	do {
		std::cout << "Add anoter subnet? [yYnN]" << std::endl;
		std::getline(std::cin, input);

	} while(!std::regex_match(input, REGEX_YES_NO));

	return (input == "y" || input == "Y");
}
