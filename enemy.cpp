#include "enemy.h"
Enemy::Enemy(){
        //hp = 1024;
        //     static bool loaded = 0;
        // if(!loaded){
        //     try {
        //         if (!texture.loadFromFile("sprites/Grass.png")) {
        //             throw std::runtime_error("Failed to load grass texture.");
        //         }
        //     } 
        //     catch (const std::exception& e) {
        //         std::cerr << "[Grass Texture Error] " << e.what() << '\n';
        //     }
        // sprite.emplace(texture);
        // sprite->setOrigin({texture.getSize().x / 2.0f, texture.getSize().y / 2.0f});

        sf::Vector2f randomPos(xDist(rng), yDist(rng));
        // sprite->setPosition(randomPos);
        setPositionByChild(randomPos);
        }

Enemy::~Enemy(){}

void Enemy::update(float dt) {
        // o sa-l folosesc pentru a ii schimba textura cand este taiata
    }

void Enemy::draw(sf::RenderWindow& window){
        if (sprite) {
            window.draw(*sprite);
        }
    }


sf::FloatRect Enemy::getBounds() const{
        return sprite ? sprite->getGlobalBounds() : sf::FloatRect{};
    }

void Enemy::takeDamage(int amount){
        hp -= amount;
    }

bool Enemy::isDead() const {
        return hp <= 0;
    }

int Enemy::getHP() const {
        return hp;
    }

void Enemy::setTexture(const sf::Texture &aux){
        sprite.emplace(aux);
    }

void Enemy::setHP( const int &aux){
    hp = aux;
}









