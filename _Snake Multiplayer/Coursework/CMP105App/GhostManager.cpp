#include "GhostManager.h"
GhostManager::GhostManager()
{

}

GhostManager::~GhostManager()
{

}

void GhostManager::setNetworkManager(NetworkManager* networkManager)
{
	_networkManager = networkManager;
}

void GhostManager::update(float dt)
{
	for (Ghost* ghost : _ghosts)
	{
		for (playerDATA* data : _playerData)
		{
			if (ghost->getPlayerData().id == data->id)
			{
		
				ghost->updatePlayerData(*data);
			}
		}

		ghost->update(dt);
	}
}

void GhostManager::updateGhostData(playerDATA player)
{
	
	for (playerDATA* data : _playerData)
	{
		if (data->id == player.id)
		{
			
			data->dirX = player.dirX;
			data->dirY = player.dirY;
			data->speed = player.speed;
			data->size = player.size;

			
		}
	}
}

void GhostManager::render(sf::RenderWindow* window)
{
	for (Ghost* ghost : _ghosts)
	{
		ghost->Render(window);
	}
}

void GhostManager::addGhost(playerDATA data)
{
	std::cout << "id: " << data.id << std::endl;

	if (data.id > _ghosts.size())
	{
		_ghosts.push_back(new Ghost(data));
		_playerData.push_back(&data);
	}
	
}