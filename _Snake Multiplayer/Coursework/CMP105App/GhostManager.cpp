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

void GhostManager::update(float dt, float ping)
{

	for (Ghost* ghost : _ghosts)
	{

		for (playerDATA* data : _playerData)
		{

			if (ghost->getPlayerData().id == data->id)
			{

				ghost->updatePlayerData(*data, ping);
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

void GhostManager::removeGhost(int id)
{
	for(int i =0; i < _ghosts.size(); i++)
	{
		if (id == _ghosts[i]->getPlayerData().id)
		{
			_ghosts.erase(_ghosts.begin() + i);
			break;
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
	bool duplicate = false;

	for (Ghost* ghost : _ghosts)
	{
		if (data.id == ghost->getPlayerData().id)
		{
			duplicate = true;
			break;
		}
	}

	if (duplicate == false)
	{
		if (data.id > _ghosts.size())
		{
			_ghosts.push_back(new Ghost(data));
			_playerData.push_back(new playerDATA(data));
		}
	}
	
	
}