#include "GameObject.h"
#include "../util/GameConstants.h"
#include "../util/model/ModelLoader.h"
#include "../PreImports.h"
#include <glm/gtx/quaternion.hpp>
#include "../world/CollisionUtil.h"

GameObject::GameObject(const glm::vec3 vec)
    : position(vec),
      mass(1.0f),
      gravity(0.98),
      model(ModelLoader::getModel("unknown")),
      shader(GameConstants::defaultShader) {
}

GameObject::GameObject() {
    throw std::runtime_error("Cannot create empty GameObject");
}

void GameObject::applySlowdown(float drag) {
    velocity *= (1.0f - drag);
}

std::vector<ShapeVariant>* GameObject::getCollisionParts() const {
    return &this->model->collisionMap->collisionParts;
}

void GameObject::update(float dt) {
    collisions.clear();
}

void GameObject::draw(float deltaTime) {
    shader.use();
    animator.tick(deltaTime);
    model->draw(shader, this->transform, animator);

    if (GameConstants::debugCollision) {
        GameConstants::simpleShader.use();
        // for (auto& part : *getCollisionParts()) {
        //     glm::vec3 min = glm::min(part.start, part.end);
        //     glm::vec3 max = glm::max(part.start, part.end);
        //
        //     glm::vec3 size = max - min;
        //     glm::vec3 center = (min + max) / 2.0f;
        //
        //     auto model = glm::mat4(1.0f);
        //     model = glm::translate(model, this->position + center); // center in world
        //     model = glm::scale(model, size); // scale full size (no division by 2)
        //
        //     GameConstants::simpleShader.setMat4("model", model);
        //
        //     renderBoundingBox();
        // }
    }
}

void GameObject::baseTick() {
    this->transform = glm::mat4(1.0f);
    this->transform = glm::translate(this->transform, this->position);
    this->transform = glm::rotate(this->transform, glm::radians(this->yaw), glm::vec3(0, 1, 0));
    this->transform = glm::rotate(this->transform, glm::radians(this->pitch), glm::vec3(1, 0, 0));
    this->tick();
}

unsigned int boundingBoxVAO = 0;
unsigned int boundingBoxVBO;
void GameObject::renderBoundingBox() {
    if (boundingBoxVAO == 0) {
        float cubeEdgeVertices[] = {
            // back face
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            // front face
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            // left face
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            // right face
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,

            // bottom face
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            // top face
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };
        // setup plane VAO
        glGenVertexArrays(1, &boundingBoxVAO);
        glGenBuffers(1, &boundingBoxVBO);
        glBindVertexArray(boundingBoxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, boundingBoxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeEdgeVertices), &cubeEdgeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }
    glBindVertexArray(boundingBoxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}