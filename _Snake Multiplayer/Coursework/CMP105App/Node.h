#pragma once

class Node
{

public:
	Node* prev, *next;

	Node();
	Node(int xDir, int yDir, int xPos, int yPos) {
		prev = nullptr;
		next = nullptr;
		_xDir = xDir;
		_yDir = yDir;
		_xPos = xPos;
		_yPos = yPos;
	};

	~Node();

	void updateDirection();
	void updatePosition();
	int _xDir, _yDir;
	int _xPos, _yPos;
	
};

