#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	
	shape = sf::CircleShape(10);
	wall = sf::RectangleShape(sf::Vector2f(100, 100));
	wall.setFillColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	player1 = new Player(sf::Vector2f(window->getView().getSize().x / 2, window->getView().getSize().y / 2));
	player1->setInput(in);
	sf::View* view = new sf::View(player1->getHeadPosition(), window->getView().getSize());
	for (int i = 0; i < MAX_PILLS; i++)
	{
		pills.push_back( new Pill());
		pills[i]->setWindow(window);
	}

	player1->_playerIp = sf::IpAddress::getLocalAddress();
	socket.bind(53846);
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
	
	sf::Int16 test[7];
	test[0] = 2;
	test[1] = player1->_playerData.name[0];
	test[2] = player1->_playerData.name[1];
	test[3] = player1->_playerData.name[2];
	test[4] = player1->_playerData.name[3];
	test[5] = player1->getHeadPosition().x;
	test[6] = player1->getHeadPosition().y;
	sf::IpAddress sendIp("127.0.0.1");
	socket.send(test, sizeof(test), sendIp, 54000);


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

	player1->Render(window);
	
	
	endDraw();
}

void Level::update(float dt)
{

	sf::View view = sf::View(player1->getHeadPosition(), window->getView().getSize());
	window->setView(view);
	
	player1->update(dt);

	for (int i = 0; i < pills.size() - 1; i++)
	{
		if (Collision::checkBoundingCircle(pills[i], player1))
		{
			std::cout << "what" << std::endl;
			player1->Grow(pills[i]->_growthValue);
			
			delete pills[i];
			pills[i] = new Pill();
		}
	}
}

void networkUpdate()
{

}