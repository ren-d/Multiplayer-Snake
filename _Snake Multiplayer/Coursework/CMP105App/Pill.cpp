#include "Pill.h"

Pill::Pill()
{

}
Pill::Pill(pillDATA data)
{
	_data = data;
	init();
}

Pill::~Pill()
{

}

void Pill::init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr2(100, 255);

	_shape = sf::CircleShape(5);
	_shape.setPosition(sf::Vector2f(_data.x, _data.y));
	setSize(sf::Vector2f(_shape.getLocalBounds().width, _shape.getLocalBounds().height));
	setPosition(_shape.getPosition());

	sf::Color pillColor(distr2(gen), distr2(gen), distr2(gen), 255);
	_shape.setFillColor(pillColor);
	
	_growthValue = _data.growthValue;

	if (_growthValue == 1)
	{
		_shape.setScale(sf::Vector2f(0.7, 0.7));
	}
	setCollisionBox(sf::FloatRect(_shape.getPosition(),
		sf::Vector2f(_shape.getLocalBounds().width,
			_shape.getLocalBounds().height)));
}

void Pill::render(sf::RenderWindow* wwindow)
{
	wwindow->draw(_shape);
}

