#include "GameObject.h"
#include "../util/GameConstants.h"
#include "../PreImports.h"
#include <glm/gtx/quaternion.hpp>
#include "../world/CollisionUtil.h"

GameObject::GameObject(const glm::vec3 vec)
    : position(vec) {
}

GameObject::GameObject() {
    throw std::runtime_error("Cannot create empty GameObject");
}

void GameObject::applySlowdown(float drag) {
    velocity *= (1.0f - drag);
}

void GameObject::update(float dt) {
}

void GameObject::draw(int *shadow) const {
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

void GameObject::drawShadow() const {

}


void GameObject::baseTick() {
    this->tick();
}