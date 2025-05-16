#pragma once
#include "enemy.h"

class Weed : public Enemy {
    static sf::Texture texture; //au fost erori atunci cand se incerca sa se incarce textura pentru fiecare obiect de iarba in parte

public:
    Weed();
    ~Weed();
};