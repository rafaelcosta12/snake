#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, std::string title)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    window->setFramerateLimit(60);
}

Window::~Window()
{
    free(window);
}

void Window::Render()
{
    window->display();
    window->clear(sf::Color::Black);
}

bool Window::IsOpen()
{
    return window->isOpen();
}

void Window::Close()
{
    window->close();
}

void Window::Draw(const sf::Drawable& obj)
{
    window->draw(obj);
}

bool Window::PollEvent(sf::Event& event)
{
    bool r = window->pollEvent(event);
    
    if (r && event.type == sf::Event::Closed)
    {
        this->Close();
    }
    
    return r;
}

sf::Vector2u Window::GetSize()
{
    return window->getSize();
}