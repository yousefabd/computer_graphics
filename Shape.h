#ifndef SHAPE_H
#define SHAPE_H
#include <glm/glm/glm.hpp>
#include <vector>
#include "Vertex.h";
class Shape {
public:
	std::vector<TexVertex> texRegtangle{
		{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f)},//bottom left
		{glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f, 0.0f)}, //bottom right
		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f)}, //top right

		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f)}, //top right
		{glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 1.0f)},//top left
		{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f)},//bottom left
	};
	std::vector<TexVertex> texTriangle{
		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(4.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 4.0f)},
		{glm::vec3(0.0f,0.85f,1.2071067812), glm::vec2(2.0f,4.0f)}
	};
};

#endif