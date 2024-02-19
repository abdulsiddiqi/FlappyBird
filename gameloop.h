#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "pipemanager.h"
#include "player.h"
#include "basegraphic.h"

class GameLoop {
public:
    GameLoop(sf::RenderWindow& window, unsigned int xMax, unsigned int yMax);

    int startLoop();
    int initShapes();

private: 
    int init();
    bool isCollision();

    sf::RenderWindow& main_window;
    unsigned int xMax, yMax;
    sf::Texture background_tex, base_tex;
    std::vector<std::shared_ptr<sf::Shape>> permanentObjects;
    Player player;
    PipeManager pipe_manager;
    BaseGraphic base_graphic;
};