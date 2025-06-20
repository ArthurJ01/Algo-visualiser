#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "headers/initialize.hpp"
#include "headers/stepStruct.hpp"
#include "headers/sortingVisualiser.hpp"
#include "headers/button.hpp"

enum class Windows {menu, sorting, graph};
extern const sf::Font font("C:/Windows/fonts/arial.ttf");

int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    sf::Vector2f buttonSize = {200.f, 100.f};
    Button insertionSortButton(buttonSize, {100.f, 50.f}, "insertion sort");
    Button mergeSortButton(buttonSize, {100.f, 200.f}, "merge sort");
    Button graphButton(buttonSize, {400.f, 50.f}, "Graph builder");

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        switch (currentWindow){
            case Windows::menu: {
                window.clear(sf::Color(100,100,100));

                sf::Text text(font); // a font is required to make a text object
                text.setString("menu ");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::insertionSort;
                }
                if(mergeSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::mergeSort;
                }
                if(graphButton.clicked(mouse_position)){
                    currentWindow = Windows::graph;
                }

                window.draw(insertionSortButton);
                window.draw(mergeSortButton);
                window.draw(graphButton);
                window.draw(text);
                window.display();

                break;
            }

            case Windows::graph:{

                bool wantToExit = false;

                while(!wantToExit && window.isOpen()){

                    window.clear({0,0,0});

                    while (const std::optional event = window.pollEvent()){
                        if(event->is<sf::Event::Closed>()){
                            window.close();
                        }
                        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                        {
                            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                                wantToExit = true;
                            }
                        }
                    }
                    window.display();
                }
                currentWindow = Windows::menu;
                break;
            }

            case Windows::sorting: {
                //run sorting algo and when it is done, go back to menu
                runSortAlgo(window, algoToRun);
                currentWindow = Windows::menu;
                break;
            }

        }
    }
}

