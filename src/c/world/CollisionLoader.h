//
// Created by dj on 25/07/2025.
//

#pragma once

#include "CollisionUtil.h"

class CollisionLoader {
public:
	static CollisionMap loadCollisionMapFromFile(const std::string &path);

	static void loadCollisionMaps();

	static CollisionMap *getCollisionMap(const std::string &name);
};
