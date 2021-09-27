#include "pch.h"
#include "IPCalculator.h"


IPNetwork* IPCalculator::_network;
std::vector<Subnet> IPCalculator::_subnets;


void IPCalculator::addSubnet(const std::string& name, const uint64_t& amountOfHosts) {
	for(const auto& subnet : _subnets) {
		if(subnet.first == name) {
			std::cout << "Subnet '" << name << "' already exists!" << std::endl;
			return;
		}
	}

	_subnets.push_back(std::make_pair(name, amountOfHosts));
}

void IPCalculator::calculate() {
	std::sort(_subnets.begin(), _subnets.end(), [](const auto& a, const auto& b) {
		return (a.second > b.second);
	});

	std::vector<IPNetwork> networks;
	_network->printDetails();
	std::cout << "Class information: \t" << _network->getClassInformation() << std::endl;
	std::cout << std::endl;

	for(const auto& subnet : _subnets) {
		uint8_t subnetCIDR = -(log10(subnet.second + 2) / log10(2)) + 32;
		
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

void IPCalculator::shutdown() {
	for(auto& subnet : _subnets)
		delete &subnet;

	delete _network;
}
