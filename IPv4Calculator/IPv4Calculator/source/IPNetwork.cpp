#include "IPNetwork.h"
#include "Constants.h"
#include <iostream>
#include <sstream>


IPNetwork::IPNetwork(const std::string& address, const uint8_t& cidr)
	: _cidr(cidr) {

	_address = _stringToBits(address);
	_subnetmask = ~(0xFFFFFFFF >> cidr);

	_wildcard = (~_subnetmask);
	_networkID = (_address & _subnetmask);
	_broadcast = (_networkID | _wildcard);

	_firstHost = (_networkID.to_ulong() + 1);
	_lastHost = (_broadcast.to_ulong() - 1);

	_availableHosts = (std::pow(2, (32 - _cidr)) - 2);
}

IPNetwork::IPNetwork(const std::string& name, const std::string& address, const uint8_t& cidr)
	: _name(name), _cidr(cidr) {

	_address = _stringToBits(address);
	_subnetmask = ~(0xFFFFFFFF >> cidr);

	_wildcard = (~_subnetmask);
	_networkID = (_address & _subnetmask);
	_broadcast = (_networkID | _wildcard);

	_firstHost = (_networkID.to_ulong() + 1);
	_lastHost = (_broadcast.to_ulong() - 1);

	_availableHosts = (std::pow(2, (32 - _cidr)) - 2);
}


std::string IPNetwork::getNetworkID() {
	return _bitsToString(_networkID);
}

std::string IPNetwork::getNextSubnetIP() {
	return _bitsToString(_broadcast.to_ulong() + 1);
}

std::string IPNetwork::getClassInformation() {
	auto ipToIntVector = [](const std::string& address) {
		std::stringstream ss(address);
		std::vector<int> ip;

		std::string temp;
		while(std::getline(ss, temp, '.'))
			ip.push_back(std::atoi(temp.c_str()));

		return ip;
	};

	std::vector<int> ip = ipToIntVector(getNetworkID());

	if(ip[0] == 10)
		return "'A', private block";

	else if(ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31)
		return "'B', private block";

	else if(ip[0] == 192 && ip[1] == 168)
		return "'C', private block";

	else if(ip[0] == 127)
		return "Reserved block, System Loopback Address";

	else if(ip[0] >= 0 && ip[0] < 127)
		return "A";

	else if(ip[0] > 127 && ip[0] < 192)
		return "B";

	else if(ip[0] > 191 && ip[0] < 224)
		return "C";

	else if(ip[0] > 223 && ip[0] < 240)
		return "D, Multicast IP-Address block";

	else if(ip[0] > 239 && ip[0] <= 255)
		return "E, Multicast IP-Address block";

	else return "Not in range";
}

void IPNetwork::printDetails() {
	if(_name != "")
		std::cout << "Network name: \t\t" << _name << std::endl;
	
	std::cout << "Network ID: \t\t" << _bitsToString(_networkID) << std::endl;
	std::cout << "Subnetmask/Wildcard: \t" << _bitsToString(_subnetmask) << " / " << _bitsToString(_wildcard) << std::endl;
	std::cout << "Range: \t\t\t" << _bitsToString(_firstHost) << " - " << _bitsToString(_lastHost) << std::endl;
	std::cout << "Broadcast: \t\t" << _bitsToString(_broadcast) << std::endl;
	std::cout << "Available hosts: \t" << _availableHosts << std::endl;
}


Bits IPNetwork::_stringToBits(const std::string& str) {
	std::stringstream ss(str);

	uint8_t i = 0;
	std::string temp;

	uint8_t octets[4];
	while(std::getline(ss, temp, '.'))
		octets[i++] = std::atoi(temp.c_str());

	Bits bits;
	for(size_t i = 0; i < AMOUNT_OF_OCTETS; i++)
		bits |= std::bitset<32>(octets[i] << OCTET_MASK_BITSHIFTS[i]) & OCTET_MASKS[i];

	return bits;
}

std::string IPNetwork::_bitsToString(const Bits& bits) {
	std::string result = "";

	for(uint8_t i = 0; i <= AMOUNT_OF_DOTS; i++) {
		result += std::to_string(((bits & OCTET_MASKS[i]) >> OCTET_MASK_BITSHIFTS[i]).to_ulong());

		if(i != AMOUNT_OF_DOTS)
			result += ".";
	}

	return result;
}
