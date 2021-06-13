#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Heroe.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::vector<std::unique_ptr<RuchomySprite>> pociski_i_coinsy;

    for(int i=0;i<2;i++){
        pociski_i_coinsy.emplace_back(std::make_unique<Pocisk>());
    }
    for(int i=0;i<3;i++){
        pociski_i_coinsy.emplace_back(std::make_unique<Coin>());
    }

    std::vector<std::unique_ptr<Przeszkoda>> przeszkody;

    sf::Vector2f size_przeszkoda(20.0, 140.0);

    for(int i=0;i<3;i++){
        przeszkody.emplace_back(std::make_unique<Przeszkoda>(size_przeszkoda));
    }

    sf::Clock clock;

        sf::Vector2f position(50, 520);
        Heroe my_heroe(position);
        my_heroe.setSpeed(0,150);
        my_heroe.setBounds(0, window.getSize().x, 0, window.getSize().y);


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

                        my_heroe.move_sprite(elapsed);

                        for(auto &p : przeszkody) {
                                p->move_przeszkoda(elapsed);
                            }

                        for(auto &pic : pociski_i_coinsy) {
                                pic->move_sprite(elapsed);
                            }

                        int i=0;
                        for(auto &pic : pociski_i_coinsy) {
                                if(pic->getGlobalBounds().intersects(my_heroe.getGlobalBounds())){
                                    Pocisk* pocisk = dynamic_cast<Pocisk *>(pociski_i_coinsy[i].get());
                                    if(pocisk != nullptr){
                                        std::cout << "End Game. You Lose." << std::endl;
                                        window.close();

                                    }
                                    Coin* coin = dynamic_cast<Coin *>(pociski_i_coinsy[i].get());
                                    if(coin != nullptr){
                                        pic->pojaw();
                                        my_heroe.zarobek(2);
                                    }
                                }
                                i++;
                            }

                        i=0;
                        for(auto &pic : przeszkody) {
                                if(pic->getGlobalBounds().intersects(my_heroe.getGlobalBounds())){
                                        std::cout << "End Game. You Lose." << std::endl;
                                        window.close();
                                }
                                i++;
                            }

                        for(auto &pic : pociski_i_coinsy) {
                                window.draw(*pic);
                            }
                        for(auto &p : przeszkody) {
                                window.draw(*p);
                            }


                        window.draw(my_heroe);

                window.display();
        }

    return 0;
}
