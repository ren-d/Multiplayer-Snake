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

bool isLoaded = false;
std::vector<pillDATA> pills;

pillDATA generatePill(pillDATA newPill)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-1500, 1500);


	newPill.posX = distr(gen);
	newPill.posY = distr(gen);

	if (distr(gen) > 500) {
		newPill.growthValue = 2;
	}
	else
	{
		newPill.growthValue = 1;
	}

	return newPill;
}

void generatePills()
{
	for (int i = 0; i < 300; i++)
	{
		pillDATA newPill;
		newPill.id = i;
		
		pills.push_back(generatePill(newPill));
	}
}



int main()
{
	int numberOfPlayers;
	std::vector<playerDATA> players;
	std::vector<unsigned short> ports;
	sf::Int16 data[1];
	generatePills();
	isLoaded = false;
	sf::Packet packet;

	sf::UdpSocket socket;
	playerDATA player;
	// UDP socket:
	sf::IpAddress sender;
	unsigned short port;
	std::size_t received = 0;
	sf::TcpListener listener;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		// error...
	}

	socket.bind(54000);
	while (true)
	{
		
		
		

		// accept a new connection
		
		sf::TcpSocket client;
		if(isLoaded != true)
		{ 
			if (listener.accept(client) != sf::Socket::Done)
			{
				// error...
			}
			else
			{
				std::cout << "WINNER" << std::endl;
				for (int i = 0; i < 300; i++)
				{
					packet << static_cast<int>(DataType::PILL) << pills[i].id << pills[i].posX << pills[i].posY << pills[i].growthValue;
					if (client.send(packet) != sf::Socket::Done)
					{
						// error...
					}
					packet.clear();
				}
				client.disconnect();
				isLoaded = true;
			}
		}
		

		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{
			
		}
		else
		{
			int id;
			packet >> id;
			
			std::cout << id;
			pills[id] = generatePill(pills[id]);
			packet.clear();

			packet << static_cast<int>(DataType::PILL) << pills[id].id << pills[id].posX << pills[id].posY << pills[id].growthValue;
			socket.send(packet, sender, port);
			packet.clear();
			
		}

		

	}

	
	

	return 0;
}
