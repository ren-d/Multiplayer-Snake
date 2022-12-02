#include "TileMap.h"

// Constructor sets default position value.
TileMap::TileMap()
{
	position = sf::Vector2f(0, 0);
}

TileMap::~TileMap()
{
}

// Uses window pointer to render level/section. Tile by Tile.
void TileMap::render(sf::RenderWindow* window)
{
	for (int i = 0; i < (int)levelAssets.size(); i++)
	{
		window->draw(levelAssets[i]);
	}
}

// Loads and stores the spritesheet containing all the tiles required to build the level/section
void TileMap::loadTexture(const char* filename)
{
	texture.loadFromFile(filename);
}

// Receives an array of GameObjects representing the tile set (in order)
void TileMap::setTileSet(std::vector<GameObject> ts)
{
	tileSet = ts;
}

// Receives and array of integers and map dimensions representing the map (where and what tiles to place).
void TileMap::setTileMap(std::vector<int> tm, sf::Vector2u _mapDimensions)
{
	tileMap = tm;
	mapDimensions = _mapDimensions;
}

// Once provided with the map and tile set, builds the level, creating an array of tile sprites positioned based on the map. Ready to render.
void TileMap::buildLevel()
{
	if (tileSet.size() > 0 && tileMap.size() > 0)
	{
		int x, y = 0;
		sf::Vector2f tileSize(tileSet[0].getSize().x, tileSet[0].getSize().y);

		for (int i = 0; i < (int)tileMap.size(); i++)
		{
			x = i % mapDimensions.x;
			y = (int)floor(i / mapDimensions.x);
			tileSet[tileMap[i]].setPosition(position.x + (x * tileSize.x), position.y + (y * tileSize.y));
			levelAssets.push_back(tileSet[tileMap[i]]);
			levelAssets[i].setTexture(&texture);
		}
	}
}