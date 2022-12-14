#include "SFML/Network.hpp"
#include <iostream>

struct playerDATA
{
	char name[4];
	int posX;
	int posY;
	int id;
};
int main()
{
	int numberOfPlayers;
	std::vector<playerDATA> players;
	std::vector<unsigned short> ports;
	sf::Int16 data[7];

	std::size_t received = 0;
	sf::UdpSocket socket;
	
	// UDP socket:
	sf::IpAddress sender;
	unsigned short port;
	socket.bind(54000);
	while (true)
	{
		if (socket.receive(data, sizeof(data), received, sender, port) != sf::Socket::Done)
		{
			// error...
		}
		else
		{
			std::cout << data[0] << " " << (char)data[1] << (char)data[2] << (char)data[3] << (char)data[4] << " Position X: " << data[5] << " Position Y: " << data[6] << std::endl;
		}


	}

	
	

	return 0;
}