#include "player.h"

Player::Player(){
    try {
        if (!texture.loadFromFile("sprites/Player.png")) {
            throw std::runtime_error("Failed to load texture: ");
        }

        sprite.emplace(texture); // Now safe: sf::Sprite(texture)
        sprite->setOrigin({texture.getSize().x / 2.0f, texture.getSize().y / 2.0f});
    } catch (const std::exception& e) {
        std::cerr << "[Texture Error] " << e.what() << '\n';
    }

    damage = 5;
}

Player::~Player(){}

void Player::mousePosition(const sf::RenderWindow& aux) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(aux);
    sf::Vector2f worldPos = aux.mapPixelToCoords(mousePos);

    sprite->setPosition(worldPos);
    setPositionByChild(worldPos);
}


void Player::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}

sf::FloatRect Player::getBounds() const {
    return sprite ? sprite->getGlobalBounds() : sf::FloatRect{};
}

int Player::getDamage() const {
    return damage;
}

void Player::plusDamage() {
    damage++;
}