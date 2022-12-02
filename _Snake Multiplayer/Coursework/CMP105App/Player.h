#pragma once
#include "Framework/GameObject.h"

#include "Node.h"
#include <iostream>
class Player :
    public GameObject
{
public:
    Player();
    ~Player();

    
    void Init();
    void handleInput(float dt);
    void Render(sf::RenderWindow* window);
    void Grow();
    void Die();
    void update(float dt);

private:
    void addFront(Node* node);
    void addEnd(Node* node);
    void addTailNode();
    void propagateDirections();
    int _size;
    float _speed;
    sf::CircleShape shape;
    sf::Vector2f _pos;
    sf::Vector2f _dir;
    sf::Vector2f mouse;
    Node* _head;
    Node* _end;
};

