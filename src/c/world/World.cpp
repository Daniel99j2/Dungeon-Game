#include "World.h"

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <cmath>
#include <unordered_map>
#include <memory>

#include "CollisionUtil.h"
#include "../util/Profiler.h"

constexpr float GRID_SIZE = 10.0f;

struct GridCoord {
	int x, y, z;

	bool operator==(const GridCoord &other) const {
		return x == other.x && y == other.y && z == other.z;
	}
};

namespace std {
	template<>
	struct hash<GridCoord> {
		std::size_t operator()(const GridCoord &g) const {
			return ((hash<int>()(g.x) ^ (hash<int>()(g.y) << 1)) >> 1) ^ (hash<int>()(g.z) << 1);
		}
	};
}

static GridCoord toGrid(const glm::vec3 &pos) {
	return {
		static_cast<int>(std::floor(pos.x / GRID_SIZE)),
		static_cast<int>(std::floor(pos.y / GRID_SIZE)),
		static_cast<int>(std::floor(pos.z / GRID_SIZE))
	};
}

void World::drawWorld() const {
	for (auto &object: gameObjects) {
		object->draw();
	}
}

void World::tick(float deltaTime) {
	Profiler::beginSection("Physics");
	simulatePhysics(deltaTime);
	Profiler::endSection("Physics");
	for (auto &object: gameObjects) {
		object->baseTick();
	}
}

void World::addObject(std::shared_ptr<GameObject> object) {
	object->id = currentId++;
	gameObjects.push_back(object);
}

void World::simulatePhysics(float dt) {
	for (auto &obj: gameObjects)
		obj->update(dt);

	for (auto &obj: gameObjects)
		obj->applySlowdown(0.05f);
}

static bool checkAABBAABB(const glm::vec3 &aMin, const glm::vec3 &aMax,
                          const glm::vec3 &bMin, const glm::vec3 &bMax) {
	return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
	       (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
	       (aMin.z <= bMax.z && aMax.z >= bMin.z);
}
