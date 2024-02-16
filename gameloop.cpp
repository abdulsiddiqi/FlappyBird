#include <SFML/Graphics.hpp>
#include "gameloop.h"
#include <iostream>
#include <memory>
#include <chrono>

GameLoop::GameLoop(sf::RenderWindow& window): main_window(window) {
    if (!background_tex.loadFromFile("../assets/sprites/background-day.png")) {
        throw std::invalid_argument("Couldn't load file");
    }
    if (!base_tex.loadFromFile("../assets/sprites/base.png")) {
        throw std::invalid_argument("Couldn't load file");
    }
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
        if (player.isCollision(pipe_manager)) {
            pipe_manager.updateState(false);
        }

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

        main_window.draw(player.getInstance());

        main_window.display();
    }
    return 0;
}

int GameLoop::init() {
    pipe_manager.init();
    player.init(main_window.getSize().y);

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

    std::shared_ptr<sf::RectangleShape> base = std::make_shared<sf::RectangleShape>();
    base->setSize(sf::Vector2f(288*2, 300));
    base->setPosition(0,1024 - base->getSize().y);
    base->setTexture(&base_tex);

    permanentObjects.push_back(background);
    permanentObjects.push_back(base);

    return 0;
}