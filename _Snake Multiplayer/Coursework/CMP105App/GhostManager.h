#pragma once
#include "Player.h"
#include "Pill.h"
class GhostManager
{
	GhostManager();
	~GhostManager();

	std::vector<Player> _players;
	std::vector<Pill> _pills;
};

