#include "SFML/Network.hpp"
#include <iostream>
#include <random>
#include <thread>
enum class NetworkType {
	PLAYER = 0, PILL = 1, TEXT = 2, EVENT = 3, WORLD = 4, PLAYER_INIT = 5, PING = 6, PONG = 7
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
float deltaTime;
float server_time;

int playerno = 0;
//main server
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
		//wait for new connection
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
					//add client to stack
					clients.push_back(newClient);
					selector.add(*newClient);
					std::cout << "NEW CLIENT CONNECTED" << std::endl;
					if (isLoaded != true)
					{
						playerno++;
						for (int i = 0; i < pills.size(); i++)
						{
							packet << static_cast<int>(NetworkType::PILL) << pills[i].id << pills[i].posX << pills[i].posY << pills[i].growthValue;
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

//udp thread
void udpConnection()
{
	sf::Clock clock;
	sf::Packet udpPacket;
	socket.bind(54000);

	socket.setBlocking(false);

	while (true)
	{
		deltaTime = clock.restart().asSeconds();
		server_time += deltaTime;
		if (socket.receive(udpPacket, sender, port) != sf::Socket::Done)
		{

		}
		else
		{
			processRecievedPacket(udpPacket);
		}
	}
}

//check for incoming udp packets
void processRecievedPacket(sf::Packet packet)
{
	playerDATA* newPlayer;
	int dataType;
	int id = 0;
	packet >> dataType;

	//network type state machine
	switch (static_cast<NetworkType>(dataType)) {
	case NetworkType::PING:
		packet.clear();
		packet << static_cast<int>(NetworkType::PONG) << server_time;
		socket.send(packet, sender, port);
		packet.clear();
		break;
	case NetworkType::WORLD:
		
		packet << id;

		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->id == id)
			{
				for (int j = 0; i < ports.size(); i++)
				{
					
					if (players[i]->port == port)
					{
						ports.erase(ports.begin() + j);
						std::cout << players[i]->name << " disconnected" << std::endl;
						
					}
				}
			}
		}
		packet.clear();

		packet << static_cast<int>(NetworkType::WORLD) << id;

		for (int i = 0; i < ports.size(); i++)
		{
			socket.send(packet, sender, ports[i]);
		}
		packet.clear();

		break;

	case NetworkType::PLAYER_INIT:
		if (std::count(ports.begin(), ports.end(), port))
		{
			std::cout << "port already in use" << std::endl;
			break;
		}

		int temp;
		packet >> temp;
		ports.push_back(port);
		newPlayer = new playerDATA();
		packet >> newPlayer->name >> newPlayer->speed >> newPlayer->posX >> newPlayer->posY >> newPlayer->dirX >> newPlayer->dirY >> newPlayer->size;
		newPlayer->id = playerno;
		newPlayer->port = port;
		players.push_back(newPlayer);

		std::cout << newPlayer->name << newPlayer->speed << newPlayer->posX << newPlayer->posY << newPlayer->dirX << newPlayer->dirY << newPlayer->size << std::endl;
		packet.clear();

		packet << static_cast<int>(NetworkType::PLAYER_INIT) << newPlayer->id << playerno;

		for (playerDATA* player : players)
		{
			packet << player->id << player->name << player->speed << player->posX << player->posY << player->dirX << player->dirY << player->size;
		}

		for (int i = 0; i < ports.size(); i++)
		{
			socket.send(packet, sender, ports[i]);
		}

		packet.clear();

		break;
	case NetworkType::PLAYER:
		int pid;
		packet >> pid;
		
		for (playerDATA* player : players)
		{
			if (player->id == pid)
			{
				
				packet >> player->name >> player->speed >> player->posX >> player->posY >> player->dirX >> player->dirY >> player->size;
	

			}
		}
		packet.clear();
		packet << static_cast<int>(NetworkType::PLAYER) << playerno;

		for (playerDATA* player : players)
		{
			
			packet << player->id << player->name << player->speed << player->posX << player->posY << player->dirX << player->dirY << player->size;
			
			
		}
		
		for (int i = 0; i < ports.size(); i++)
		{
			if (ports[i] != port)
			{
				socket.send(packet, sender, ports[i]);
			}

		}
		
		packet.clear();
		break;
	case NetworkType::PILL:
		int id;
		packet >> id;
		pills[id] = generatePill(pills[id], id);
		packet.clear();

		packet << static_cast<int>(NetworkType::PILL) << pills[id].id << pills[id].posX << pills[id].posY << pills[id].growthValue;
		std::cout << "Pill Removed: " << std::endl;
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

//generate world
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