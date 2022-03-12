#ifndef _DEBUG

#include "DrawGraph.h"

#include <SFML/Graphics.hpp>

void DrawGraph::showGraph(location* locations, std::shared_ptr <Result> result)
{
    sf::Vector2i windowSize(800, 800);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for(int i = 0; i<2;++i)
        {

            for (auto j : result->cycle[i])
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(10.f, 10.f)),
                    sf::Vertex(sf::Vector2f(150.f, 150.f))
                };

                window.draw(line, 2, sf::Lines);
            }
        }
        

        window.display();
    }
   
}

#endif // !_DEBUG
