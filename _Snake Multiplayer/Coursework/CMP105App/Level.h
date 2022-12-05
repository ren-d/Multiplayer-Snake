#pragma once
#include "Framework/BaseLevel.h"
#include "Framework/Collision.h"
#include "Player.h"
#include "Pill.h"
class Level :
    BaseLevel
{
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt) override;
    void update(float dt);
    void render();

    std::vector<Pill*> pills;
    sf::CircleShape shape;
    Player* player1;
    sf::RectangleShape wall;

    const int MAX_PILLS = 300;
};

