#include "grass.h"

Grass::Grass(){
    hp = 45;
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

    sf::Vector2f randomPos(xDist(rng), yDist(rng));
    sprite->setPosition(randomPos);
    setPositionByChild(randomPos);
    }
}

void Grass::update(float dt) {
    // o sa-l folosesc pentru a ii schimba textura cand este taiata
}

void Grass::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}

sf::FloatRect Grass::getBounds() const {
    return sprite ? sprite->getGlobalBounds() : sf::FloatRect{};
}

void Grass::takeDamage(int amount) {
    hp -= amount;
}

bool Grass::isDead() const{
    return hp <= 0;
}

int Grass::getHP() const{
    return hp;
}

void Grass::setHP(const int &aux){
    hp = aux;
}

void Grass::setTexture(const sf::Texture &aux){
    texture = aux;
    sprite->setTexture(texture);
}

sf::Texture Grass::texture;