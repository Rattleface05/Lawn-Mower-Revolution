#pragma once
#include "entity.h"
#include <random>
#include <iostream>
#include <optional>
#include <stdexcept>

class Grass : public Entity {
    static sf::Texture texture; //au fost erori atunci cand se incerca sa se incarce textura pentru fiecare obiect de iarba in parte
    std::optional<sf::Sprite> sprite;

    int hp; 
    std::mt19937 rng{ std::random_device{}() }; //folosit in loc de rand()
    std::uniform_real_distribution<float> xDist{100.0f, 1820.0f}; 
    std::uniform_real_distribution<float> yDist{100.0f, 980.0f};

public:
    Grass();

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const override;

    void takeDamage(int amount = 1);

    bool isDead() const;

    int getHP() const;

    void setTexture(const sf::Texture &aux);

    void setHP( const int &aux);
};