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
    glm::vec3 position;
    glm::vec3 velocity = glm::vec3(0);
    std::string type;
    glm::mat4 transform = glm::mat4(1.0f);
    int id = -1;
    std::vector<Collision> collisions;

    void applySlowdown(float drag);

    void update(float dt);

    static void renderBoundingBox();

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