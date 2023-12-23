#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <Shader.h>
#include <glm/glm/glm.hpp>
class Renderer {
public:
	void clear() const;
	void bind(unsigned int VAO, unsigned int VBO, Shader shader);
	void drawOctagon(int size, Shader shader);
};
void Renderer::clear() const{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::bind(unsigned int VAO, unsigned int VBO, Shader shader) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
}
void Renderer::drawOctagon(int size,Shader shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(9.0f, 4.0f, 7.0f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, size);
    for (int i = 0; i < 7; i++) {
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, size);
    }
}
#endif