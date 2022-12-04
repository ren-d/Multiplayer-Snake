#include "Player.h"
Player::Player(sf::Vector2f newPosition)
{
	center = newPosition;
	_size = 3;
	_speed = 50;
	_head = new Node(1, 0,10, 10, sf::Color::Red);

	_end = new Node(1, 0, 5, 10, sf::Color::Black);
	_head->prev = _end;
	_end->next = _head;
	Init();
	
}

Player::~Player()
{

}

void Player::Init()
{

	for (int i = 0; i < _size - 1; i++) {
		addTailNode();
	}
}

void Player::handleInput(float dt)
{
	if (true)
	{
		sf::Vector2f mouse( input->getMouseX() - center.x,  input->getMouseY() - center.y );
		mouse = VectorHelper::normalise(mouse);

		_head->_yDir = mouse.y * 3;
		_head->_xDir = mouse.x * 3;


	}

	if (input->isPressed(sf::Keyboard::Space))
	{
		Grow();
	}
}

void Player::Render(sf::RenderWindow* window)
{
	Node* current = _head->prev;

	while (current != nullptr) {
		window->draw(current->shape);
		current = current->prev;
	}

	window->draw(_head->shape);
}

void Player::Grow()
{
	addTailNode();
}

void Player::Die()
{

}

void Player::addFront(Node* node)
{
	if (_size == 0) {
		_end = node;
	} else {
		_head->prev = node;
	}

	_head = node;
	_size++;
}

void Player::addEnd(Node* node)
{
	if (_size == 0) {
		_head = node;
		_end = node;
		return;
	}

	_end->prev = node;
	node->next = _end;
	_end = node;

}

void Player::addTailNode()
{
	addEnd(new Node(_end->_xDir, _end->_yDir, _end->_xPos - _end->_xDir, _end->_yPos - _end->_yDir, sf::Color::Green));
}

sf::Vector2f Player::getHeadPosition()
{
	return sf::Vector2f(_head->_xPos, _head->_yPos);
}
void Player::update(float dt)
{
	Node* current = _head;

	while (current != nullptr) {
		current->updateDirection();
		current->updatePosition(dt, _speed);
		current = current->prev;
	}

}

