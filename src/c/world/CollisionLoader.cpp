//
// Created by dj on 25/07/2025.
//

#include "CollisionLoader.h"

#include "CollisionUtil.h"

using namespace std;

map<std::string, CollisionMap> loadedCollisions = {};

CollisionMap CollisionLoader::loadCollisionMapFromFile(const std::string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERROR] Failed to open collision map file: " << path << endl;
        throw std::runtime_error("Failed to open collision map file");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    nlohmann::json data = nlohmann::json::parse(buffer.str());

    vector<ShapeVariant> collisionParts;

    for (auto &i: data["collisions"]) {
        ShapeVariant shape;
        if (i["type"] == "box") {
            shape = CGAL::Iso_cuboid_3<PointType>(CGAL::Point_3<PointType>(i["start"][0], i["start"][1], i["start"][2]), CGAL::Point_3<PointType>(i["end"][0], i["end"][1], i["end"][2]));
        } else if (i["type"] == "triangle") {
            shape = CGAL::Triangle_3<PointType>(CGAL::Point_3<PointType>(i["vertex1"][0], i["vertex1"][1], i["vertex1"][2]), CGAL::Point_3<PointType>(i["vertex2"][0], i["vertex2"][1], i["vertex2"][2]), CGAL::Point_3<PointType>(i["vertex3"][0], i["vertex3"][1], i["vertex3"][2]));
        } else if (i["type"] == "sphere") {
            shape = CGAL::Sphere_3<PointType>(CGAL::Point_3<PointType>(i["pos"][0], i["pos"][1], i["pos"][2]), static_cast<float>(i["radius"]));
        } else continue;
        glm::mat4 out = glm::mat4(1.0f);
        out = glm::scale(out, glm::vec3(i["scale"][0], i["scale"][1], i["scale"][2]));

        glm::vec3 rotation = glm::radians(glm::vec3(i["rotation"][0], i["rotation"][1], i["rotation"][2]));
        out = glm::rotate(out, rotation.x, glm::vec3(1, 0, 0)); // pitch
        out = glm::rotate(out, rotation.y, glm::vec3(0, 1, 0)); // yaw
        out = glm::rotate(out, rotation.z, glm::vec3(0, 0, 1)); // roll

        shape = CollisionUtil::transform_shape(shape, out);

        collisionParts.push_back(shape);
    }

    //TODO
    return CollisionMap(collisionParts);
}

void CollisionLoader::loadCollisionMaps() {
    for (auto &entry: std::filesystem::recursive_directory_iterator("src/resources/collision_maps/")) {
        std::string extension = entry.path().extension().string();
        if (extension == ".json") {
            std::string path = entry.path().string();
            std::string key = "collision_maps/";
            std::string out = "error";

            size_t pos = path.rfind(key);
            if (pos != std::string::npos) {
                out = path.substr(pos + key.length());

                if (out.size() >= extension.size() &&
                    out.compare(out.size() - extension.size(), extension.size(), extension) == 0) {
                    out = out.substr(0, out.size() - extension.size());
                }
            }

            loadedCollisions[out] = loadCollisionMapFromFile(entry.path().string());
        }
    }
}

CollisionMap* CollisionLoader::getCollisionMap(const string &name) {
	if ((!loadedCollisions.contains(name)) && name != "unknown") {
		cerr << "[ERROR] [CollisionLoader] Unknown collision map: " << name << endl;
		return getCollisionMap("unknown");
	}
	return &loadedCollisions[name];
}
