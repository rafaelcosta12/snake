#include <string>
#include <random>
#include "World.hpp"

World::World()
{
    gameArea.top = block_size * 4;
    gameArea.left = block_size * 2;
    gameArea.height = block_size * heigth;
    gameArea.width = block_size * width;
    wall_size = block_size * 0.5f;
    game_over = false;

    window = new Window(
        gameArea.width + wall_size * 4 + block_size * 2,
        gameArea.height + wall_size * 4 + block_size * 4,
        "Snake");
    ui = new GameUi(block_size);
    ui->SetWindowSize(window->GetSize());

    snake = new Snake(block_size, sf::Vector2i(width * 0.5f, heigth * 0.5f));
    speed = 5;

    apple.setFillColor(sf::Color::Green);
    apple.setRadius(block_size / 2);
    apple.setOrigin(block_size / 2, block_size / 2);
    
    CreateWalls();
    RespawnApple();
}

World::~World()
{
    free(window);
    free(snake);
    free(ui);
}

void World::EventHandle()
{
    sf::Event event;
    while (window->PollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Down)
            {
                snake->SetDirection(SnakeMove::Down);
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                snake->SetDirection(SnakeMove::Up);
            }
            if (event.key.code == sf::Keyboard::Left)
            {
                snake->SetDirection(SnakeMove::Left);
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                snake->SetDirection(SnakeMove::Right);
            }
            if (game_over && event.key.code == sf::Keyboard::Enter)
            {
                snake->Reset();
                ui->Reset();
            }
        }
    }
}

void World::Update()
{
    if (speed == 0) { return; }
    float frametime = 1.0f / 60.0f + 1.0f / speed;

    elapsed += clock.restart();
    if (elapsed.asSeconds() < frametime) { return; }
    elapsed -= sf::seconds(frametime);
    
    snake->Update();
    
    if (snake->GetLives() == 0)
    {
        GameOver();
    }
    else
    {
        CheckCollision();
    }

    ui->SetScore(snake->GetPoints(), snake->GetLives());
}

void World::Render()
{
    for (int i = 0; i < 4; i++)
    {
        window->Draw(wall[i]);
    }
    snake->Render(window, gameArea);
    window->Draw(apple);
    ui->Draw(window);
    window->Render();
}

bool World::IsOpen()
{
    return window->IsOpen();
}

void World::CreateWalls()
{
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f origin;

    for (int i = 0; i < 4; i++)
    {
        if (i < 2)
        {
            size.x = (width + 2) * block_size;
            size.y = wall_size;
            origin.x = size.x / 2;
            position.x = gameArea.left + gameArea.width / 2;
            position.y = gameArea.top;

            if (((i + 1) % 2) == 0)
            {
                origin.y = size.y;
                position.y -= size.y;
            }
            else
            {
                origin.y = 0;
                position.y += gameArea.height + size.y;
            }
        }
        else
        {
            size.x = wall_size;
            size.y = (heigth + 2) * block_size;
            origin.y = size.y / 2;
            position.y = gameArea.top + gameArea.height / 2;
            position.x = gameArea.left;

            if (((i + 1) % 2) == 0)
            {
                origin.x = size.x;
                position.x += -size.x;
            }
            else
            {
                origin.x = 0;
                position.x += gameArea.width + size.x;
            }
        }
        wall[i].setFillColor(sf::Color::Red);
        wall[i].setSize(size);
        wall[i].setOrigin(origin);
        wall[i].setPosition(position);
    }
}

void World::RespawnApple()
{
    int max_x = width - 1;
    int max_y = heigth - 1;
    
    apple_position.x = rand() % max_x + 1;
    apple_position.y = rand() % max_y + 1;
    apple.setPosition(
        gameArea.left + apple_position.x * block_size,
        gameArea.top + apple_position.y * block_size);
}

void World::CheckCollision()
{
    sf::Vector2f head = snake->GetPosition();
    SnakeMove move = snake->GetMove();
    
    if ((head.x == 0 && move == SnakeMove::Left) ||
        (head.x == width && move == SnakeMove::Right) ||
        (head.y == 0 && move == SnakeMove::Up) ||
        (head.y == heigth && move == SnakeMove::Down))
        GameOver();
    if (snake->GetPosition() == apple_position)
    {
        snake->Grow();
        RespawnApple();
        speed += 1;
    }
}

void World::GameOver()
{
    speed = 5;
    game_over = true;
    snake->Lose();
    ui->ShowGameOver();
}
