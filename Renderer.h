#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <Shader.h>
#include <glm/glm/glm.hpp>
class Renderer {
public:
	void clear() const;
	void bind(unsigned int VAO, unsigned int VBO, Shader shader);
	void drawOctagon(int size, glm::mat4 model, Shader shader);
};
void Renderer::clear() const{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::bind(unsigned int VAO, unsigned int VBO, Shader shader) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
}
void Renderer::drawOctagon(int size, glm::mat4 model, Shader shader) {
    model = glm::scale(model, glm::vec3(6.0f, 3.0f, 6.0f));
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