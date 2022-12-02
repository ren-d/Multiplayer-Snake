#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	
}

Level::~Level()
{

}

void Level::handleInput(float dt)
{

}

void Level::render()
{
	beginDraw();

	endDraw();
}

void Level::update(float dt)
{
	window->clear(sf::Color(155, 0, 0, 255));
}