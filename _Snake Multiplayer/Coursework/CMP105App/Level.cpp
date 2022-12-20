#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	/**/
	networkManager = new NetworkManager();
	networkManager->setPort(53846);
	networkManager->tcpHandshake();
	std::string bruh;
	
	ghostManager = new GhostManager();



	player1 = new Player(sf::Vector2f(window->getView().getSize().x / 2, window->getView().getSize().y / 2));
	player1->setInput(in);
	sf::View* view = new sf::View(player1->getHeadPosition(), window->getView().getSize());

	pillDATA pillData;
	for (int i = 0; i < MAX_PILLS; i++)
	{
		networkManager->tcpRecievePacket() >> pillData.id >> pillData.x >> pillData.y >> pillData.growthValue;
		Pill* newPill = new Pill(pillData);
		pills.push_back(newPill);
		pills[i]->setWindow(window);
	}
	
	


}

Level::~Level()
{

}

void Level::handleInput(float dt)
{

	player1->handleInput(dt);

	
}

void Level::render()
{


	
	if (player1->getHeadPosition().x > 1500 || player1->getHeadPosition().x < -1500 ||
		player1->getHeadPosition().y > 1500 || player1->getHeadPosition().y < -1500)
	{
		window->clear(sf::Color(125, 0, 0));
		player1->outOfBounds = true;
	}
	else
	{
		beginDraw();
		player1->outOfBounds = false;
	}
	
	
	for (int i = 0; i < pills.size() - 1; i++)
	{
		
		pills[i]->render(window);
	}
	ghostManager->render(window);
	player1->Render(window);
	
	
	endDraw();
}

void Level::update(float dt)
{
	if (!ponged)
	{
		global_server_time += clock.getElapsedTime().asSeconds();
		if (!sentPlayerData)
		{
			
			networkManager->udpSendPacket(player1->getPlayerData(), true);
			sentPlayerData = true;
		}
		
	}
	else
	{
		
		count += dt;

		ghostManager->update(dt);
		


		sf::View view = sf::View(player1->getHeadPosition(), window->getView().getSize());
		window->setView(view);

		player1->update(dt);



		for (int i = 0; i < pills.size() - 1; i++)
		{
			if (Collision::checkBoundingCircle(pills[i], player1))
			{
				std::cout << "what" << std::endl;
				player1->Grow(pills[i]->_growthValue);
				networkManager->udpSendPacket(pills[i]->_data.id);


				delete pills[i];
				pills[i] = new Pill();
			}
		}
	}
	
	int type = -1;
	sf::Packet packet = networkManager->udpRecievePacket();
	packet >> type;
	int serverplayers;
	switch (static_cast<NetworkType>(type))
	{
	case NetworkType::PONG:
		ponged = true;
		
		float server_time;
		packet >> server_time;
		if (global_server_time > 1.0f)
		{
			ping = std::abs(global_server_time - server_time);

			pongs.push_back(ping);

		}

		global_server_time = server_time;
		if (pongs.size() >= 5)
		{
			float temp = pongs[0];
			pongs[0] = pongs.back();
			pongs.back() = temp;
			pongs.pop_back();
			int size = 0;
			float pongValues = 0;
			for (float pong : pongs)
			{

				size++;
				pongValues += pong;
				std::cout << pongValues << std::endl;


			}

			pongValues /= size;
			ping = pongValues;
			std::cout << "PING: " << ping << std::endl;
			pongValues = 0;
			
		}
		else
		{
			networkManager->sendPing();
		}
		ping = 0;
		
		break;
	case NetworkType::PLAYER_INIT:
		pongs.clear();
		networkManager->sendPing();
		int id;
		packet >> id;
		if (player1->getPlayerData().id <= 0)
		{
			player1->setId(id);
		}


		packet >> serverplayers;
		for (int i = 0; i < serverplayers; i++)
		{
			playerDATA data;
			packet >> data.id >> data.name >> data.speed >> data.posX >> data.posY >> data.dirX >> data.dirY >> data.size;

			if (data.id != player1->getPlayerData().id)
			{
				ghostManager->addGhost(data);

			}


		}
		packet.clear();
		break;
	case NetworkType::PLAYER:
		packet >> serverplayers;
		playerDATA data;
		for (int i = 0; i < serverplayers; i++)
		{
			packet >> data.id >> data.name >> data.speed >> data.posX >> data.posY >> data.dirX >> data.dirY >> data.size;
			if (data.id != player1->getPlayerData().id)
			{
				ghostManager->updateGhostData(data);

			}
		}

		break;
	case NetworkType::PILL:
		pillDATA pillData;
		packet >> pillData.id >> pillData.x >> pillData.y >> pillData.growthValue;
		std::cout << pillData.id << std::endl;
		std::cout << pillData.x << std::endl;
		std::cout << pillData.y << std::endl;
		std::cout << pillData.growthValue << std::endl;

		delete pills[pillData.id];
		pills[pillData.id] = new Pill(pillData);

		break;
	}

	if (count >= 0.05f)
	{
		if (player1->getPlayerData().speed > 0)
		{
			networkManager->udpSendPacket(player1->getPlayerData(), false);
			cooldown = 0;
		}
		else if (player1->getPlayerData().speed == 0 && cooldown == 0)
		{
			networkManager->udpSendPacket(player1->getPlayerData(), false);
			cooldown++;
		}
		count = 0;
	}
	
	
	
}

void networkUpdate()
{
}