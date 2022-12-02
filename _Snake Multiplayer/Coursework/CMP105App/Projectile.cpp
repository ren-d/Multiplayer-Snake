#include "Projectile.h"
Projectile::Projectile()
{

}

Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
	move(velocity * dt);
}

void Projectile::handleInput(float dt)
{

}
