#include "Player.h"
Player::Player()
{
	_size = 30;
	_speed = 50;
	_head = new Node(1, 0, 10, 10);

	_end = new Node(1, 0, 5,10);
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
		sf::Vector2f mouse( input->getMouseX() - _head->_xPos ,  input->getMouseY() - _head->_yPos );
		mouse = VectorHelper::normalise(mouse);
		_head->_yDir = mouse.y * 3;
		_head->_xDir = mouse.x * 3;


	}
}

void Player::Render(sf::RenderWindow* window)
{
	Node* current = _head;

	while (current != nullptr) {
		window->draw(current->shape);
		current = current->prev;
	}
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
	addEnd(new Node(_end->_xDir, _end->_yDir * 3, _end->_xPos - _end->_xDir * 3, _end->_yPos - _end->_yDir ));
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

