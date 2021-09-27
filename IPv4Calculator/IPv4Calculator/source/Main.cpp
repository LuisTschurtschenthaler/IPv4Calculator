#include "pch.h"
#include "IPCalculator.h"
#include "Constants.h"
#include "Input.h"


int main() {
	std::string ip = Input::getIP();
	uint8_t cidr = Input::getCIDR();
	
	IPCalculator::setIPNetwork(new IPNetwork(ip, cidr));

	do {
		std::string subnetName = Input::getSubnetName();
		uint64_t subnetSize = Input::getSubnetSize();

		IPCalculator::addSubnet(subnetName, subnetSize);
	} while(Input::shouldContinue());

	IPCalculator::calculate();


	std::cin.ignore();
	IPCalculator::shutdown();

	return 0;
}
