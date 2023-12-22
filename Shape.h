#ifndef SHAPE_H
#define SHAPE_H
#include <glm/glm/glm.hpp>
#include <vector>
#include "Vertex.h";
class Shape {
public:
	std::vector<TexVertex> texRegtangle{
		{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f)},
	};
};

#endif