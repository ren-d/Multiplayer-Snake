#pragma once
#include "Framework/BaseLevel.h"
#include "Framework/Collision.h"
#include "Player.h"
#include "Pill.h"
#include "NetworkManager.h"
#include "GhostManager.h"
class Level :
    BaseLevel
{
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt) override;
    void update(float dt);
    void render();

    NetworkManager* networkManager;
    std::vector<Pill*> pills;
    sf::CircleShape shape;
    Player* player1;
    sf::RectangleShape wall;
    sf::Clock clock;
    bool ponged = false;
    bool sentPlayerData = false;
    GhostManager* ghostManager;
    int cooldown = 0;
    float count, ping;
    std::vector<float> pongs;
    float server_time;
    float global_server_time = 0;
    sf::IpAddress rIp;
    char buffer[100];
    const int MAX_PILLS = 300;
};

