#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Heroe.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock clock;

        sf::Vector2f position(50, 520);
        Heroe my_heroe(position);
        my_heroe.setSpeed(150);
        my_heroe.setBounds(0, window.getSize().x, 0, window.getSize().y);

        sf::Vector2f size(20.0, 20.0);
        Pocisk my_pocisk(my_heroe,size);
        my_pocisk.setSpeed(150);

        sf::Vector2f size_przeszkoda(20.0, 180.0);
        Przeszkoda my_przeszkoda(size_przeszkoda);
        my_przeszkoda.setSpeed(150);

        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                            std::cout << "End Game" << std::endl;
                            window.close();
                        }
                }
                window.clear(sf::Color::Black);

                sf::Time elapsed = clock.restart();

                        my_heroe.move_heroe(elapsed);
                        my_pocisk.move_pocisk(elapsed);
                        my_przeszkoda.move_przeszkoda(elapsed);

                        window.draw(my_heroe);
                        window.draw(my_pocisk);
                        window.draw(my_przeszkoda);

                window.display();
        }

    return 0;
}
