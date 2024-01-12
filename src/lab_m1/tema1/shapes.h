#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace shapes {
    Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float length, float width, glm::vec3 color, bool fill = false);

    Mesh* CreateStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color);

    Mesh* CreateEnemy(const std::string& name, int type, glm::vec3 center, float length, glm::vec3 color1, glm::vec3 color2);

    Mesh* CreateHero(const std::string& name, int type, glm::vec3 center, float length, glm::vec3 color);
}
