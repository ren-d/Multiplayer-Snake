#include "NetworkManager.h"

NetworkManager::NetworkManager()
{

}

NetworkManager::~NetworkManager()
{

}

sf::Packet NetworkManager::udpSendPacket(DataType type)
{
	return _sendPacket;
}

sf::Packet NetworkManager::udpRecievePacket()
{
	
	_uSocket.receive(_rcvPacket, _serverIp, _port);

	return _rcvPacket;
}

sf::Packet NetworkManager::tcpSendPacket()
{
	
	sf::Socket::Status status = _tSocket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		// error...
	}

	return _sendPacket;
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
	_uSocket.bind(port);
}