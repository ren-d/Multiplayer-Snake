#include "SFML/Network.hpp"
#include <iostream>

struct playerDATA
{
	char name[4];
	int id,
		speed,
		posX, posY,
		dirX, dirY;
};
int main()
{
	int numberOfPlayers;
	std::vector<playerDATA> players;
	std::vector<unsigned short> ports;
	sf::Int16 data[7];
	sf::Packet packet;
	std::size_t received = 0;
	sf::UdpSocket socket;
	playerDATA player;
	// UDP socket:
	sf::IpAddress sender;
	unsigned short port;
	socket.bind(54000);
	while (true)
	{
		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{
			// error...
		}
		else
		{
			packet >> player.id >> player.name >> player.posX >> player.posY;
			std::cout << player.id << " " << player.name << std::endl;
			std::cout << "x: " << player.posX << " y: " << player.posY << std::endl;
		}


	}

	
	

	return 0;
}