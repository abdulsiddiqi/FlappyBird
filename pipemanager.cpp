#include "pipemanager.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>


void PipeManager::updatePipes() {
    if (!healthy_state) {
        return;
    }
    
    auto now = clock.now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - prev).count();
    if (diff >= 5) {

        std::shared_ptr<sf::RectangleShape> bot_pipe = std::make_shared<sf::RectangleShape>();
        bot_pipe->setSize(sf::Vector2f(52*1.5, 320*1.5));
        bot_pipe->setPosition(288*2 + 60, 1024 - bot_pipe->getSize().y);
        bot_pipe->setTexture(&pipe_tex);

        std::shared_ptr<sf::RectangleShape> top_pipe = std::make_shared<sf::RectangleShape>();
        top_pipe->setSize(sf::Vector2f(52*1.5, 320*1.5));
        top_pipe->setRotation(180);
        top_pipe->setPosition(288*2 + 60, 320);
        top_pipe->setTexture(&pipe_tex);

        pipes.push_back(bot_pipe);
        pipes.push_back(top_pipe);

        std::cout << "Added pipes with len: " << pipes.size() << "\n";

        prev = now;
    }

    for (auto pipe: pipes) {
        pipe->move(sf::Vector2f(-5, 0));
    }

    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](std::shared_ptr<sf::RectangleShape> pipe)
                               { return (pipe->getPosition().x + pipe->getSize().x + 5) < 0; }),
                pipes.end());
}

