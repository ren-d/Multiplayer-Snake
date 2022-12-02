#pragma once
#include "Framework/GameObject.h"
#include "Node.h"
class Player :
    public GameObject
{
public:
    Player();
    ~Player();

    
    void Init();
    void handleInput(float dt);
    void Render();
    void Grow();
    void Die();
    void update(float dt);

private:
    void addFront(Node* node);
    void addEnd(Node* node);
    void addTailNode();
    void propagateDirections();
    int _size;
    sf::Vector2f _pos;
    sf::Vector2f _dir;
    Node* _head;
    Node* _end;
};

