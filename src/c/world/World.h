#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

#include "../objects/GameObject.h"

class World {
public:
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    void tick(float deltaTime);

    void addObject(std::shared_ptr<GameObject> object);

    [[nodiscard]] std::vector<std::shared_ptr<GameObject>> getObjects() const {
        return gameObjects;
    }

private:
    int currentId = 0;

    void simulatePhysics(float deltaTime);
};