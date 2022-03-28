#ifndef GAME_H
#define GAME_H 1
#include "SFML/Graphics.hpp"
#include "Snake.hpp"

using namespace sf;

class Game
{
private:
    RenderWindow * window;
    void run();
    void event_handler();
    void draw();
    Snake snake;
public:
    Game();
    ~Game();
    void start();
};

#endif