#include "SFML/Network.hpp"
#include <iostream>
#include <random>
#include <thread>
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
	sf::Int16 id,
		posX, posY,
		growthValue;
};

bool isLoaded = false;
std::vector<pillDATA> pills;

pillDATA generatePill(pillDATA newPill, int id)
{
	newPill.id = id;
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
		pills.push_back(generatePill(newPill, i));

	}
}
sf::UdpSocket socket;
sf::Packet packet;
sf::IpAddress sender;
unsigned short port;

void udpConnection()
{
	socket.bind(54000);
	
	socket.setBlocking(false);
	
	while (true)
	{
		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{

		}
		else
		{
			
			int id;
			packet >> id;

			pills[id] = generatePill(pills[id], id);
			packet.clear();

			packet << static_cast<int>(DataType::PILL) << pills[id].id << pills[id].posX << pills[id].posY << pills[id].growthValue;

			std::cout << pills[id].id << std::endl;
			std::cout << pills[id].posX << std::endl;
			std::cout << pills[id].posY << std::endl;
			std::cout << pills[id].growthValue << std::endl;
			socket.send(packet, sender, port);
			packet.clear();
	

		}
	}
	
	
	
}


int main()
{
	int numberOfPlayers;
	
	std::vector<sf::TcpSocket*> clients;
	
	generatePills();
	isLoaded = false;
	sf::Packet packet;
	
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
	sf::SocketSelector selector;

	selector.add(listener);
	sf::TcpSocket client;
	

	sf::Thread* thread = new sf::Thread(udpConnection);
	thread->launch();
	
	while (true)
	{
		
		
		

		// accept a new connection
		if (selector.wait())
		{
			if (selector.isReady(listener))
			{
				
					sf::TcpSocket* newClient = new sf::TcpSocket;
					newClient->setBlocking(false);
					if (listener.accept(*newClient) != sf::Socket::Done)
					{
						// error...
					}
					else
					{
						clients.push_back(newClient);
						selector.add(*newClient);

						std::cout << "WINNER" << std::endl;
						if (isLoaded != true)
						{
							for (int i = 0; i < 300; i++)
							{
								packet << static_cast<int>(DataType::PILL) << pills[i].id << pills[i].posX << pills[i].posY << pills[i].growthValue;
								if (newClient->send(packet) != sf::Socket::Done)
								{
									// error...
								}
								packet.clear();
								
								
							}
						}
						
					}
				
			}

			
			
			
		}
		
		
		

		

		

	}

	
	

	return 0;
}
