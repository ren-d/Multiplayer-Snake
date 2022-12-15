#pragma once
#include "Player.h"
#include "Pill.h"
class GhostManager
{
public:
	GhostManager();
	~GhostManager();

	std::vector<Player> _players;
	std::vector<Pill> _pills;

	void update(float dt);
	void render(sf::RenderWindow window);
};

