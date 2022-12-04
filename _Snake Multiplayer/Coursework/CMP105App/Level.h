#pragma once
#include "Framework/BaseLevel.h"
#include "Player.h"
class Level :
    BaseLevel
{
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt) override;
    void update(float dt);
    void render();

    sf::CircleShape shape;
    Player* player1;
    sf::RectangleShape wall;
};

