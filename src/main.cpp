#include <SFML/Graphics.hpp>
#include "World.hpp"

int main()
{
    World game = World();
    while (game.IsOpen())
    {
        game.EventHandle();
        game.Update();
        game.Render();
    }
}
