#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	_serverIp = sf::IpAddress("127.0.0.1");
}

NetworkManager::~NetworkManager()
{

}
void NetworkManager::tcpSendPacket(int id)
{
	_sendPacket << id;
	_tSocket.send(_sendPacket);
	_sendPacket.clear();
}
sf::Packet NetworkManager::udpSendPacket(int id)
{
	sf::Packet packet;

	packet << id;

	sf::IpAddress sendIp("127.0.0.1");
	_uSocket.send(packet, sendIp, 54000);
	return _sendPacket;
}

sf::Packet NetworkManager::udpRecievePacket()
{
	
	_uSocket.receive(_rcvPacket, _serverIp, _port);

	return _rcvPacket;
}

void NetworkManager::tcpHandshake()
{
	
	sf::Socket::Status status = _tSocket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		// error...
	}

	
}

sf::Packet NetworkManager::tcpRecievePacket()
{
	int type;
	
	if (_tSocket.receive(_rcvPacket) != sf::Socket::Done)
	{
		// error...
	}
	else
	{
		_rcvPacket >> type;
		switch (type)
		{
		case 1:
			test++;
			std::cout << test << std::endl;
			break;
		default:
			std::cout << "nope" << std::endl;
		}
		
	}
	

	

	return _rcvPacket;
}

void NetworkManager::setPort(unsigned short port)
{
	_uSocket.bind(53000);
}