#include "Game.hpp"

Game::Game()
{
    snake = Snake();
}

Game::~Game()
{
}

void Game::start()
{
    window = new RenderWindow(VideoMode(BLOCK_SIZE * 30, BLOCK_SIZE * 30), "Tetris");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);
    snake.start();
    run();
}

void Game::run()
{
    while (window->isOpen())
    {
        draw();
        event_handler();
        snake.run(window);
    }
}

void Game::event_handler()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window->close();
        }
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Down)
            {
                snake.move(Vector2i(0, 1));
            }
            if (event.key.code == Keyboard::Up)
            {
                snake.move(Vector2i(0, -1));
            }
            if (event.key.code == Keyboard::Left)
            {
                snake.move(Vector2i(-1, 0));
            }
            if (event.key.code == Keyboard::Right)
            {
                snake.move(Vector2i(1, 0));
            }
        }
    }
}

void Game::draw()
{
    window->clear(Color::Black);
    snake.draw(window);
    window->display();
}