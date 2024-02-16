#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "pipemanager.h"
#include "player.h"

class GameLoop {
public:
    GameLoop(sf::RenderWindow& window): main_window(window) {
    };

    int startLoop();
    int initShapes();

private: 
    int init();

    sf::RenderWindow& main_window;
    sf::Texture background_tex, base_tex;
    std::vector<std::shared_ptr<sf::Shape>> permanentObjects;
    Player player;
    PipeManager pipe_manager;
    
};