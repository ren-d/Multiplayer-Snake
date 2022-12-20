#include "Node.h"
Node::Node()
{

}

Node::~Node()
{

}

void Node::updatePosition(float dt, float speed)
{
	_shape.setScale(*_scale);
	if (next != nullptr) {
		
		if (distanceToNextNode())
		{
			_xPos = _xPos + (_xDir * dt) * speed;
			_yPos = _yPos + (_yDir * dt) * speed;
		}
		else
		{
			_xPos = _xPos + (_xDir * dt) * 0;
			_yPos = _yPos + (_yDir * dt) * 0;
		}
		
	}
	else
	{
		_xPos = _xPos + (_xDir * dt) * speed;
		_yPos = _yPos + (_yDir * dt) * speed;
	}
	
	_shape.setPosition(sf::Vector2f(_xPos, _yPos));
	
}


bool Node::distanceToNextNode()
{
	float magnitude = VectorHelper::magnitude(sf::Vector2f(next->_xPos - _xPos, next->_yPos - _yPos));
	if (magnitude > 3) {
		return true;
	}

	return false;
}
void Node::updateDirection()
{
	
	if (next != nullptr) {

		float angle = atan2((double)next->getPosition().y - _yPos, (double)next->getPosition().x - _xPos);
		_xDir = 3 * cos(angle);
		_yDir = 3 * sin(angle);
		

	}
	
}

sf::Vector2f Node::getDirection()
{
	return sf::Vector2f(_xDir, _yDir);
}

sf::Vector2f Node::getPosition()
{
	return sf::Vector2f(_xPos, _yPos);
}

sf::Vector2f Node::getScale()
{
	return *_scale;
}

sf::CircleShape Node::getShape()
{
	return _shape;
}

void Node::setDirection(sf::Vector2f newDirection)
{
	_xDir = newDirection.x;
	_yDir = newDirection.y;
}
