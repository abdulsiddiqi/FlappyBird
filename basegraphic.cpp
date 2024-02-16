#include "basegraphic.h"
#include <iostream>

BaseGraphic::BaseGraphic(unsigned int window_max_x): window_max_x(window_max_x) {
    if (!base_tex.loadFromFile("../assets/sprites/base.png")) {
        throw std::invalid_argument("Couldn't load file");
    }
}


void BaseGraphic::init() {
    base_shapes.clear();
    healthy_state = true;

    auto first_base_shape = std::make_shared<sf::RectangleShape>();
    auto second_base_shape = std::make_shared<sf::RectangleShape>();
    base_shapes.push_back(first_base_shape);
    base_shapes.push_back(second_base_shape);

    first_base_shape->setSize(sf::Vector2f(window_max_x, 300));
    first_base_shape->setPosition(0,1024 - first_base_shape->getSize().y);
    first_base_shape->setTexture(&base_tex);

    second_base_shape->setSize(sf::Vector2f(window_max_x, 300));
    second_base_shape->setPosition(window_max_x,1024 - first_base_shape->getSize().y);
    second_base_shape->setTexture(&base_tex);
}

void BaseGraphic::update() {
    if (healthy_state) {
        for (auto base_shape_ptr: base_shapes) {
            base_shape_ptr->move(-1, 0);
        }
        // Check if one is out of bounds. Then update its position
        for (int i = 0; i < 2; i++) {
            auto base_shape_ptr_first = base_shapes[i];
            if (base_shape_ptr_first->getPosition().x + base_shape_ptr_first->getSize().x < 0) {
                auto base_shape_ptr_second = (i == 0) ? base_shapes[1] : base_shapes[0];
                base_shape_ptr_first->setPosition(base_shape_ptr_second->getPosition().x + window_max_x, 1024 - base_shape_ptr_first->getSize().y);
                break;
            }
        }
    }

}