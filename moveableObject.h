#include <SFML/Graphics.hpp>

class MoveableObject{
    public: 
    MoveableObject(sf::Shape& shape) {
        shape_ptr = &shape;
    };

    private:
    sf::Shape* shape_ptr;
};