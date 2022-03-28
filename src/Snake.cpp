#include "Snake.hpp"

Snake::Snake()
{
    body = std::vector<RectangleShape*>();
    move_cooldown = 30;
}

Snake::~Snake()
{

}

void Snake::draw(RenderWindow * window)
{
    for (auto part : body)
    {
        window->draw(*part);
    }

    RectangleShape feed = RectangleShape(Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
    feed.setPosition(feed_position);
    feed.setFillColor(Color::Yellow);
    window->draw(feed);
}

void Snake::run(RenderWindow * window)
{
    if (--move_cooldown > 0) return;
    move_cooldown = 30;

    auto head = body.at(0);
    auto past_pos = head->getPosition();

    head->move(next_move.x * BLOCK_SIZE, next_move.y * BLOCK_SIZE);

    const int limit_w_min = 0;
    const int limit_w_max = 30 * BLOCK_SIZE - BLOCK_SIZE;
    const int limit_h_min = 0;
    const int limit_h_max = 30 * BLOCK_SIZE - BLOCK_SIZE;
    
    if (head->getPosition().x < limit_w_min)
    {
        head->setPosition(limit_w_max, head->getPosition().y);
    }

    if (head->getPosition().x > limit_w_max)
    {
        head->setPosition(limit_w_min, head->getPosition().y);
    }

    if (head->getPosition().y < limit_h_min)
    {
        head->setPosition(head->getPosition().x, limit_h_max);
    }

    if (head->getPosition().y > limit_h_max)
    {
        head->setPosition(head->getPosition().x, limit_h_min);
    }

    if (head->getPosition() == feed_position)
    {
        body.push_back(create_body_piece());
        create_feed();
    }

    Vector2f last = past_pos;
    Vector2f aux;
    for (int i = 1; i < body.size(); i++)
    {
        aux = body.at(i)->getPosition();
        body.at(i)->setPosition(last);
        last = aux;
    }
}

void Snake::start()
{
    body.clear();
    next_move = Vector2i(1, 0);

    auto block = create_body_piece();
    block->setPosition(0, 0);
    body.push_back(block);

    create_feed();
}

void Snake::move(Vector2i direction)
{
    next_move = direction;
    move_cooldown = 0;
}

void Snake::create_feed() {
    feed_position = Vector2f((rand() % 30) * BLOCK_SIZE, (rand() % 30) * BLOCK_SIZE);
}

RectangleShape * Snake::create_body_piece()
{
    RectangleShape * piece = new RectangleShape(Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
    return piece;
}