#ifndef GAME_UI
#define GAME_UI 1
#include <SFML/Graphics.hpp>
#include "Window.hpp"

class GameUi
{
private:
    unsigned int blockSize = 16;
    sf::Font font;

    sf::Text score[2];
    void ConfigureScore();
    
    bool ShowingGameOver;
    sf::Text gameOver[2];
    void ConfigureGameOver();
public:
    GameUi(unsigned int blockSize);
    ~GameUi();
    void SetScore(int points, int lives);
    void ShowGameOver();
    void Draw(Window* window);
    void SetWindowSize(sf::Vector2u windowSize);
    void Reset();
};

#endif