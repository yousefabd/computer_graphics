#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <Shader.h>
#include <glm/glm/glm.hpp>
#include "Shape.h"
#include "Vertex.h"

class Renderer {
public:
	void clear() const;
	void bind(unsigned int VAO, unsigned int VBO, Shader shader);
	void drawOctagon(Shader shader,glm::vec3 position);
    void drawRoof(Shader shader,glm::vec3 position);
    void drawCylinder(Shader shader,glm::vec3 position);
    void drawSphere(Shader shader,glm::vec3 position);
    void drawOutside(Shader shader,glm::vec3 position);
    void drawGate(Shader shader, glm::vec3 position);
    void drawWall(Shader shader, glm::vec3 position,glm::vec3 scale);
private:
    Shape shape;
    void drawCubes(glm::mat4 model, Shader shader) {
        std::vector<TexVertex>vertices = shape.texCube1;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model,glm::vec3(0.3f));
        model = glm::translate(model, glm::vec3(-2.0f, -1.2f, 0.0f));
        int count = 8;
        float xpos = 0.0f;
        while (count--) {
            model = glm::translate(model, glm::vec3(xpos, 0.0f, 0.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
            xpos += 0.1f;
        }
        vertices = shape.texRegtangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    }
    void drawWallside(Shader shader, glm::vec3 position,glm::mat4 model,glm::vec3 scale);
    void drawMiniwall(Shader shader, glm::vec3 position,glm::mat4 model,glm::vec3 scale);
};
void Renderer::clear() const{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::bind(unsigned int VAO, unsigned int VBO, Shader shader) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
}
void Renderer::drawOctagon(Shader shader,glm::vec3 position) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    for (int i = 0; i < 7; i++) {
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
}
void Renderer::drawRoof(Shader shader,glm::vec3 position ) {
    std::vector<TexVertex> vertices = shape.texTriangle;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    for (int i = 0; i < 7; i++) {
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
}
void Renderer::drawCylinder(Shader shader,glm::vec3 position) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::translate(model, glm::vec3(0.0, 4.0f, 3.8f));
    model = glm::scale(model, glm::vec3(2.0f, 2.5f, 2.0f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    for (int i = 0; i < 15; i++) {
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(24.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
}
void Renderer::drawSphere(Shader shader,glm::vec3 position) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,position);
    model = glm::translate(model, glm::vec3(0.0, 6.0f, 3.69f));
    model = glm::scale(model, glm::vec3(0.95, 1.425, 0.95f));
    for (int i = 0; i < 32; i++) {
        glm::mat4 temp = model;
        shader.setVec3("u_Color", glm::vec3(1.0f, 0.8f, 0.0f));
        drawCubes(model, shader);
        if (i % 8 == 0) {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.45f));
            drawCubes(model, shader);
            model = temp;
        }
        shader.setVec3("u_Color", glm::vec3(1.0f, .647f, 0.0f));
        for (int j = 0; j < 24; j++) {
            model = glm::translate(model, glm::vec3(0.0f, .25f, 0.0f));
            model = glm::rotate(model, glm::radians(7.5f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::translate(model, glm::vec3(0.0f, .25f, 0.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        }
        model = temp;
        model = glm::translate(model, glm::vec3(-.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(11.25f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
}
void Renderer::drawWallside(Shader shader, glm::vec3 position,glm::mat4 model,glm::vec3 scale) {
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
   // glm::mat4 model = glm::mat4(1.0f);
   // model = glm::translate(model, position);
    //model = glm::scale(model, scale);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.3f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));

    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //fuc
    for (int i = 0; i < 9; i++) {
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        drawMiniwall(shader, position, model,scale);
    }
}
void Renderer::drawMiniwall(Shader shader, glm::vec3 position,glm::mat4 model,glm::vec3 scale) {
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
   // model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.5f));
    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));

    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //fuc
    
}
void::Renderer::drawWall(Shader shader, glm::vec3 position,glm::vec3 scale) {
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (int i = 0; i < 4; i++) {
        drawWallside(shader, position,model,scale);
        model = glm::translate(model, glm::vec3(-10.5f, 0.0f, -3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-4.4f, 0.0f, 0.0f));
    }
}
void Renderer::drawGate(Shader shader, glm::vec3 position) {
    std::vector<TexVertex> vertices = shape.arch;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
    for (int i = 0; i < 2; i++) {
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.6f));
    }
}
#endif