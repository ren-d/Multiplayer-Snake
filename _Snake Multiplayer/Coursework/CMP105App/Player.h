#pragma once
#include "Framework/GameObject.h"
#include "SFML/Network.hpp"
#include "Node.h"
#include <iostream>



struct playerDATA
{

    char name[4];
    int id,
        speed,
        posX, posY,
        dirX, dirY;
};

class Player :
    public GameObject
{
public:
    Player(sf::Vector2f newPosition);
    ~Player();

    
    void Init();
    void handleInput(float dt);
    void Render(sf::RenderWindow* window);
    void Grow(int growth);
    void Shrink();
    void Die();
    void update(float dt);
    sf::Vector2f getHeadPosition();
    playerDATA getPlayerData();

    bool outOfBounds = false;

private:
    void addFront(Node* node);
    void addEnd(Node* node);
    void addTailNode();
    float _counter, _outOfBoundsCounter, _size, _speed;
    sf::Color _bodyColor, _headColor;
    sf::Vector2f _scale;
    sf::Vector2f _screenCenter;
    sf::Vector2f _mouseDirectionVector;
    playerDATA _playerData;
    Node* _head, *_end;
    
    
   

};

