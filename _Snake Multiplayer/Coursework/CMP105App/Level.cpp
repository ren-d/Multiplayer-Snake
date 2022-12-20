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

	networkManager->udpSendPacket(player1->getPlayerData());


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
	
	ghostManager->update(dt);
	int type = -1;


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
	sf::Packet packet = networkManager->udpRecievePacket();
	packet >> type;
	
	switch (static_cast<DataType>(type))
	{
	case DataType::PLAYER:
		
		int id;
		packet >> id;
		player1->setId(id);
		int serverplayers;
		packet >> serverplayers;
		std::cout << "tage" << serverplayers << std::endl;
		for (int i = 0; i < serverplayers; i++)
		{
			playerDATA data;
			packet >> data.id >> data.name >> data.speed >>data.posX >> data.posY >> data.dirX >> data.dirY >> data.size;
			if (data.id != player1->getPlayerData().id)
			{
				ghostManager->addGhost(data);
			}
			

		}
		break;
	case DataType::PILL:
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

}

void networkUpdate()
{
}