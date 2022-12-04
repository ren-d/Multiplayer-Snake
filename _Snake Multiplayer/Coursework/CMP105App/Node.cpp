#include "Node.h"
Node::Node()
{

}

Node::~Node()
{

}

void Node::updatePosition(float dt, float speed)
{
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
	
	shape.setPosition(sf::Vector2f(_xPos, _yPos));
}

bool Node::distanceToNextNode()
{
	float magnitude = VectorHelper::magnitude(sf::Vector2f(next->_xPos - _xPos, next->_yPos - _yPos));
	if (magnitude > 5) {
		return true;
	}

	return false;
}
void Node::updateDirection()
{
	
	if (next != nullptr) {

		float angle = atan2(next->_yPos - _yPos, next->_xPos - _xPos);
		_xDir = 3 * cos(angle);
		_yDir = 3 * sin(angle);
		

	}
	
}