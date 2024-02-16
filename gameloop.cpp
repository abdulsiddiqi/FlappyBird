#include <SFML/Graphics.hpp>
#include "gameloop.h"
#include <iostream>
#include <memory>
#include <chrono>

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
    if (!background_tex.loadFromFile("../assets/sprites/background-day.png")) {
        return 1;
    }
    if (!base_tex.loadFromFile("../assets/sprites/base.png")) {
        return 1;
    }

    if (pipe_manager.init() == 1) {
        return 1;
    }

    if (player.init(main_window.getSize().y) == 1) {
        return 1;
    }

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