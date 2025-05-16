#include "entity.h"

Entity::Entity(){}

Entity::~Entity(){}

void Entity::setPosition(const sf::Vector2f& aux) {
    position = aux;
}

void Entity::setPositionByChild(const sf::Vector2f& aux){
    position = aux;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

