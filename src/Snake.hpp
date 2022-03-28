#ifndef SNAKE_H
#define SNAKE_H 1

#define BLOCK_SIZE 20

#include "SFML/Graphics.hpp"
#include "vector"

using namespace sf;

class Snake
{
private:
    std::vector<RectangleShape*> body;
    int move_cooldown;
    Vector2i next_move;
    Vector2f feed_position;
    RectangleShape * create_body_piece();
public:
    Snake();
    ~Snake();
    void draw(RenderWindow * window);
    void run(RenderWindow * window);
    void start();
    void move(Vector2i direction);
    void create_feed();
};

#endif