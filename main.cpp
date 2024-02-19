#include <iostream>
#include "gameloop.h"

int main() {
    unsigned int xMax = 288*2, yMax = 512*2;
    sf::RenderWindow window(sf::VideoMode(xMax, yMax), "SFML works!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    GameLoop gameLoop(window, xMax, yMax);
    if (gameLoop.initShapes() == 1) {
        return 1;
    }
    
    return gameLoop.startLoop();
}