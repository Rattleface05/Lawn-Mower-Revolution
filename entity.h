#pragma once
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

class Entity {
    sf::Vector2f position;
    
public:
    Entity();
    virtual ~Entity();

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;

    virtual void setPosition(const sf::Vector2f& aux);

    void setPositionByChild(const sf::Vector2f& aux);

    sf::Vector2f getPosition() const;


};
