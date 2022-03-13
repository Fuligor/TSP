#include <iostream> 

#include "DrawGraph.h"

#include <SFML/Graphics.hpp>

void DrawGraph::showGraph(location* locations, std::shared_ptr <Result> result, std::string algorithmName, std::string filename, int size)
{
    int padding = 10;
    int maximumX = 0;
    int maximumY = 0;
    for (int i = 0; i < size; i++)
    {
        if (locations[i].first > maximumX)
        {
            maximumX = locations[i].first;
        }
        if (locations[i].second > maximumY)
        {
            maximumY = locations[i].second;
        }
    }
    sf::Vector2i windowSize(maximumX+2*padding, maximumY + 2 * padding);
    
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), algorithmName);
    window.clear(sf::Color::White);
    for(int i = 0; i<2;++i)
    {
        int last = -1;
        for (auto j : result->cycle[i])
        {
            if (last != -1)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(locations[last].first + padding, locations[last].second + padding), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(locations[j].first + padding, locations[j].second + padding), sf::Color::Black)
                };

                window.draw(line, 2, sf::Lines);
            }
            last = j;
        }

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(locations[last].first + padding, locations[last].second + padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(locations[result->cycle[i].front()].first + padding, locations[result->cycle[i].front()].second + padding), sf::Color::Black)
        };

        window.draw(line, 2, sf::Lines);
    }
        
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    std::string name = filename + "_" + algorithmName + ".png";
    if (texture.copyToImage().saveToFile(name))
    {
        std::cout << "screenshot saved to " << name << std::endl;
    }
    window.close();
}


