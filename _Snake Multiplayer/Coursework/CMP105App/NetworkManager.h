#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Player.h"
enum class NetworkType {
	PLAYER = 0, PILL = 1, TEXT = 2, EVENT = 3, WORLD = 4, PLAYER_INIT = 5, PING = 6, PONG = 7
};

enum class PacketType {
	PT_HELLO
};




struct textDATA
{

};

struct eventDATA
{

};

struct worldDATA
{

};

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	sf::Packet udpSendPacket(int id);
	sf::Packet udpSendPacket(playerDATA data, bool isInit);
	sf::Packet udpSendPacket(bool death, int id);
	sf::Packet udpRecievePacket();
	void tcpSendPacket(int id);
	sf::Packet tcpRecievePacket();

	void sendPing();

	void tcpHandshake();

	void setPort(unsigned short port);
	unsigned short getPort();

	void setServerIp(std::string ip);
	sf::IpAddress getServerIp();

	sf::IpAddress getLocalIp();



	int test = 0;
	sf::IpAddress _localIp, _serverIp;
	sf::Packet _sendPacket, _rcvPacket;
	sf::UdpSocket _uSocket;
	sf::TcpSocket _tSocket;
	unsigned short _port;

};

