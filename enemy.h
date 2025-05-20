#pragma once
#include "entity.h"
#include <random>
#include <iostream>
#include <optional>
#include <stdexcept>

class Enemy : public Entity {
protected:
    std::optional<sf::Sprite> sprite;

    int hp;
    std::mt19937 rng{ std::random_device{}() }; //folosit in loc de rand()
    std::uniform_real_distribution<float> xDist{100.0f, 1820.0f}; 
    std::uniform_real_distribution<float> yDist{100.0f, 980.0f};

public:
    Enemy();
    ~Enemy();

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const override;

    void takeDamage(int amount = 1);

    bool isDead() const;

    int getHP() const;

    void setTexture(const sf::Texture &aux);

    void setHP( const int &aux);

};