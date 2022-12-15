#pragma once
#include "NetworkManager.h"
#include "Player.h"
#include "Pill.h"
class GhostManager
{
public:
	GhostManager();
	~GhostManager();

	void setNetworkManager(NetworkManager* networkManager);


	void init();
	void update(float dt);
	void render(sf::RenderWindow window);

	void unpackData(DataType type);
	NetworkManager* _networkManager;

	int _playerCount;
};

