#include "Pill.h"

Pill::Pill()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(-1500, 1500);
	std::uniform_int_distribution<> distr2(100, 255);
	_shape = sf::CircleShape(5);
	_shape.setPosition(sf::Vector2f(distr(gen), distr(gen)));
	setSize(sf::Vector2f(_shape.getLocalBounds().width, _shape.getLocalBounds().height));
	setPosition(_shape.getPosition());
	std::cout << distr(gen) << std::endl;
	sf::Color pillColor(distr2(gen), distr2(gen), distr2(gen), 255);
	_shape.setFillColor(pillColor);
	if (distr(gen) > 500) {
		_shape.setScale(1.2, 1.2);
		_growthValue = 2;
	}
	else
	{
		_growthValue = 1;
		_shape.setScale(0.8, 0.8);
	}
	setCollisionBox(sf::FloatRect(_shape.getPosition(),
					sf::Vector2f(_shape.getLocalBounds().width,
					_shape.getLocalBounds().height)));
}

Pill::~Pill()
{

}

void Pill::render(sf::RenderWindow* wwindow)
{
	wwindow->draw(_shape);
}

