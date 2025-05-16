#include "weed.h"

Weed::Weed(){
    hp = 350;
    static bool loaded = 0;
    if(!loaded){
        try {
            if (!texture.loadFromFile("sprites/Weed.png")) {
                throw std::runtime_error("Failed to load weed texture.");
            }
        } 
        catch (const std::exception& e) {
            std::cerr << "[Weed Texture Error] " << e.what() << '\n';
        }
    sprite.emplace(texture);
    sprite->setOrigin({texture.getSize().x / 2.0f, texture.getSize().y / 2.0f});

    sprite->setPosition(getPosition());
    }
}

Weed::~Weed(){}

sf::Texture Weed::texture;