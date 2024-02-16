#include <SFML/Graphics.hpp>

class BaseGraphic {
public:
    BaseGraphic(unsigned int window_max_x);
    void init();

    void update();
    inline void updateState(bool state) {
        healthy_state = state;
    }

    inline std::vector<std::shared_ptr<sf::RectangleShape>> getInstances() {
        return base_shapes;
    }

private:
    unsigned int window_max_x;
    sf::Texture base_tex;
    std::vector<std::shared_ptr<sf::RectangleShape>> base_shapes;
    bool healthy_state;
};