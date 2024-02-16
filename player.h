#include <SFML/Graphics.hpp>
#include "pipemanager.h"

class Player {
public:
    Player();
    void init(float window_max_y);

    inline sf::RectangleShape getInstance() {
        return *bird_ptr;
    }

    // This method updates the position of the player and its animations
    void updatePosition(bool up);
    inline void updateState(bool state) {
        healthy_state = state;
    }

private:
    // Methods
    void updateTexture();

    // Constants
    const int TEXTURE_UPDATE_MS = 200;

    // Variables
    std::chrono::steady_clock clock;
    std::chrono::steady_clock::time_point prev_update;
    std::shared_ptr<sf::RectangleShape> bird_ptr;
    float speed_y, acceleration_y = (9.8/60);
    sf::Texture bird_mid_tex, bird_up_tex, bird_down_tex;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    int texture_index;
    bool healthy_state;
};