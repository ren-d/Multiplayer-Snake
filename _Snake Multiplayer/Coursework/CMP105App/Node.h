#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "Framework/VectorHelper.h"

class Node
{

public:
	
	Node();
	Node(float xDir, float yDir, float xPos, float yPos, sf::Color color, sf::Vector2f* scale) {
		prev = nullptr;
		next = nullptr;
		_xDir = xDir;
		_yDir = yDir;
		_xPos = xPos;
		_yPos = yPos;
		_shape = sf::CircleShape(10);
		_shape.setFillColor(color);
		_scale = scale;
		
	};

	~Node();

	void updateDirection();
	void updatePosition(float dt, float speed);
	bool distanceToNextNode();

	sf::Vector2f getDirection();
	sf::Vector2f getPosition();
	sf::CircleShape getShape();
	sf::Vector2f getScale();

	void setDirection(sf::Vector2f newDirection);

	Node* prev, * next;
	

private:
	sf::Vector2f* _scale;
	sf::CircleShape _shape;
	float _xDir, _yDir;
	float _xPos, _yPos;

	
};

