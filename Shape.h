#ifndef SHAPE_H
#define SHAPE_H
#include <glm/glm/glm.hpp>
#include <vector>
#include "Vertex.h";
class Shape {
private:
    std::vector<TexVertex>arch2() {
        std::vector<TexVertex> vertices{
            {glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(0.0f,-0.11f),glm::vec3(0.0f,0.0f,-1.0f)},//bottom left
            {glm::vec3(-0.4f,0.4f,0.0f), glm::vec2(0.2f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)},//middle middle
            {glm::vec3(-0.4f,-0.5f,0.0f), glm::vec2(0.2f,-0.11f),glm::vec3(0.0f,0.0f,-1.0f)},//bottom right

            {glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(0.0f,-0.11f),glm::vec3(0.0f,0.0f,-1.0f)},//bottom left 
            {glm::vec3(-0.4f,0.4f,0.0f), glm::vec2(0.2f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)},//middle middle
            {glm::vec3(-0.5f,0.4f,0.0f), glm::vec2(0.0f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)},//middle left

            {glm::vec3(-0.5f,0.4f,0.0f), glm::vec2(0.0f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)},//middle left
            {glm::vec3(0.0f,0.5f,0.0f), glm::vec2(1.0f ,1.0f),glm::vec3(0.0f,0.0f,-1.0f)},//top right
            {glm::vec3(-0.5f,0.5f,0.0f), glm::vec2(0.0f,1.0f),glm::vec3(0.0f,0.0f,-1.0f)},//top left

            {glm::vec3(-0.5f,0.4f,0.0f), glm::vec2(0.0f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)},//middle left
            {glm::vec3(0.0f,0.5f,0.0f), glm::vec2(1.0f ,1.0f),glm::vec3(0.0f,0.0f,-1.0f)},//top right
            {glm::vec3(0.0f,0.4f,0.0f), glm::vec2(1.0f,0.8f),glm::vec3(0.0f,0.0f,-1.0f)}, //middle right
            //3D coords
            //top rectangle
            {glm::vec3(-0.5f,0.5f,0.0f), glm::vec2(0.0f,0.0f)},
            {glm::vec3(-0.5f,0.5f,-0.3f), glm::vec2(0.0f,.1f)},
            {glm::vec3(0.0f,0.5f,-0.3f), glm::vec2(1.0f,.1f)},
            {glm::vec3(0.0f,0.5f,0.0f), glm::vec2(0.0f,0.0f)},
            {glm::vec3(-0.5f,0.5f,0.0f), glm::vec2(1.0f,0.0f)},
            {glm::vec3(0.0f,0.5f,-0.3f), glm::vec2(1.0f,.1f)},
            //left rectangle
            {glm::vec3(-0.5f,-0.5f,0.0f), glm::vec2(1.0f,0.0f)},
            {glm::vec3(-0.5f,-0.5f,-0.3f), glm::vec2(0.0f,0.0f)},
            {glm::vec3(-0.5f,0.5f,-0.3f), glm::vec2(.0f,1.0f)},
            {glm::vec3(-0.5f,-0.5f,0.0f), glm::vec2(1.0f,0.0f)},
            {glm::vec3(-0.5f,0.5f,-0.3f), glm::vec2(.0f,1.0f)},
            {glm::vec3(-0.5f,0.5f,0.0f), glm::vec2(1.0f,1.0f)},

            // right rectangle
            {glm::vec3(-0.4f,0.0f,0.0f), glm::vec2(0.2f,0.4f)},
            {glm::vec3(-0.4f,-0.5f,-0.3f), glm::vec2(0.4f,-0.11f)},
            {glm::vec3(-0.4f,-0.5f,0.0f), glm::vec2(0.2f,-0.11f)},
            {glm::vec3(-0.4f,0.0f,0.0f), glm::vec2(0.2f,0.4f)},
            {glm::vec3(-0.4f,-0.5f,-0.3f), glm::vec2(0.4f,-0.11f)},
            {glm::vec3(-0.4f,0.0f,-0.3f), glm::vec2(0.4f,0.4f)},
        };
        float precision = 0.01f;
        for (float y = 0.4f; y - precision >= 0; ) {
            float x = -1.0f * sqrt((0.4f * 0.4f - y * y));
            float x0 = x;
            vertices.push_back({ glm::vec3(-0.4,0.4,0.0f), glm::vec2(0.2f,0.8f) ,glm::vec3(0.0f,0.0f,-1.0f) });//center
            vertices.push_back({ glm::vec3(x,y,0.0f), glm::vec2(1.0f + 2.0f * x,y + 0.4f),glm::vec3(0.0f,0.0f,-1.0f) });//first circle vertex
            y -= precision;
            x = -1 * sqrt((0.4f * 0.4f - y * y));
            vertices.push_back({ glm::vec3(x,y,0.0f), glm::vec2(1.0f + 2.0f * x,y + 0.4f) ,glm::vec3(0.0f,0.0f,-1.0f) });//second circle vertex
            //3D coords
            vertices.push_back({ glm::vec3(x0,y + precision,0.0f), glm::vec2(1.0f + 2.0f * x0,y + 0.4f + precision) });//top left
            vertices.push_back({ glm::vec3(x,y,-0.3f), glm::vec2(1.0f + 2.0f * x + 0.2f,y + 0.4f) });//bottom right
            vertices.push_back({ glm::vec3(x0,y + precision,-0.3f), glm::vec2(1.0f + 2.0f * x0 + 0.2f,y + 0.4f + precision) });//top right

            vertices.push_back({ glm::vec3(x0,y + precision,0.0f), glm::vec2(1.0f + 2.0f * x0,y + 0.4f + precision) });//top left
            vertices.push_back({ glm::vec3(x,y,-0.3f), glm::vec2(1.0f + 2.0f * x + 0.2f,y + 0.4f) });//bottom right
            vertices.push_back({ glm::vec3(x,y,0.0f), glm::vec2(1.0f + 2.0f * x,y + 0.4f) });//bottom left
        }
        return vertices;
    }
public:
    std::vector<TexVertex> texRegtangle{
          {glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f)},//bottom left
        {glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,0.0f,1.0f)},//bottom right
        {glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f)},//top rigght

        {glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f)}, //top right
        {glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f)},//top left
        {glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f) }//bottom left
    };
    std::vector<TexVertex> texTriangle{
        {glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(4.0f, 0.0f), glm::vec3(0,-0.9604,0.278)},
        {glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 4.0f),glm::vec3(0,-0.9604,0.278)},
        {glm::vec3(0.0f,0.85f,1.2071067812), glm::vec2(2.0f,4.0f),glm::vec3(0,-0.9604,0.278)}
    };
    std::vector<TexVertex> texCube1{
        //back
        {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f)},
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f) },
        {glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f)},
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,0.0f,1.0f) },
        {glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f)},
        //front
        {glm::vec3(-0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,-1.0f)},
        {glm::vec3(0.5f, -0.5f,  0.5f),glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,0.0f,-1.0f) },
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,-1.0f)},
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,0.0f,-1.0f) },
        {glm::vec3(-0.5f,  0.5f,  0.5f),glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,0.0f,-1.0f)},
        {glm::vec3(-0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,0.0f,-1.0f)},
        //left
        {glm::vec3(-0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,0.0f,0.0f)},
        {glm::vec3(-0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f),glm::vec3(1.0f,0.0f,0.0f)},
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,0.0f,0.0f)},
        {glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,0.0f,0.0f)},
        { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(1.0f,0.0f,0.0f)},
        {glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,0.0f,0.0f)},
        //right
        {glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(-1.0f,0.0f,0.0f)},
        //bottom
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,1.0f,0.0f)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,1.0f,0.0f)},
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f) },
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f)},
        {glm::vec3(-0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f)},
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,1.0f,0.0f)},
        //top
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,-1.0f,0.0f)},
        {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,-1.0f,0.0f)},
        {glm::vec3(0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,-1.0f,0.0f)},
        {glm::vec3(0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,-1.0f,0.0f)},
        {glm::vec3(-0.5f, 0.5f,  0.5f),glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,-1.0f,0.0f)},
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,-1.0f,0.0f)},
    };
    std::vector<TexVertex>arch = arch2();
    std::vector<float>sky_box_cube{
       -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };
};

#endif