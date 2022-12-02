#include "ProjectileManager.h"
ProjectileManager::ProjectileManager()
{
	numberOfProjectiles = 0;
	texture = new sf::Texture();
	texture->loadFromFile("gfx/ProjectilePH.png");
	for (int i = 0; i < 5; i++)
	{
		projectiles.push_back(Projectile());
		projectiles[i].setAlive(false);
		projectiles[i].setTexture(texture);
		projectiles[i].setSize(sf::Vector2f(8, 8));
		projectiles[i].setCollisionBox(0, 0, 8, 8);

	}
	
}

ProjectileManager::~ProjectileManager()
{

}
void ProjectileManager::spawn(sf::Vector2f playerPosition)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (!projectiles[i].isAlive())
		{
			sf::Vector2f direction = playerPosition - spawnPoint ;
			direction = VectorHelper::normalise(direction);
			projectiles[i].setAlive(true);
			projectiles[i].setVelocity(direction * 200.0f);
			projectiles[i].setPosition(spawnPoint);
			numberOfProjectiles++;
			break;
		}
	}

}
void ProjectileManager::update(float dt)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].isAlive())
		{
			projectiles[i].update(dt);
		}

	}
	deathCheck();
}

void ProjectileManager::deathCheck()
{

}

void ProjectileManager::render(sf::RenderWindow* window)
{
	for (Projectile& projectile : projectiles)
	{
		if (projectile.isAlive())
		{
			window->draw(projectile);
		}
	}
}