#ifndef WINDOW_H
#define WINDOW_H 1
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
private:
   sf::RenderWindow* window;
public:
    Window(unsigned int width, unsigned int height, std::string title);
    ~Window();
    void Render();
    bool IsOpen();
    void Close();
    void Draw(const sf::Drawable&);
    bool PollEvent(sf::Event& event);
    sf::Vector2u GetSize();
};

#endif