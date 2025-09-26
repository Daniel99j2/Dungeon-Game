//
// Created by dj on 22/06/2025.
//

#include "Player.h"

#include "../../card/Cards.h"
#include "../../util/GameConstants.h"
#include "../../util/model/RenderUtil.h"

Player::Player(const glm::vec3& vec)
    : GameObject(vec) {
    type = "player";
}

void Player::tick() {

}

void Player::move(bool w, bool a, bool s, bool d) {
    float speed = 0.4f;
    if (w) position.y += speed;
    if (s) position.y -= speed;
    if (a) position.x -= speed;
    if (d) position.x += speed;
    // float max_speed = 1;
    // glm::vec3 front;
    // float speed = 1;
    // float pitch = 0;
    // float yaw = 0;
    // front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    // front.y = sin(glm::radians(pitch));
    // front.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    // front = glm::normalize(front);
    //
    // glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
    // glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
    // glm::vec3 flatRight = glm::normalize(glm::vec3(right.x, 0.0f, right.z));
    //
    // glm::vec3 inputDir(0.0f);
    // if (w) inputDir += flatFront;
    // if (a) inputDir -= flatRight;
    // if (s) inputDir -= flatFront;
    // if (d) inputDir += flatRight;
    //
    // if (glm::length(inputDir) > 0.0f)
    //     inputDir = glm::normalize(inputDir);
    //
    // velocity += inputDir * speed;
    //
    //
    // if (glm::length(velocity) > max_speed)
    //     velocity = glm::normalize(velocity) * max_speed;
}

void Player::draw(int *shadow) const {
    GameConstants::backgroundShader.use();
    GameConstants::backgroundShader.setMat4("projection", RenderUtil::getGuiProjection());
    GameConstants::backgroundShader.setMat4("view", glm::mat4(1));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(GameConstants::window_width/2, GameConstants::window_height/2, 0.0f));
    model = glm::scale(model, glm::vec3(100, 100, 1.0f));
    GameConstants::backgroundShader.setMat4("model", model);
    GameConstants::backgroundShader.setInt("tex", 0);
    RenderUtil::renderQuad();
    Cards::renderCard(*Cards::DEV_TEST_CARD, glm::vec2(1, 2), 500);
}
