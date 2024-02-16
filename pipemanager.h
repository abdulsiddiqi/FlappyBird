#include <stdlib.h>
#include <SFML/Graphics.hpp>

#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

class PipeManager {
public:
    PipeManager() {
        prev = clock.now();
    }

    // Adds pipes
    // Removes pipes which are out of bounds

    inline int init() {
        if (!pipe_tex.loadFromFile("../assets/sprites/pipe-green.png")) {
            return 1;
        }
        return 0;
    }
    void updatePipes();
    inline void updateState(bool state) {
        healthy_state = state;
    }

    inline std::vector<std::shared_ptr<sf::RectangleShape>> getPipes() {
        return pipes;
    }
private:
    sf::Texture pipe_tex;
    std::vector<std::shared_ptr<sf::RectangleShape>> pipes;
    std::chrono::steady_clock clock;
    std::chrono::steady_clock::time_point prev;
    bool healthy_state = true;
};

#endif // PIPEMANAGER_H