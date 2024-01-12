#include "shapes.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* shapes::CreateRectangle(const std::string& name, glm::vec3 center, float length, float width, glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(center + glm::vec3(-length / 2, -width / 2, 0), color),
        VertexFormat(center + glm::vec3(-length / 2, width / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, width / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, -width / 2, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* shapes::CreateEnemy(const std::string& name, int type, glm::vec3 center, float length, glm::vec3 color1, glm::vec3 color2) {
    int gap = 15; // GAP BETWEEN OUTER AND INNER HEXAGHON

    double rotation_angle = -10.0; // DEGREES

    double rotation_angle_radians = rotation_angle * M_PI / 180.0; // TRANSFORM IN RADIANS

    std::vector<VertexFormat> vertices;
        // OUTER HEXAGHON
        for (int i = 0; i < 6; i++) {
            double angle = i * M_PI / 3.0; // WHICH 60 DEGREES WE'RE TALKING ABOUT
            vertices.push_back(VertexFormat(center + glm::vec3(length/2 * cos(angle + rotation_angle_radians), length/2 * sin(angle + rotation_angle_radians), 2), color1));
        }
        // INNER HEXAGHON
        for (int i = 0; i < 6; i++) {
            double angle = i * M_PI / 3.0;
            vertices.push_back(VertexFormat(center + glm::vec3((length/2 - gap) * cos(angle + rotation_angle_radians), (length/2 - gap) * sin(angle + rotation_angle_radians), 3), color2));
        }

    Mesh* hexaghon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5,
                                          6, 7, 8, 6, 8, 9, 6, 9, 10, 6, 10, 11};

    hexaghon->InitFromData(vertices, indices);
    return hexaghon;
}

Mesh* shapes::CreateHero(const std::string& name, int type, glm::vec3 center, float length, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        // THE RHOMBUS
        VertexFormat(center + glm::vec3(-length / 4, 0, 2), color),
        VertexFormat(center + glm::vec3(0, length / 2, 2), color),
        VertexFormat(center + glm::vec3(length / 4, 0, 2), color),
        VertexFormat(center + glm::vec3(0, -length / 2, 2), color),
        // THE GUN
        VertexFormat(center + glm::vec3(0, length / 8, 2), color),
        VertexFormat(center + glm::vec3(length / 2, length / 8, 2), color),
        VertexFormat(center + glm::vec3(length / 2, -length / 8, 2), color),
        VertexFormat(center + glm::vec3(0 , -length / 8, 2), color),
    };

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          2, 3, 0,
                                          4, 5, 6,
                                          4, 6, 7 };

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}


Mesh* shapes::CreateStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(center + glm::vec3(-7 * length / 16, -length / 2, 1), color),
        VertexFormat(center + glm::vec3(-2.2 * length / 8, -length / 8, 1), color),
        VertexFormat(center + glm::vec3(-length / 2 ,length / 6 , 1), color),
        VertexFormat(center + glm::vec3(-length / 6, length / 6, 1), color),
        VertexFormat(center + glm::vec3(0, length / 2, 1), color),
        VertexFormat(center + glm::vec3(length / 6, length / 6, 1), color),
        VertexFormat(center + glm::vec3(length / 2, length / 6, 1), color),
        VertexFormat(center + glm::vec3(2.2 * length / 8, -length / 8, 1), color),
        VertexFormat(center + glm::vec3(7 * length / 16, -length / 2, 1), color),
        VertexFormat(center + glm::vec3(0, -length / 3.5, 1), color),
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 9,
                                          1, 2, 3,
                                          3, 4, 5,
                                          5, 6, 7,
                                          7, 8, 9,
                                          1, 3, 9,
                                          3, 9, 5,
                                          5, 9, 7};

    star->InitFromData(vertices, indices);
    return star;
}
