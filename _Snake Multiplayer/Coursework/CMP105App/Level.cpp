#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	shape = sf::CircleShape(10);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	player1 = new Player(sf::Vector2f(window->getView().getSize().x / 2, window->getView().getSize().y / 2));
	player1->setInput(in);
	sf::View* view = new sf::View(player1->getHeadPosition(), window->getView().getSize());

}

Level::~Level()
{

}

void Level::handleInput(float dt)
{
	player1->handleInput(dt);
}

void Level::render()
{
	beginDraw();
	player1->Render(window);

	endDraw();
}

void Level::update(float dt)
{
	sf::View view = sf::View(player1->getHeadPosition(), window->getView().getSize());
	window->setView(view);
	window->clear(sf::Color(155, 0, 0, 255));
	player1->update(dt);
}