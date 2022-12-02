#pragma once
#include <iostream>
#include "Projectile.h"
#include "Framework/VectorHelper.h"
class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void spawn(sf::Vector2f playerPosition);
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);
	void setSpawnPoint(sf::Vector2f point) { spawnPoint = point; }
private:
	std::vector<Projectile> projectiles;
	sf::Vector2f spawnPoint;
	sf::Texture* texture;
	int numberOfProjectiles;
};

