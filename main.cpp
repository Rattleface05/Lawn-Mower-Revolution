#include <SFML/Audio.hpp>
#include "entity.h"
#include "player.h"
#include "grass.h"
#include "weed.h"
#include <vector>

int main() {
    unsigned int width = 1920, height = 1080;
    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode({width,height}), "Lawn Mower Revolution");
    window->setFramerateLimit(60);

    Player player;
    std::vector<Grass> grassPatches;
    std::vector<Weed> weedPatches;

    for (int i = 0; i < 20; ++i) {
        grassPatches.emplace_back();
    }

    //Scorul
    long long int score = 0;
    sf::Font font;
    if (!font.openFromFile("fonts/kenney_mini.ttf")) {
        std::cerr << "Failed to load font: kenney_mini.ttf\n";
        return -1;
    }

    sf::Text scoreText(font), dmgAllert(font);

    scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({1700, 10});
    scoreText.setString("Score: 0");

    dmgAllert.setFont(font);
    dmgAllert.setCharacterSize(38);
    dmgAllert.setFillColor(sf::Color::White);
    dmgAllert.setPosition({860, 10});
    dmgAllert.setString("Damage up!");

    //EL MUSICA
    sf::Music music("audio/background.wav");
    music.setLoopPoints({sf::seconds(4), sf::seconds(225)});
    music.play();

    // //Background //Nu i-am gasit o textura care sa imi placa inca ;-;
    // sf::Texture background;
    // try {
    //     if (!background.loadFromFile("sprites/background.png")) {
    //         throw std::runtime_error("Failed to load texture: ");
    //     }
    // } catch (const std::exception& e) {
    //     std::cerr << "[Texture Error] " << e.what() << '\n';
    // }
    // sf::Sprite bg(background);


    //utilitati sa ma ocup de timpul elapsat
    sf::Clock timp, clock, grassSpawnClock, weedSpawnClock, damageClock;
    float grassInterval = 1, weedInterval = 1.5;

    while (window->isOpen()) {
        
        //esc inchide fereastra, doar o componenta in plus, irelevanta
        while(const std::optional event = window->pollEvent()){

            if (event->is<sf::Event::Closed>()){
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                }
            }
        }

        //Actualizam scorul
        scoreText.setString("Score: " + std::to_string(score));

        float dt = clock.restart().asSeconds();

        player.mousePosition(*window);
        player.update(dt);

        //Decide daca iarba sau buruiana este taiata
        for (auto& grass : grassPatches) {
            grass.update(dt);

            if (grass.getBounds().findIntersection(player.getBounds())) {
                grass.takeDamage(player.getDamage());
            }
        }
        for (auto& weed : weedPatches) {
            weed.update(dt);

            if (weed.getBounds().findIntersection(player.getBounds())) {
                weed.takeDamage(player.getDamage());
            }
        }

        //Daca sunt taiate de tot, dispar
        for(int i = 0; i < grassPatches.size(); ++i){
            if(grassPatches.at(i).isDead()){
                grassPatches.erase(grassPatches.begin() + i);
                score++;
            }

        }

        for(int i = 0; i < weedPatches.size(); ++i){
            if(weedPatches.at(i).isDead()){
                weedPatches.erase(weedPatches.begin() + i);
                score+=2; //buruienile dau scor dublu
            }

        }

        // Se spawn-eaza in continuu iarba pana ajunge la 30
        if (grassPatches.size() < 30 && grassSpawnClock.getElapsedTime().asSeconds() >= grassInterval) {
            grassPatches.emplace_back();
            grassSpawnClock.restart();
        }

        //La fel pentru buruieni, dar ele apar abia dupa 10 secunde, si ajung la abia 20
        if(timp.getElapsedTime().asSeconds() >= 10.0f)
            if (weedPatches.size() < 20 && weedSpawnClock.getElapsedTime().asSeconds() >= weedInterval) {
                weedPatches.emplace_back();
                weedSpawnClock.restart();
            }
        
        //Damage creste la fiecare 15 sec pana ajunge la 10
        if(damageClock.getElapsedTime().asSeconds() >= 15 && player.getDamage() < 10){
            player.plusDamage();
            damageClock.restart();
        }



        //render
        window->clear(sf::Color(17, 112, 42));

        //deseneaza entitati si scor
        // window->draw(bg);
        for (int i = 0; i < grassPatches.size(); ++i) {
            grassPatches.at(i).draw(*window);
        }
        for (int i = 0; i < weedPatches.size(); ++i) {
            weedPatches.at(i).draw(*window);
        }
        player.draw(*window);


        //Scorul si notificarile trebuie sa  fie ultimul rendered 
        window->draw(scoreText);
        if(damageClock.getElapsedTime().asSeconds() <= 5 && player.getDamage() > 5 && player.getDamage() <10 )
            window->draw(dmgAllert);



        window->display();
    }

    return 0;
}
