#include <string>
#include "GameUi.hpp"

GameUi::GameUi(unsigned int blockSize)
{
    this->blockSize = blockSize;

    font.loadFromFile("arial.ttf");
    
    Reset();
}

GameUi::~GameUi()
{

}

void GameUi::Reset()
{
    ConfigureScore();
    ConfigureGameOver();
}

void GameUi::ConfigureScore()
{
    for (int i = 0; i < 2; i++)
    {
        score[i].setFont(font);
        score[i].setCharacterSize(blockSize);
        score[i].setFillColor(sf::Color::White);
    }
}

void GameUi::ConfigureGameOver()
{
    ShowingGameOver = false;
    
    gameOver[0].setString("GAME OVER");
    gameOver[1].setString("Press \"Enter\" to restart");

    for (int i = 0; i < 2; i++)
    {
        gameOver[i].setFont(font);
        gameOver[i].setCharacterSize(blockSize);
        gameOver[i].setFillColor(sf::Color::White);        
        sf::FloatRect bounds = gameOver[i].getLocalBounds();
        gameOver[i].setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
    }
}

void GameUi::ShowGameOver()
{
    ShowingGameOver = true;
}

void GameUi::SetScore(int points, int lives)
{
    score[0].setString("POINTS: " + std::to_string(points));
    score[1].setString("LIVES: " + std::to_string(lives));
}

void GameUi::Draw(Window* window)
{
    for (int i = 0; i < 2; i++)
    {
        window->Draw(score[i]);
    }
    if (ShowingGameOver)
    {
        sf::RectangleShape cover(sf::Vector2f(window->GetSize()));
        cover.setFillColor(sf::Color(0, 0, 0, 150));
        window->Draw(cover);
        for (int i = 0; i < 2; i++)
        {
                window->Draw(gameOver[i]);
        }
    }
}

void GameUi::SetWindowSize(sf::Vector2u windowSize)
{
    gameOver[0].setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
    gameOver[1].setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + blockSize));
    
    score[0].setPosition(sf::Vector2f(blockSize, blockSize * 0.5f));
    score[1].setPosition(sf::Vector2f(blockSize, blockSize * 1.5f));
}