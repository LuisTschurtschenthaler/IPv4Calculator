#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <stdint.h>
#include <regex>


class Input {

	friend class IPCalculator;

public:
	static std::string getIP();
	static uint8_t getCIDR();

	static std::string getSubnetName();
	static uint64_t getSubnetSize();
	
	static bool shouldContinue();

private:
	static std::string _getInput(const std::string& message, const std::string& regexStr);
	static void _clearConsole();

};

#endif // INPUT_H
