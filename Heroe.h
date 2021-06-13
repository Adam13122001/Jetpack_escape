#ifndef HEROE_H
#define HEROE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class RuchomySprite: public sf::Sprite{
protected:
    sf::Texture texture;
    int speed_x = 0;
    int speed_y = 0;
public:
    void setSpeed(int x, int y){
        speed_x=x;
        speed_y=y;
    }
    void move_sprite(const sf::Time &elapsed){
        move(-1*speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());
        sf::FloatRect bounds = getGlobalBounds();
        if(bounds.left<=2){
            pojaw();
        }
    }
    void pojaw(){
        setPosition(799,rand()%540);
        speed_x*=1.01;
        speed_y*=1.01;
    }
};

class Heroe : public RuchomySprite{
public:
    Heroe(sf::Vector2f &position):RuchomySprite(){setPosition(position);
                                    if (!texture.loadFromFile("jetpack.png")) {
                                    std::cerr << "Could not load texture" << std::endl;}
                                    setTexture(texture);
                                    setScale(0.06,0.06);
                                    }
    void move_sprite(const sf::Time &elapsed){
            sf::FloatRect bounds = getGlobalBounds();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if(bounds.top>top_){
                        move(0,-(speed_y*elapsed.asSeconds()));
                    }
                }
                else{
                    if(bounds.top<down_-bounds.height){
                        move(0,0.8*speed_y*elapsed.asSeconds());
                    }
                }

    }
    void setBounds(int left, int right, int top, int down){
    top_=top;
    down_=down;
    left_=left;
    right_=right;
    }

    void zarobek(int hajsiwo){
        kasa+=hajsiwo;
        if(kasa%100==0){
            speed_y*=1.1;
        }
        std::cout<<kasa<<std::endl;
    }
private:

    int top_;
    int down_;
    int left_;
    int right_; 

    int kasa=0;

};



class Pocisk : public RuchomySprite{
public:
    Pocisk():RuchomySprite(){
        setPosition(rand()%200 + 400,rand()%560);
        if (!texture.loadFromFile("bullet.png")) {
        std::cerr << "Could not load texture" << std::endl;}
        setTexture(texture);
        setScale(0.2,0.2);
        setSpeed(200,0);
    }
};



class Przeszkoda : public sf::RectangleShape{
    int speed = 0;
public:
    Przeszkoda(sf::Vector2f &size):sf::RectangleShape(size){
        setPosition(rand()%400 + 300,rand()%560);
        setFillColor(sf::Color(100, 50, 250));
        setSpeed(150);
    }
    void setSpeed(int y){
        speed=y;
    }
    void move_przeszkoda(const sf::Time &elapsed){
        move(-1*speed*elapsed.asSeconds(),0);
        sf::FloatRect bounds = getGlobalBounds();
        if(bounds.left<=2){
            pojaw_przeszkode();
        }
    }
    void pojaw_przeszkode(){
        setPosition(799,rand()%540);
    }
};



class Coin : public RuchomySprite{
public:
    Coin():RuchomySprite(){setPosition(600,rand()%600);
                                    if (!texture.loadFromFile("coin.png")) {
                                    std::cerr << "Could not load texture" << std::endl;}
                                    setTexture(texture);
                                    setScale(0.1,0.1);
                                    setSpeed(150,0);
                                    }
};

#endif // HEROE_H
