#ifndef HEROE_H
#define HEROE_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Heroe : public sf::Sprite{
public:
    Heroe(sf::Vector2f &position):Sprite(){setPosition(position);
                                    if (!texture.loadFromFile("guy.png")) {
                                    std::cerr << "Could not load texture" << std::endl;}
                                    setTexture(texture);
                                    }
    void setSpeed(int y){
        speed_y_=y;
    }
    void move_heroe(const sf::Time &elapsed){
            sf::FloatRect rectangle_bounds = getGlobalBounds();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if(rectangle_bounds.top>top_){
                        move(0,-(speed_y_*elapsed.asSeconds()));
                    }
                }
                else{
                    if(rectangle_bounds.top<down_-rectangle_bounds.height){
                        move(0,0.8*speed_y_*elapsed.asSeconds());
                    }
                }

    }
    void setBounds(int left, int right, int top, int down){
    top_=top;
    down_=down;
    left_=left;
    right_=right;
    }
private:
    int speed_y_ = 0;

    int top_;
    int down_;
    int left_;
    int right_;

    sf::Texture texture;
};



class Pocisk : public sf::RectangleShape{
    int speed = 0;
public:
    Pocisk(Heroe bohater,sf::Vector2f &size):sf::RectangleShape(size){
        sf::FloatRect heroe_bounds = bohater.getGlobalBounds();
        setPosition(799,heroe_bounds.top);
        setFillColor(sf::Color(100, 50, 250));
    }
    void setSpeed(int y){
        speed=y;
    }
    void move_pocisk(const sf::Time &elapsed){
        move(-1*speed*elapsed.asSeconds(),0);
    }
};



class Przeszkoda : public sf::RectangleShape{
    int speed = 0;
public:
    Przeszkoda(sf::Vector2f &size):sf::RectangleShape(size){
        setPosition(780,rand()%600);
        setFillColor(sf::Color(100, 50, 250));
    }
    void setSpeed(int y){
        speed=y;
    }
    void move_przeszkoda(const sf::Time &elapsed){
        move(-1*speed*elapsed.asSeconds(),0);
    }
};

#endif // HEROE_H
