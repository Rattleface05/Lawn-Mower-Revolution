#include "grass.h"

Grass::Grass(){
    hp = 225;
    static bool loaded = 0;
    if(!loaded){
        try {
            if (!texture.loadFromFile("sprites/Grass.png")) {
                throw std::runtime_error("Failed to load grass texture.");
            }
        } 
        catch (const std::exception& e) {
            std::cerr << "[Grass Texture Error] " << e.what() << '\n';
        }
    sprite.emplace(texture);
    sprite->setOrigin({texture.getSize().x / 2.0f, texture.getSize().y / 2.0f});

    sprite->setPosition(getPosition());
    }
}

Grass::~Grass(){}

sf::Texture Grass::texture;