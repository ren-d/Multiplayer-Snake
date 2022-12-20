#include "Ghost.h"
Ghost::Ghost(playerDATA data)
{
	_size = data.size;
	_speed = data.speed;
	_scale = sf::Vector2f(1, 1);
	_head = new Node(data.dirX, data.dirY, data.posX, data.posY, sf::Color::Red, &_scale);
	_end = new Node(data.dirX, data.dirY, data.posX - 3, data.posY, sf::Color::Yellow, &_scale);
	_head->prev = _end;
	_end->next = _head;

	setSize(sf::Vector2f(_head->getShape().getLocalBounds().width, _head->getShape().getLocalBounds().height));
	Init();


	_playerData = data;
}

Ghost::~Ghost()
{

}
void Ghost::updatePlayerData(playerDATA data)
{
	_playerData.speed = data.speed;
	_playerData.dirX = data.dirX;
	_playerData.dirY = data.dirY;
	_speed = _playerData.speed;

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

	std::cout << "MAMA" << _playerData.dirX << _playerData.dirY;
	_head->setDirection(sf::Vector2f(_playerData.dirX, _playerData.dirY));

	setPosition(_head->getPosition());

	

}

void Ghost::handleInput(float dt)
{
	_speed = _playerData.speed;
}