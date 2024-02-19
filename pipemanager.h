#include <stdlib.h>
#include <SFML/Graphics.hpp>

#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

class PipeManager {
public:
    PipeManager(unsigned int window_max_x, unsigned int window_max_y);
    void init();

    void updatePipes();
    inline void updateState(bool state) {
        healthy_state = state;
    }

    inline std::vector<std::shared_ptr<sf::RectangleShape>> getPipes() {
        return pipes;
    }
private:
    unsigned int window_max_x, window_max_y;
    sf::Texture pipe_tex;
    std::vector<std::shared_ptr<sf::RectangleShape>> pipes;
    std::chrono::steady_clock clock;
    std::chrono::steady_clock::time_point prev;
    bool healthy_state;
    const int PIPE_INSERTION_BUFFER_X = 60;
};

#endif // PIPEMANAGER_H