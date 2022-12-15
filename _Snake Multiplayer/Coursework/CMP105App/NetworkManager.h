#pragma once
#include "SFML/Network.hpp"
#include "GhostManager.h"

enum class DataType {
	PLAYER, PILL, TEXT, EVENT
};
class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	sf::Packet udpSendPacket();
	sf::Packet udpRecievePacket();
	sf::Packet tcpSendPacket();
	sf::Packet tcpRecievePacket();

	void setPort(unsigned short port);
	unsigned short getPort();

	void setServerIp(std::string ip);
	sf::IpAddress getServerIp();

	sf::IpAddress getLocalIp();

private:


	sf::IpAddress _localIp, _serverIp;
	sf::Packet _sendPacket, _rcvPacket;
	sf::UdpSocket _uSocket;
	sf::TcpSocket _tSocket;
	unsigned short _port;

};

