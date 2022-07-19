#ifndef IP_CALCULATOR_H
#define IP_CALCULATOR_H

#include <map>
#include <vector>
#include <functional>

#include "IPNetwork.h"


using Subnet = std::pair<std::string, uint64_t>;


class IPCalculator {

private:
	static IPNetwork _network;
	static std::vector<Subnet> _subnets;


public:
	static void addSubnet(const std::string& name, const uint64_t& amountOfHosts);
	static void calculate();

	static void setIPNetwork(const IPNetwork& network) { _network = network; }

};

#endif // IP_CALCULATOR_H
