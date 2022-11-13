#ifndef WORLD_H
#define WORLD_H 1

#include "Window.hpp"
#include "Snake.hpp"
#include "GameUi.hpp"

using Apple = sf::CircleShape;

class World
{
private:
    const unsigned int block_size = 16;
    unsigned int wall_size;
    sf::IntRect gameArea;
    unsigned int width = 20;
    unsigned int heigth = 25;
    bool game_over;

    Window* window;
    Snake* snake;
    GameUi* ui;
    
    sf::Font font;
    sf::Text text[4];

    int speed;
    sf::Clock clock;
    sf::Time elapsed;

    sf::RectangleShape wall[4];
    void CreateWalls();

    Apple apple;
    sf::Vector2f apple_position;
    void RespawnApple();

    void CheckCollision();
    void GameOver();
public:
    World();
    ~World();
    void EventHandle();
    void Update();
    void Render();
    bool IsOpen();
};

#endif