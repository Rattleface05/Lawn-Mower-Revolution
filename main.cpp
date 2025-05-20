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

    sf::Text scoreText(font), dmgAllert(font), remainingTime(font);

    //scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({1705, 10});
    scoreText.setString("Score: 0");

    remainingTime.setCharacterSize(32);
    remainingTime.setFillColor(sf::Color::White);
    remainingTime.setPosition({1569, 40});
    remainingTime.setString("Time remaining: 60");

    //dmgAllert.setFont(font);
    dmgAllert.setCharacterSize(38);
    dmgAllert.setFillColor(sf::Color::White);
    dmgAllert.setPosition({830, 10});
    dmgAllert.setString("Damage increased!");


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

        if(timp.getElapsedTime().asSeconds() < 60){
            //Actualizam scorul si timpul
            scoreText.setString("Score: " + std::to_string(score));
            remainingTime.setString("Time remaining: " + std::to_string(60 - timp.getElapsedTime().asSeconds()));


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
            
            //Damage creste la fiecare 10
            if(damageClock.getElapsedTime().asSeconds() >= 10){
                player.plusDamage(2);
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
            window->draw(remainingTime);
            if(damageClock.getElapsedTime().asSeconds() <= 2.5f && player.getDamage() > 5)
                window->draw(dmgAllert);

        }
    else{
        window->clear(sf::Color(17, 100, 42));
        sf::Text highScore(font);
        highScore.setCharacterSize(160);
        highScore.setFillColor(sf::Color::White);
        highScore.setPosition({610, 300});
        highScore.setString("Time's Up!\nScore: " + std::to_string(score));
        window->draw(highScore);
    }

    window->display();
        
    }

    return 0;
}
