//
// Created by dj on 20/06/2025.
//

#pragma once
#include <string>

struct Vertex;
class Model;

class ModelLoader {
public:
    static Model loadModelFromFile(const std::string &path);

    static void loadModels();

    static Model* getModel(const std::string &name);
};
