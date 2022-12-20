#pragma once
#include "NetworkManager.h"
#include "Ghost.h"
#include "Pill.h"
class GhostManager
{
public:
	GhostManager();
	~GhostManager();

	void setNetworkManager(NetworkManager* networkManager);


	void init();
	void update(float dt);
	void render(sf::RenderWindow* window);
	void updateGhostData(playerDATA player);
	void addGhost(playerDATA data);
	void unpackData(NetworkType type);
	NetworkManager* _networkManager;

	std::vector<playerDATA*> _playerData;
	std::vector<Ghost*> _ghosts;
	int _playerCount;
};

