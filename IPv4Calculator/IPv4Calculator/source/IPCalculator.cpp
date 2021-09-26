#include "IPCalculator.h"
#include <iostream>
#include <algorithm>


IPNetwork* IPCalculator::_network;
std::vector<Subnet> IPCalculator::_subnets;


void IPCalculator::addSubnet(const std::string& name, const uint64_t& size) {
	for(const auto& subnet : _subnets) {
		if(subnet.first == name) {
			std::cout << "Subnet '" << name << "' already exists!" << std::endl;
			return;
		}
	}

	_subnets.push_back(std::make_pair(name, size));
}

void IPCalculator::calculate() {
	std::sort(_subnets.begin(), _subnets.end(), [](const auto& a, const auto& b) {
		return (a.second > b.second);
	});

	std::vector<IPNetwork> networks;
	_network->printDetails();
	std::cout << std::endl;

	for(const auto& subnet : _subnets) {
		uint8_t subnetCIDR = -(log(subnet.second + 2) / log(2)) + 32;

		std::string address = (networks.size() == 0) 
			? _network->getNetworkID()
			: networks[networks.size() - 1].getNextSubnetIP();

		IPNetwork network({ subnet.first, address, subnetCIDR });
		if(network._address.to_ulong() >= _network->_broadcast.to_ulong()) {
			std::cout << "NOT ENOUGH SPACE!" << std::endl;
			return;
		}

		network.printDetails();
		std::cout << std::endl;

		networks.push_back(network);
	}
}
