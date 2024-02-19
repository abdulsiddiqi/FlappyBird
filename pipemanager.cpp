#include "pipemanager.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

PipeManager::PipeManager(unsigned int window_max_x, unsigned int window_max_y, int speed_x) {
    if (!pipe_tex.loadFromFile("../assets/sprites/pipe-green.png")) {
        throw std::invalid_argument("Couldn't load file in pipemanager");
    }
    this->window_max_x = window_max_x;
    this->window_max_y = window_max_y;
    this->speed_x = speed_x;
}

void PipeManager::init() {
    healthy_state = true;
    pipes.clear();
    prev = clock.now();
}


void PipeManager::updatePipes() {
    if (!healthy_state) {
        return;
    }

    auto now = clock.now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - prev).count();
    std::random_device rd;
    std::mt19937 gen(rd());
    if (diff >= 2) {
        int pipe_size_x = 52*2;
        int pipe_size_y = 320*2;

        int pipe_gap_distance = 200;
        std::uniform_int_distribution<> distrib(pipe_size_y, pipe_size_y*1.2);
        int bot_pipe_pos_y = window_max_y - distrib(gen);
        int top_pipe_pos_y = bot_pipe_pos_y - pipe_gap_distance;

        std::shared_ptr<sf::RectangleShape> bot_pipe = std::make_shared<sf::RectangleShape>();
        bot_pipe->setSize(sf::Vector2f(pipe_size_x, window_max_y - bot_pipe_pos_y));
        bot_pipe->setPosition(window_max_x + PIPE_INSERTION_BUFFER_X, bot_pipe_pos_y);
        bot_pipe->setTexture(&pipe_tex);

        std::shared_ptr<sf::RectangleShape> top_pipe = std::make_shared<sf::RectangleShape>();
        top_pipe->setSize(sf::Vector2f(pipe_size_x, pipe_size_y));
        top_pipe->setRotation(180);
        top_pipe->setPosition(window_max_x + PIPE_INSERTION_BUFFER_X + pipe_size_x, top_pipe_pos_y);
        top_pipe->setTexture(&pipe_tex);

        pipes.push_back(bot_pipe);
        pipes.push_back(top_pipe);

        std::cout << "Added pipes with len: " << pipes.size() << "\n";

        prev = now;
    }

    for (auto pipe: pipes) {
        pipe->move(sf::Vector2f(speed_x, 0));
    }

    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](std::shared_ptr<sf::RectangleShape> pipe)
                               { return (pipe->getPosition().x + pipe->getSize().x + 5) < 0; }),
                pipes.end());
}

