#ifndef IP_NETWORK_H
#define IP_NETWORK_H

#include <string>
#include <bitset>
#include <stdint.h>


using Bits = std::bitset<32>;


class IPNetwork {

	friend class IPCalculator;

private:
	std::string _name = "";
	uint8_t _cidr = 0;
	Bits _address, _subnetmask, _wildcard;
	Bits _networkID, _broadcast;
	Bits _firstHost, _lastHost;
	uint64_t _availableHosts;


public:
	IPNetwork(const std::string& address, const uint8_t& cidr);
	IPNetwork(const std::string& name, const std::string& address, const uint8_t& cidr);

	std::string getNetworkID();
	std::string getNextSubnetIP();

	std::string getClassInformation();
	void printDetails();

private:
	static Bits _stringToBits(const std::string& str);
	static std::string _bitsToString(const Bits& bits);

};

#endif // IP_NETWORK_H
