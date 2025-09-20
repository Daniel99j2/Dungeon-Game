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

void World::drawWorld(glm::mat4 projection) const {
	for (auto &object: gameObjects) {
		object->draw(projection);
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

	handleCollisions();

	for (auto &obj: gameObjects)
		obj->applySlowdown(0.05f);
}

static bool checkAABBAABB(const glm::vec3 &aMin, const glm::vec3 &aMax,
                          const glm::vec3 &bMin, const glm::vec3 &bMax) {
	return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
	       (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
	       (aMin.z <= bMax.z && aMax.z >= bMin.z);
}

void World::handleCollisions() const {
	std::unordered_map<GridCoord, std::vector<std::shared_ptr<GameObject> > > spatial;

	for (auto &obj: gameObjects)
		spatial[toGrid(obj->position)].push_back(obj);

		// for (size_t j = i + 1; j < objs.size(); ++j) {
		//     auto a = objs[i];
		//     auto b = objs[j];
		//
		//     bool collisionFound = false;
		//     glm::vec3 collisionNormal(0.0f);
		//     float penetrationDepth = 0.0f;
		//
		//     for (const auto& partA : *a->getCollisionParts()) {
		//         for (const auto& partB : *b->getCollisionParts()) {
		//             if (!CollisionUtil::colliding_with(partA.shape, a->transform, partB.shape, b->transform)) continue;
		//
		//             collisionFound = true;
		//             break;
		//             //
		//             // // Calculate overlap
		//             // float overlapX = std::min(aMax.x, bMax.x) - std::max(aMin.x, bMin.x);
		//             // float overlapY = std::min(aMax.y, bMax.y) - std::max(aMin.y, bMin.y);
		//             // float overlapZ = std::min(aMax.z, bMax.z) - std::max(aMin.z, bMin.z);
		//             //
		//             // // Smallest penetration axis
		//             // penetrationDepth = overlapX;
		//             // collisionNormal = glm::vec3((a->position.x < b->position.x) ? -1.0f : 1.0f, 0, 0);
		//             //
		//             // if (overlapY < penetrationDepth) {
		//             //     penetrationDepth = overlapY;
		//             //     collisionNormal = glm::vec3(0, (a->position.y < b->position.y) ? -1.0f : 1.0f, 0);
		//             // }
		//             // if (overlapZ < penetrationDepth) {
		//             //     penetrationDepth = overlapZ;
		//             //     collisionNormal = glm::vec3(0, 0, (a->position.z < b->position.z) ? -1.0f : 1.0f);
		//             // }
		//
		//             break;
		//         }
		//         if (collisionFound) break;
		//     }
		//
		//     if (!collisionFound)
		//         continue;
		//
		//     glm::vec3 contactPoint = (a->position + b->position) * 0.5f;
		//     a->collisions.push_back({ b, contactPoint });
		//     b->collisions.push_back({ a, contactPoint });
		//
		//     // Static ↔ dynamic collision
		//     if (a->isStatic && !b->isStatic) {
		//         b->position += collisionNormal * penetrationDepth;
		//
		//         float velInto = glm::dot(b->velocity, collisionNormal);
		//         if (velInto < 0.0f)
		//             b->velocity -= velInto * collisionNormal;
		//
		//     } else if (!a->isStatic && b->isStatic) {
		//         a->position -= collisionNormal * penetrationDepth;
		//
		//         float velInto = glm::dot(a->velocity, collisionNormal);
		//         if (velInto > 0.0f)
		//             a->velocity -= velInto * collisionNormal;
		//
		//     } else if (!a->isStatic && !b->isStatic) {
		//         glm::vec3 correction = collisionNormal * (penetrationDepth * 0.5f);
		//         a->position -= correction;
		//         b->position += correction;
		//
		//         glm::vec3 relVel = b->velocity - a->velocity;
		//         float velAlong = glm::dot(relVel, collisionNormal);
		//         if (velAlong < 0.0f) {
		//             glm::vec3 impulse = collisionNormal * velAlong * 0.5f;
		//             a->velocity += impulse;
		//             b->velocity -= impulse;
		//         }
		//     }
		// }
}
