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
	void drawOctagon(Shader shader);
    void drawRoof(Shader shader);
    void drawCylinder(Shader shader);
    void drawSphere(Shader shader);
private:
    Shape shape;
};
void Renderer::clear() const{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::bind(unsigned int VAO, unsigned int VBO, Shader shader) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
}
void Renderer::drawOctagon(Shader shader) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(TexVertex), vertices.data());
    glm::mat4 model = glm::mat4(1.0f);
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
void Renderer::drawRoof(Shader shader) {
    std::vector<TexVertex> vertices = shape.texTriangle;
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(TexVertex), vertices.data());
    glm::mat4 model = glm::mat4(1.0f);
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
void Renderer::drawCylinder(Shader shader) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(TexVertex), vertices.data());
    glm::mat4 model = glm::mat4(1.0f);
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
void Renderer::drawSphere(Shader shader) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(TexVertex), vertices.data());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 6.0f, 3.69f));
    model = glm::scale(model, glm::vec3(0.95, 1.425, 0.95f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    for (int i = 0; i < 32; i++) {
        glm::mat4 temp = model;
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
#endif