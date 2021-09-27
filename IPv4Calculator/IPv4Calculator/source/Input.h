#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <stdint.h>


class Input {

public:
	static std::string getIP();
	static uint8_t getCIDR();

	static std::string getSubnetName();
	static uint64_t getSubnetSize();
	
	static bool shouldContinue();

};

#endif // INPUT_H
