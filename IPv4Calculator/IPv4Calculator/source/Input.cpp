#include "pch.h"
#include "Input.h"
#include "Constants.h"


std::string Input::getIP() {
	std::string ip = _getInput("IPv4-Address: ", REGEX_IP_V4);
	return ip;
}

uint8_t Input::getCIDR() {
	std::string cidr = _getInput("CIDR (8-30): ", REGEX_CIDR);
	return std::atoi(cidr.c_str());
}

std::string Input::getSubnetName() {
	std::string name = "";

	do {
		_clearConsole();
		std::cout << "Subnetname: ";
		std::getline(std::cin, name);
	} while(name == "");

	return name;
}

uint64_t Input::getSubnetSize() {
	std::string subnetSize = _getInput("Subnet size: ", REGEX_SUBNET_SIZE);
	return std::atoi(subnetSize.c_str());
}

bool Input::shouldContinue() {
	std::string input = _getInput("Add anoter subnet? (y/n): ", REGEX_YES_NO);
	return (input == "y" || input == "Y");
}


std::string Input::_getInput(const std::string& message, const std::string& regexStr) {
	std::regex regex = std::regex(regexStr);
	std::string input = "";

	do {
		_clearConsole();
		std::cout << message;
		std::getline(std::cin, input);
	} while(!std::regex_match(input, regex));

	return input;
}

void Input::_clearConsole() {
	#if defined(_WIN32)
		system("cls");
	#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
	#elif defined(__APPLE__)
		system("clear");
	#endif
}
