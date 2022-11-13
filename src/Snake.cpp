#include "Snake.hpp"

SnakeSegment::SnakeSegment(sf::Vector2f position)
{
    this->position = position;
}

void SnakeSegment::SetPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f SnakeSegment::GetPosition()
{
    return position;
}

Snake::Snake(unsigned int block_size, sf::Vector2i initial_position)
{
    this->block_size = block_size;
    this->initial_position = initial_position;
    Reset();
}

Snake::~Snake()
{

}

void Snake::Update()
{
    if (move == SnakeMove::None) { return; }
    if (!alive) { return; }
    
    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i].SetPosition(body[i - 1].GetPosition());
    }

    sf::Vector2f step = body[0].GetPosition();
    if (move == SnakeMove::Right)
    {
        step.x += 1;
    }
    if (move == SnakeMove::Left)
    {
        step.x -= 1;
    }
    if (move == SnakeMove::Up)
    {
        step.y -= 1;
    }
    if (move == SnakeMove::Down)
    {
        step.y += 1;
    }
    body[0].SetPosition(step);
    CheckCollision();
}

void Snake::Render(Window* window, sf::IntRect screen)
{
    sf::RectangleShape piece(sf::Vector2f(block_size - 1, block_size - 1));
    piece.setOrigin(sf::Vector2f(block_size / 2, block_size / 2));
    piece.setFillColor(sf::Color::Yellow);
    piece.setPosition(sf::Vector2f(
        body[0].GetPosition().x * block_size + screen.left,
        body[0].GetPosition().y * block_size + screen.top));
    window->Draw(piece);

    piece.setFillColor(sf::Color::White);
    for (int i = 1; i < body.size(); i++)
    {
        piece.setPosition(sf::Vector2f(
            body[i].GetPosition().x * block_size + screen.left,
            body[i].GetPosition().y * block_size + screen.top));
        window->Draw(piece);
    }
}

void Snake::Reset()
{
    alive = true;
    lives = 3;
    move = SnakeMove::None;
    points = 0;
    body.clear();
    for (int i = -1; i < 2; i++)
    {
        body.push_back(SnakeSegment(sf::Vector2f(initial_position.x + i, initial_position.y)));
    }
}

void Snake::Grow()
{
    sf::Vector2f new_tail;
    points += 1;
    
    if (body.size() > 1)
    {
        sf::Vector2f tail_head = body[body.size() - 1].GetPosition();
        sf::Vector2f tail_bone = body[body.size() - 2].GetPosition();
        new_tail = sf::Vector2f(tail_head.x, tail_head.y);

        if (tail_head.x == tail_bone.x)
        {
            if (tail_head.y > tail_bone.y) { new_tail.y += 1; }
            else { new_tail.y -= 1; }
        }
        else
        if (tail_head.y == tail_bone.y)
        {
            if (tail_head.x > tail_bone.x) { new_tail.x += 1; }
            else { new_tail.x -= 1; }
        }
    }
    else
    {
        new_tail = body[0].GetPosition();
        if (move == SnakeMove::Left)
        {
            new_tail.x += 1;
        }
        else
        if (move == SnakeMove::Right)
        {
            new_tail.x += -1;
        }
        else
        if (move == SnakeMove::Up)
        {
            new_tail.y += 1;
        }
        else
        if (move == SnakeMove::Up)
        {
            new_tail.y += -1;
        }
    }
    body.push_back(SnakeSegment(new_tail));
}

void Snake::Lose()
{
    this->alive = false;
    this->lives = 0;
}

void Snake::SetDirection(SnakeMove move)
{
    this->move = move;
}

sf::Vector2f Snake::GetPosition()
{
    return body[0].GetPosition();
}

void Snake::CheckCollision()
{
    if (body.size() == 1) { return; }
    SnakeSegment head = body[0];
    for (int i = 1; i < body.size(); i++)
    {
        if (head.GetPosition() == body[i].GetPosition())
        {
            Cut(i - 1);
            return;
        }
    }
}

void Snake::Cut(int on_index)
{
    lives -= 1;
    if (lives == 0) { Lose(); }
    while (body.size() > on_index)
    {
        body.pop_back();
    }
}

SnakeMove Snake::GetMove()
{
    return move;
}

unsigned int Snake::GetLives()
{
    return lives;
}

unsigned int Snake::GetPoints()
{
    return points;
}