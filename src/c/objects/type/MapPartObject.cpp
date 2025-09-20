//
// Created by dj on 28/06/2025.
//

#include "MapPartObject.h"

MapPartObject::MapPartObject(const glm::vec3& vec, const std::string &image1, const Layer &layer1)
    : GameObject(vec) {
    type = "map_part";
    image = image1;
    layer = layer1;
}

void MapPartObject::tick() {

}

// void MapPartObject::draw() {
//     switch (this->layer) {
//         case BACKGROUND:
//             {}
//         case FOREGROUND:
//             {}
//         case MISC_TOP:
//             {}
//         case MISC_BOTTOM:
//             {}
//
//         default: throw std::runtime_error("Invalid layer");
//     }
// }
