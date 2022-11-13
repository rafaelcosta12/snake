#ifndef SNAKE_H
#define SNAKE_H 1
#include <vector>
#include <SFML/Graphics.hpp>
#include "Window.hpp"

class SnakeSegment
{
private:
    sf::Vector2f position;
public:
    SnakeSegment(sf::Vector2f);
    void SetPosition(sf::Vector2f);
    sf::Vector2f GetPosition();
};

using SnakeContainer = std::vector<SnakeSegment>;

enum SnakeMove { None, Up, Right, Down, Left };

class Snake
{
private:
    SnakeMove move;
    SnakeContainer body;
    bool alive;
    unsigned int block_size;
    unsigned int lives;
    unsigned int points;
    sf::Vector2i initial_position;
    void CheckCollision();
    void Cut(int);
public:
    Snake(unsigned int, sf::Vector2i);
    ~Snake();
    void Update();
    void Render(Window*, sf::IntRect);
    void Reset();
    void Grow();
    void Lose();
    void SetDirection(SnakeMove);
    sf::Vector2f GetPosition();
    SnakeMove GetMove();
    unsigned int GetLives();
    unsigned int GetPoints();
};

#endif