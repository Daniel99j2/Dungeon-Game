//
// Created by dj on 28/06/2025.
//

#include "SimpleObject.h"
#include "../../util/model/ModelLoader.h"

SimpleObject::SimpleObject(const glm::vec3& vec)
    : LivingObject(vec) {
    type = "simple";
    model = ModelLoader::getModel("hello");
}

void SimpleObject::tick() {

}