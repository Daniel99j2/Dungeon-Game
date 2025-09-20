//
// Created by dj on 28/06/2025.
//
#pragma once

#include "../GameObject.h"

enum Layer {
    BACKGROUND,
    FOREGROUND,
    MISC_TOP,
    MISC_BOTTOM,
};

class MapPartObject : public GameObject {
public:
    std::string image;
    Layer layer;

    explicit MapPartObject(const glm::vec3& vec, const std::string &image, const Layer &layer);

    void tick() override;
};
