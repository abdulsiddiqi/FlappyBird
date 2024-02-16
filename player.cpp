#include "player.h"
#include <iostream>
#include "pipemanager.h"

int Player::init(float window_max_y) {
        if (!bird_down_tex.loadFromFile("../assets/sprites/bluebird-downflap.png")) {
            return 1;
        }
        if (!bird_mid_tex.loadFromFile("../assets/sprites/bluebird-midflap.png")) {
            return 1;
        }
        if (!bird_up_tex.loadFromFile("../assets/sprites/bluebird-upflap.png")) {
            return 1;
        }

        bird_ptr = std::make_shared<sf::RectangleShape>();
        bird_ptr->setSize(sf::Vector2f(34*1.5,24*1.5));
        bird_ptr->setPosition(20, window_max_y / 2);
        //bird_ptr->setTexture(&bird_mid_tex);

        textures.push_back(std::make_shared<sf::Texture>(bird_down_tex));
        textures.push_back(std::make_shared<sf::Texture>(bird_mid_tex));
        textures.push_back(std::make_shared<sf::Texture>(bird_up_tex));

        bird_ptr->setTexture(textures[1].get());

        return 0;
    }

void Player::updatePosition(bool up) {
    if (healthy_state) {
        if (up) {
            speed_y = -7.5;
        } else {
            speed_y += acceleration_y;
        }
    } else {
        speed_y += acceleration_y;
    }

    bird_ptr->move(sf::Vector2f(0, speed_y));
    updateTexture();
}

void Player::updateTexture() {
    auto now = clock.now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev_update).count();
    if (diff > TEXTURE_UPDATE_MS) {
        texture_index = (texture_index + 1) % 3;
        auto next_texture = textures[texture_index];
        bird_ptr->setTexture(textures[texture_index].get());
        prev_update = now;
    }
}

bool Player::isCollision(PipeManager pipe_manager) {
    for (auto pipe_ptr: pipe_manager.getPipes()) {
        if (pipe_ptr.get()->getGlobalBounds().intersects(bird_ptr.get()->getGlobalBounds())) {
            healthy_state = false;
            return true;
        }
    }
    return false;
}