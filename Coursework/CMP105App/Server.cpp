#include "SFML/Network.hpp"
#include <iostream>
#include <random>
enum class DataType {
	PLAYER = 0, PILL = 1, TEXT = 2, EVENT = 3, WORLD = 4
};
struct playerDATA
{
	char name[4];
	int id,
		speed,
		posX, posY,
		dirX, dirY;
};

struct pillDATA
{
	int id,
		posX, posY,
		growthValue;
};

std::vector<pillDATA> pills;
void generatePills()
{
	for (int i = 0; i < 300; i++)
	{
		pillDATA newPill;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(-1500, 1500);

		newPill.id = i;
		newPill.posX = distr(gen);
		newPill.posY = distr(gen);

		if (distr(gen) > 500) {
			newPill.growthValue = 2;
		}
		else
		{
			newPill.growthValue = 1;
		}
		
		pills.push_back(newPill);
	}
}

int main()
{
	int numberOfPlayers;
	std::vector<playerDATA> players;
	std::vector<unsigned short> ports;

	generatePills();
	
	sf::Packet packet;

	sf::UdpSocket socket;
	playerDATA player;
	// UDP socket:
	sf::IpAddress sender;
	unsigned short port;

	sf::TcpListener listener;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		// error...
	}

	socket.bind(54000);
	while (true)
	{
		/*
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
		*/

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			// error...
		}
		else
		{
			std::cout << "WINNER" << std::endl;
			for (int i = 0; i < 300; i++)
			{
				packet << static_cast<int>(DataType::PILL) << pills[i].id  << pills[i].posX << pills[i].posY << pills[i].growthValue;
				if (client.send(packet) != sf::Socket::Done)
				{
					// error...
				}
				packet.clear();
			}
			
		}

	}

	
	

	return 0;
}
