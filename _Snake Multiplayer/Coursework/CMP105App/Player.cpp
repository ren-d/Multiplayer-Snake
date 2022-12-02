#include "Player.h"
Player::Player()
{
	_size = 3;
}

Player::~Player()
{

}

void Player::Init()
{
	addFront(new Node());
	for (int i = 0; i < _size - 1; i++) {
		addTailNode();
	}
}

void Player::handleInput(float dt)
{

}

void Player::Render()
{

}

void Player::Grow()
{

}

void Player::Die()
{

}

void Player::addFront(Node* node)
{
	node->next = _head;
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
	node->next = _head;
	if (_size == 0) {
		_head = node;
		_end = node;
		return;
	}

	_end->next = node;
	node->prev = _end;
	_end = node;
	_size++;
}

void Player::addTailNode()
{
	addEnd(new Node(_end->_xPos - _end->_xDir,
					_end->_yPos - _end->_yDir, 
					_end->_xDir, _end->_yDir));
}

void Player::update(float dt)
{
	Node* current = _head;

	while (current != nullptr) {
		current->updatePosition();
		current = current->next;
	}
}

