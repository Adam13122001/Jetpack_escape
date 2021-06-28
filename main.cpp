#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Heroe.h"
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::SoundBuffer music;

    music.loadFromFile("Wilki_Bohema.wav");
    sf::Sound sound;
    sound.setBuffer(music);
    sound.setLoop(true);
    sound.play();

    bool end_game = false;

    sf::Sprite background;
    sf::Texture texture_background;
    if (!texture_background.loadFromFile("background.png")) {
    std::cerr << "Could not load texture" << std::endl;}
    background.setTexture(texture_background);

    std::vector<std::unique_ptr<RuchomySprite>> pociski_i_coinsy;

    for(int i=0;i<2;i++){
        pociski_i_coinsy.emplace_back(std::make_unique<Pocisk>());
    }
    for(int i=0;i<3;i++){
        pociski_i_coinsy.emplace_back(std::make_unique<Coin>());
    }
    for(int i=0;i<1;i++){
        pociski_i_coinsy.emplace_back(std::make_unique<Bonus>());
    }

    std::vector<std::unique_ptr<Przeszkoda>> przeszkody;

    sf::Vector2f size_przeszkoda(20.0, 100.0);

    for(int i=0;i<4;i++){
        przeszkody.emplace_back(std::make_unique<Przeszkoda>(size_przeszkoda));
    }

    sf::Clock clock;

        sf::Vector2f position(50, 520);
        Heroe my_heroe(position);
        my_heroe.setSpeed(0,200);
        my_heroe.setBounds(0, window.getSize().x, 0, window.getSize().y);

        sf::Font font;
        font.loadFromFile("czocionka_pkt.ttf");


        while (window.isOpen()) {

            int s = my_heroe.punty();
            string pkt = "Score: " + std::to_string(s);
            sf::Text text(pkt,font);
            text.setPosition(700,0);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(18);

            int z = my_heroe.zycie_();
            string live = "Live: " + std::to_string(z);
            sf::Text text_l(live,font);
            text_l.setPosition(10,0);
            text_l.setFillColor(sf::Color::Black);
            text_l.setCharacterSize(18);

            int a = my_heroe.punty();
            string pkt_k = "You're Score: " + std::to_string(a);
            sf::Text text_wynik(pkt_k,font);
            text_wynik.setPosition(220,250);
            text_wynik.setFillColor(sf::Color::Black);
            text_wynik.setCharacterSize(50);

            sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                            std::cout << "End Game" << std::endl;
                            window.close();
                        }
                }

                if(end_game){
                    window.draw(text_wynik);
                    window.display();
                    sf::sleep(sf::milliseconds(1000));
                    window.close();
                    std::cout << "End Game. You Lose." << std::endl;
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

                        window.draw(background);


                        for(auto &pic : pociski_i_coinsy) {
                                window.draw(*pic);
                            }
                        for(auto &p : przeszkody) {
                                window.draw(*p);
                            }


                        window.draw(my_heroe);
                        window.draw(text);
                        window.draw(text_l);

                        int i=0;
                        for(auto &pic : pociski_i_coinsy) {
                                if(pic->getGlobalBounds().intersects(my_heroe.getGlobalBounds())){
                                    Pocisk* pocisk = dynamic_cast<Pocisk *>(pociski_i_coinsy[i].get());
                                    if(pocisk != nullptr){
                                        pic->pojaw();
                                        my_heroe.smierc(1);
                                    }
                                    Coin* coin = dynamic_cast<Coin *>(pociski_i_coinsy[i].get());
                                    if(coin != nullptr){
                                        pic->pojaw();
                                        my_heroe.zarobek(2);
                                    }
                                    Bonus* bonus = dynamic_cast<Bonus *>(pociski_i_coinsy[i].get());
                                    if(bonus != nullptr){
                                        pic->pojaw();
                                        my_heroe.leczenie(1);
                                    }
                                    if(my_heroe.zycie_()<=0){
                                        end_game=true;
                                    }
                                }
                                i++;
                            }

                        i=0;
                        for(auto &pic : przeszkody) {
                                if(pic->getGlobalBounds().intersects(my_heroe.getGlobalBounds())){
                                   pic->pojaw_przeszkode();
                                   my_heroe.smierc(1);
                                   if(my_heroe.zycie_()<=0){
                                       end_game=true;
                                   }
                                }
                                i++;
                            }

                window.display();
        }

    return 0;
}
