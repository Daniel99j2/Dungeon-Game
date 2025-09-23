//
// Created by dj on 28/06/2025.
//

#include "MapPartObject.h"

#include "Player.h"
#include "../../util/GameConstants.h"
#include "../../util/model/RenderUtil.h"

MapPartObject::MapPartObject(const glm::vec3& vec, const std::string &image1, const Layer &layer1)
    : GameObject(vec) {
    type = "map_part";
    image = image1;
    layer = layer1;
}

void MapPartObject::tick() {

}

void MapPartObject::draw() const {
    Shader* shader;
    int layer = 0;
    switch (this->layer) {
        case BACKGROUND: {
            shader = &GameConstants::backgroundShader;
            layer = 0;
            break;
        }
        case FOREGROUND: {
            shader = &GameConstants::foregroundShader;
            layer = 0.1;
            break;
        }
        case MISC_TOP: {
            shader = &GameConstants::backgroundShader;
            layer = 0.2;
            break;
        }
        case MISC_BOTTOM: {
            shader = &GameConstants::backgroundShader;
            layer = -0.1;
            break;
        }
        default: throw std::runtime_error("Invalid layer");
    }

    shader->use();
    shader->setMat4("projection", RenderUtil::getWorldProjection());
    shader->setMat4("view", glm::mat4(1));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-GameConstants::player->position.x, -GameConstants::player->position.y, layer));
    model = glm::scale(model, glm::vec3(200, 200, 1.0f));
    shader->setMat4("model", model);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, RenderUtil::getOrGenTexture("src/resources/textures/"+image));
    shader->setInt("tex", 1);
    RenderUtil::renderQuad();
}
