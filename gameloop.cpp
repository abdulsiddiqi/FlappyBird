#include <SFML/Graphics.hpp>
#include "gameloop.h"
#include <iostream>
#include <memory>
#include <chrono>

GameLoop::GameLoop(sf::RenderWindow &window, unsigned int xMax, unsigned int yMax) : base_graphic{xMax, -5}, main_window(window), pipe_manager{xMax, yMax, -5} {
    if (!background_tex.loadFromFile("../assets/sprites/background-day.png"))
    {
        throw std::invalid_argument("Couldn't load file");
    }
    if (!base_tex.loadFromFile("../assets/sprites/base.png"))
    {
        throw std::invalid_argument("Couldn't load file");
    }
    this->xMax = xMax;
    this->yMax = yMax;
};

int GameLoop::startLoop() {
    // Game loop
    bool play = true;

    // States
    bool up = false;

    sf::Event event;
    while (play) {
        // Events
        up = false;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                play = false;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                up = true;
            }
        }

        // Logic
        player.updatePosition(up);
        pipe_manager.updatePipes();
        base_graphic.update();
        
        if (isCollision()) {
            player.updateState(false);
            pipe_manager.updateState(false);
            base_graphic.updateState(false);
        }

        // Check if player has gotten out of bounds vertically
        if (player.getInstance().getPosition().y + player.getInstance().getSize().y > main_window.getSize().y) {
            init();
            continue;
        }

        // Render
        main_window.clear();
        for (auto shape_ptr: permanentObjects) {
            main_window.draw(*shape_ptr);
        }

        for (auto pipe_ptr: pipe_manager.getPipes()) {
            main_window.draw(*pipe_ptr);
        }

        for (auto base_ptr: base_graphic.getInstances()) {
            main_window.draw(*base_ptr);
        }

        main_window.draw(player.getInstance());

        main_window.display();
    }
    return 0;
}

int GameLoop::init() {
    pipe_manager.init();
    player.init(main_window.getSize().y);
    base_graphic.init();

    return 0;
}

int GameLoop::initShapes() {
    if (init() == 1) {
        return 1;
    }

    std::shared_ptr<sf::RectangleShape> background = std::make_shared<sf::RectangleShape>();
    background->setSize(sf::Vector2f(288*2,1024));
    background->setPosition(0,0);
    background->setTexture(&background_tex);

    permanentObjects.push_back(background);

    return 0;
}

bool GameLoop::isCollision() {
    for (auto pipe_ptr: pipe_manager.getPipes()) {
        if (pipe_ptr.get()->getGlobalBounds().intersects(player.getInstance().getGlobalBounds())) {

            return true;
        }
    }
    return false;
}