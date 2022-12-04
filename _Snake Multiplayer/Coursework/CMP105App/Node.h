#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "Framework/VectorHelper.h"

class Node
{

public:
	Node* prev, *next;
	sf::CircleShape shape;
	Node();
	Node(float xDir, float yDir, float xPos, float yPos, sf::Color color) {
		prev = nullptr;
		next = nullptr;
		_xDir = xDir;
		_yDir = yDir;
		_xPos = xPos;
		_yPos = yPos;
		shape = sf::CircleShape(10);
		shape.setFillColor(color);
	};

	~Node();

	void updateDirection();
	void updatePosition(float dt, float speed);
	bool distanceToNextNode();
	float _xDir, _yDir;
	float _xPos, _yPos;
	float _yVel, _xVel;
	
};

