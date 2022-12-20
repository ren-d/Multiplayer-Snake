#include "Ghost.h"
Ghost::Ghost(playerDATA data)
{
	_size = data.size;
	_speed = 0;
	_scale = sf::Vector2f(1, 1);
	_bodyColor = sf::Color::Yellow;
	_head = new Node(data.dirX, data.dirY, data.posX, data.posY, sf::Color::Red, &_scale);
	_end = new Node(data.dirX, data.dirY, data.posX - 3, data.posY, sf::Color::Yellow, &_scale);
	_head->prev = _end;
	_end->next = _head;
	
	setSize(sf::Vector2f(_head->getShape().getLocalBounds().width, _head->getShape().getLocalBounds().height));
	Init();


	_playerData = data;

	directionVectors[0] = sf::Vector2f(0,0);
	directionVectors[1] = sf::Vector2f(0, 0);
	directionVectors[2] = sf::Vector2f(0, 0);
}

Ghost::~Ghost()
{

}
void Ghost::updatePlayerData(playerDATA data, float ping)
{

	_playerData.speed = data.speed;

	_speed = _playerData.speed;
	directionVectors[0] = directionVectors[1];
	directionVectors[1] = directionVectors[2];
	directionVectors[2] = sf::Vector2f(-data.dirX, -data.dirY);

	int growth = data.size - _playerData.size;

	if (growth > 0)
	{
		
		Grow(growth);
	}
	else if (growth < 0)
	{
		Shrink(growth);
	}
	
	_playerData.size = _size;


	float dirXAverage = (directionVectors[0].x + directionVectors[1].x + directionVectors[2].x) / 3.0f;
	float dirYAverage = (directionVectors[0].y + directionVectors[1].y + directionVectors[2].y) / 3.0f;
	_playerData.dirX = dirXAverage;
	_playerData.dirY = dirYAverage;
	_head->setDirection(sf::Vector2f(-_playerData.dirX, -_playerData.dirY));

	setPosition(_head->getPosition());
	 
	

}

void Ghost::handleInput(float dt)
{
	_speed = _playerData.speed;
}