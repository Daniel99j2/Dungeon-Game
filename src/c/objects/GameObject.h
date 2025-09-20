#pragma once
#include <string>
#include <vector>
#include <memory>

#include "../util/model/Shader.h"

enum class ShapeType {
    Rectangle,
    Sphere,
    Cylinder
};

struct Collision {
    std::shared_ptr<class GameObject> other;
    glm::vec3 point;
};

class GameObject {
public:
    glm::vec2 position;
    glm::vec2 velocity = glm::vec2(0);
    std::string type;
    int id = -1;
    std::vector<Collision> collisions;

    void applySlowdown(float drag);

    void update(float dt);

    virtual void draw(glm::mat4 projection);
    void baseTick();
    virtual void tick() = 0;
    virtual ~GameObject() = default;

    explicit GameObject(glm::vec3 vec);
    GameObject(const GameObject&) = default;
    GameObject& operator=(const GameObject&) = default;

private:
    GameObject();
};