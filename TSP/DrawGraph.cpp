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
    
    sf::RenderTexture window;
    window.create(windowSize.x, windowSize.y);
    window.clear(sf::Color::White);
    for (int i = 0; i < size; i++)
    {
    

        sf::CircleShape circle;
        circle.setRadius(5);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(locations[i].first + padding - 5, locations[i].second + padding - 5);
        window.draw(circle);
    }

    sf::Color colors[] = { sf::Color::Blue, sf::Color::Red };

    for(int i = 0; i<2;++i)
    {
        int last = -1;
        for (auto j : result->cycle[i])
        {
            if (last != -1)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(locations[last].first + padding, locations[last].second + padding), colors[i]),
                    sf::Vertex(sf::Vector2f(locations[j].first + padding, locations[j].second + padding), colors[i])
                };
                
                window.draw(line, 2, sf::Lines);
            }
            last = j;
            
        }

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(locations[last].first + padding, locations[last].second + padding), colors[i]),
            sf::Vertex(sf::Vector2f(locations[result->cycle[i].front()].first + padding, locations[result->cycle[i].front()].second + padding), colors[i])
        };

        window.draw(line, 2, sf::Lines);
    }
        
    sf::Texture texture = window.getTexture();

    std::string name = "Results/" + filename + "_" + algorithmName + ".png";
    if (texture.copyToImage().saveToFile(name))
    {
        std::cout << "screenshot saved to " << name << std::endl;
    }

}


