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
	DataType rcvDataType;
	int type;
	_networkManager->udpRecievePacket() >> type;

	unpackData(static_cast<DataType>(type));
}

void GhostManager::unpackData(DataType type)
{
	switch (type)
	{
	case DataType::PLAYER:

		break;
	case DataType::PILL:
		break;
	case DataType::TEXT:
		break;
	case DataType::EVENT:
		break;
	case DataType::WORLD:
		break;
	default:
		break;
	}
}