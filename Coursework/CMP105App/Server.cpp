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
		size;
	float dirX, dirY;
	unsigned short port;
};

struct pillDATA
{
	sf::Int16 id,
		posX, posY,
		growthValue;
};


pillDATA generatePill(pillDATA newPill, int id);
void generatePills();
void udpConnection();
void processRecievedPacket(sf::Packet packet);


bool isLoaded = false;
std::vector<pillDATA> pills;

sf::UdpSocket socket;
sf::Packet packet;
sf::IpAddress sender;
unsigned short port;
std::vector<playerDATA*> players;
std::vector<unsigned short> ports;

int playerno = 0;
int main()
{
	std::vector<sf::TcpSocket*> clients;
	generatePills();
	bool isLoaded = false;
	sf::Packet packet;
	
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
						playerno++;
						for (int i = 0; i < pills.size(); i++)
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

void udpConnection()
{
	sf::Packet udpPacket;
	socket.bind(54000);

	socket.setBlocking(false);

	while (true)
	{
		if (socket.receive(udpPacket, sender, port) != sf::Socket::Done)
		{

		}
		else
		{
			processRecievedPacket(udpPacket);
		}
	}
}


void processRecievedPacket(sf::Packet packet)
{
	std::cout << port << std::endl;
	int dataType;
	packet >> dataType;
	switch (static_cast<DataType>(dataType)) {
	case DataType::PLAYER:
		if (!std::count(ports.begin(), ports.end(), port))
		{

			ports.push_back(port);
			playerDATA* newPlayer = new playerDATA();
			packet >> newPlayer->name >> newPlayer->speed >> newPlayer->posX >> newPlayer->posY >> newPlayer->dirX >> newPlayer->dirY >> newPlayer->size;
			newPlayer->id = playerno;
			newPlayer->port = port;
			players.push_back(newPlayer);

			std::cout << newPlayer->name << newPlayer->speed << newPlayer->posX << newPlayer->posY << newPlayer->dirX << newPlayer->dirY << newPlayer->size<< std::endl;
			packet.clear();

			packet << static_cast<int>(DataType::PLAYER) << newPlayer->id << playerno;

			for (playerDATA* player : players)
			{
				packet << player->id << player->name << player->speed << player->posX << player->posY << player->dirX << player->dirY << player->size;
			}

			for (int i = 0; i < ports.size(); i++)
			{
				socket.send(packet, sender, ports[i]);
			}
			
			packet.clear();
		}
		else
		{

		}

		break;
	case DataType::PILL:
		int id;
		packet >> id;
		pills[id] = generatePill(pills[id], id);
		packet.clear();

		packet << static_cast<int>(DataType::PILL) << pills[id].id << pills[id].posX << pills[id].posY << pills[id].growthValue;

		std::cout << pills[id].id << std::endl;
		std::cout << pills[id].posX << std::endl;
		std::cout << pills[id].posY << std::endl;
		std::cout << pills[id].growthValue << std::endl;

		for (int i = 0; i < ports.size(); i++)
		{
			socket.send(packet, sender, ports[i]);

		}

		packet.clear();

		break;
	}
}

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