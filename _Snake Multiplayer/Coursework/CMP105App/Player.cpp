#include "Player.h"
Player::Player(sf::Vector2f screenCenter)
{
	_screenCenter = screenCenter;
	_size = 3;
	_speed = 50;
	_scale = sf::Vector2f(1, 1);
	_head = new Node(1, 0,10, 10, sf::Color::Blue, &_scale);
	_end = new Node(1, 0, 8, 10, sf::Color::Cyan, &_scale);
	_head->prev = _end;
	_end->next = _head;
	setSize(sf::Vector2f(_head->getShape().getLocalBounds().width, _head->getShape().getLocalBounds().height));
	Init();
	_counter = 0;
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
	_counter += dt;

	if (outOfBounds) {
		_outOfBoundsCounter += dt;
		if (_outOfBoundsCounter >= 3)
		{
			Die();
		}
	}
	else
	{
		_outOfBoundsCounter = 0;
	}
	
	if (input->isKeyDown(sf::Keyboard::LShift))
	{
		_speed = 100;
		if (_counter >= 0.1)
		{
			Shrink();
		}

	}
	else
	{
		_speed = 50;
	}

	_mouseDirectionVector = sf::Vector2f( input->getMouseX() - _screenCenter.x,  input->getMouseY() - _screenCenter.y );
	float angle = atan2(_mouseDirectionVector.x, _mouseDirectionVector.y);
	
	_head->setDirection(sf::Vector2f (3 * sin(angle) , 3 * cos(angle)));
	
	
		

	if (input->isPressed(sf::Keyboard::Space))
	{
		
			Grow(20);
		
		
	}

	setPosition(_head->getPosition());
}

void Player::Shrink()
{
	Node* temp = _end->next;
	temp->prev = nullptr;
	delete _end;
	_end = temp;

	_size--;
	_scale.x -= 0.002;
	_scale.y -= 0.002;
	_counter = 0;
}


void Player::Render(sf::RenderWindow* window)
{
	Node* current = _head->prev;


	while (current != nullptr) {
		window->draw(current->getShape());
		current = current->prev;
	}

	window->draw(_head->getShape());
}

void Player::Grow(int growth)
{
	for (int i = 0; i < growth; i++)
	{
		addTailNode();
		_scale.x += 0.002;
		_scale.y += 0.002;
		_size++;
	}
	
}

void Player::Die()
{
	exit(1);
}

void Player::addFront(Node* node)
{
	if (_size == 0) {
		_end = node;
	} else {
		_head->prev->prev->next = node;
		_head->prev = node;
	}

	
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
	node->updatePosition(0, _speed);
	_end = node;

}

void Player::addTailNode()
{
	addEnd(new Node(_end->getDirection().x, _end->getDirection().y,
					_end->getPosition().x - _end->getDirection().y, 
					_end->getPosition().y - _end->getDirection().y, 
					sf::Color::Cyan, 
					&_scale));
}

sf::Vector2f Player::getHeadPosition()
{
	return _head->getPosition();
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

