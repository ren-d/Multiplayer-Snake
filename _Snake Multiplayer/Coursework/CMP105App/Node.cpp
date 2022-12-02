#include "Node.h"
Node::Node()
{

}

Node::~Node()
{

}

void Node::updatePosition(float dt, float speed)
{
	_xPos = _xPos + (_xDir * dt) * speed;
	_yPos = _yPos + (_yDir * dt) * speed;
	shape.setPosition(sf::Vector2f(_xPos, _yPos));
}


void Node::updateDirection()
{

	if (next != nullptr) {
		sf::Vector2f newvec( next->_xPos - _xPos ,  next->_yPos - _yPos );
		newvec = VectorHelper::normalise(newvec);
		_xDir = newvec.x * 3;
		_yDir = newvec.y * 3;

	}
	
}