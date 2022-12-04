#include "Pill.h"

Pill::Pill()
{
	setCollisionBox(sf::FloatRect(_shape.getPosition(),
					sf::Vector2f(_shape.getLocalBounds().width,
					_shape.getLocalBounds().height)));
}

Pill::~Pill()
{

}

