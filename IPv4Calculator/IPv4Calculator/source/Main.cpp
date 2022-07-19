#include "pch.h"
#include "IPCalculator.h"
#include "Constants.h"
#include "Input.h"


int main() {
	auto ip = Input::getIP();
	auto cidr = Input::getCIDR();
	
	IPCalculator::setIPNetwork({ ip, cidr });

	do {
		auto subnetName = Input::getSubnetName();
		auto subnetSize = Input::getSubnetSize();
		IPCalculator::addSubnet(subnetName, subnetSize);
	} while(Input::shouldContinue());

	IPCalculator::calculate();

	std::cin.ignore();
	return 0;
}
