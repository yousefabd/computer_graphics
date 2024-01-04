#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <Shader.h>
#include <glm/glm/glm.hpp>
#include "Shape.h"
#include "Vertex.h"
#include "Texture.h"

class Renderer {
public:
	void clear() const;
	void bind(unsigned int VAO, unsigned int VBO, Shader shader);
    void drawRockDome(Shader, Texture,glm::vec3,glm::vec3,std::vector<unsigned int>);
    void drawGate(Shader,Texture,glm::vec3,glm::vec3,std::vector<unsigned int>);
    void drawWall(Shader, glm::vec3 ,glm::vec3 );
    void drawMinaret(Shader ,Texture, glm::vec3 , glm::vec3 ,std::vector<unsigned int>);
    void drawMosque(Shader, Texture, glm::vec3, glm::vec3, std::vector<unsigned int>);
    void drawcube(Shader,glm::vec3);
private:
    Shape shape;
    void drawCubes(Shader shader,glm::mat4 model) {
        std::vector<TexVertex>vertices = shape.texCube1;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f));
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
    void drawWallside(Shader shader, glm::vec3 position, glm::mat4 model, glm::vec3 scale) {
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
            drawMiniwall(shader, position, model, scale);
        }
    }
    void drawMiniwall(Shader shader, glm::vec3 position, glm::mat4 model, glm::vec3 scale) {
        std::vector<TexVertex> vertices = shape.texCube1;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // model = glm::translate(model, position);
        model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.5f));
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));

        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //fuc

    }
    void drawArch(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.arch;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
    void drawTriangles(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.texTriangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
    void drawSphere(Shader shader, glm::mat4 model,glm::vec3 color) {
        std::vector<TexVertex> vertices = shape.texRegtangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        for (int i = 0; i < 32; i++) {
            glm::mat4 temp = model;
            shader.setVec3("u_Color", glm::vec3(color.x,color.y+0.075f,color.z));
            drawCubes(shader,model);
            if (i % 8 == 0) {
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.45f));
                drawCubes(shader,model);
                model = temp;
            }
            shader.setVec3("u_Color", color);
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
    void drawCylinder(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.texRegtangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
    void drawOctagon(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.texRegtangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
    void drawWallSide2(Shader shader, glm::mat4 model,float angle,glm::vec3 position,glm::vec3 scale,int count,bool axis) {
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f*!axis, 1.0f*axis, 0.0f));
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::scale(model, glm::vec3(1.4f, 1.2f, 0.1f));
        std::vector<TexVertex> vertices = shape.texCube1;
        for (int i = 0; i < count; i++) {
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        }
    }
};
void Renderer::clear() const{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::bind(unsigned int VAO, unsigned int VBO, Shader shader) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
}
void Renderer::drawRockDome(Shader shader,Texture texture,glm::vec3 position,glm::vec3 scale, std::vector<unsigned int> textures) {
    unsigned int mosque_wall = textures[0];
    unsigned int mosque_roof = textures[1];
    unsigned int mosque_cylinder = textures[2];
    //sphere
    shader.setBool("useTexture", false);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model,position);
    model = glm::translate(model, glm::vec3(0.0, 6.0f, 3.69f));
    model = glm::scale(model, glm::vec3(0.95, 1.425, 0.95f));
    drawSphere(shader, model, glm::vec3(1.0f, .647f, 0.0f));
    shader.setBool("useTexture", true);
    //cylinder
    texture.activate(mosque_cylinder, GL_TEXTURE0);
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::translate(model, glm::vec3(0.0, 4.0f, 3.8f));
    model = glm::scale(model, glm::vec3(2.0f, 2.5f, 2.0f));
    drawCylinder(shader, model);
    //roof
    texture.activate(mosque_roof, GL_TEXTURE0);
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
    drawTriangles(shader, model);
    //octgone
    texture.activate(mosque_wall, GL_TEXTURE0);
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
    drawOctagon(shader, model);
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
void Renderer::drawGate(Shader shader,Texture texture, glm::vec3 position,glm::vec3 scale,std::vector<unsigned int> textures) {
    for (int i = 0; i < 4; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        glm::mat4 temp = model;
        model = glm::scale(model, scale);
        drawArch(shader, model);
        model = glm::rotate(temp, glm::radians(90.0f), glm::vec3(-0.0f, 1.0f, 0.0f));
        model = glm::scale(model, scale);
        model = glm::translate(model, glm::vec3(-0.5, 0.0f, 5.0f));
        drawArch(shader, model);
        position.x += 10.0f;
    }
}
void Renderer::drawMinaret(Shader shader,Texture texture, glm::vec3 position, glm::vec3 scale,std::vector<unsigned int>textures) {
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    float x[4] = { 1.0f,1.0f,-1.0f,-1.0f };
    float z[4] = { 1.0f,-1.0f,1.0f,-1.0f };
    texture.activate(textures[0], GL_TEXTURE0);
    for (int i = 0; i < 5; i++) {
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glm::mat4 temp = model;
        for (int i = 0; i < 4; i++) {
            model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.4f));
            model = glm::translate(model, glm::vec3(x[i], 0.0f, z[i]));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
            model = temp;
        }
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    texture.activate(textures[1], GL_TEXTURE0);
    glm::mat4 temp = model;
    for (int i = 0; i < 4; i++) {
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.4f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.2f));
        drawArch(shader, model);
        model = glm::rotate(temp, glm::radians(90.0f*(i+1)), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(1.3f, 0.1f, 1.3f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    model = glm::scale(model, glm::vec3(0.1, 2.0f, 0.1f));
    model = glm::translate(model, glm::vec3(0.0f, 0.4f, -5.0f));
    drawSphere(shader, model,glm::vec3(0.0f));
}
void Renderer::drawMosque(Shader shader, Texture texture, glm::vec3 position, glm::vec3 scale, std::vector<unsigned int>textures) {
    std::vector<TexVertex>vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    shader.setBool("useTexture", true);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    texture.activate(textures[0], GL_TEXTURE0);

    drawWallSide2(shader, model,0.0f,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f),6,1);
    texture.activate(textures[1], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.65f, 0.0f, -2.3f), glm::vec3(1.05f, 1.0f, 1.0f), 6, 1);
    texture.activate(textures[2], GL_TEXTURE0);
    drawWallSide2(shader, model, 0.0f, glm::vec3(0.0f, 0.2f, 8.9f), glm::vec3(1.0f, 1.3f, 1.0f), 6, 1);
    texture.activate(textures[3], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 4.5f, -0.71f), glm::vec3(1.05f, 7.4f, 4.0f), 6, 0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 5.17f, -1.0f), glm::vec3(1.05f, 1.75f, 5.0f), 6, 0);
    texture.activate(textures[4], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 2.1f, -0.94), glm::vec3(1.05f, 3.37f, 0.5f), 6, 0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 5.14f, -1.3f), glm::vec3(1.05f, 1.69f, 0.5f), 6, 0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 7.6f, -0.94), glm::vec3(1.05f, 2.2f, 0.5f), 6, 0);

    texture.activate(textures[5], GL_TEXTURE0);
    glm::mat4 temp = model;
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.4f, 1.2f, 0.3f));
    model = glm::translate(model, glm::vec3(.48f, 0.0f, 2.85f));
    for (int i = 0; i < 5; i++) {
        drawArch(shader, model);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        if (i == 2) {
            model = glm::translate(model, glm::vec3(1.4f, 0.0f, 0.0f));
        }
    }
    model = glm::translate(model, glm::vec3(-3.2f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.4f, 1.0f, 1.0f));
    drawArch(shader, model);
    model = temp;
    model = glm::translate(model, glm::vec3(-2.2f, 0.0f, 0.6f));
    model = glm::scale(model, glm::vec3(1.4f, 1.2f, 0.3f));
    model = glm::translate(model, glm::vec3(.48f, 0.0f, 2.85f));
    for (int i = 0; i < 5; i++) {
        drawArch(shader, model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 4.72f));
        if (i == 2)
            model = model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.7f));
    }
        model = glm::translate(model, glm::vec3(-3.0f, 1.3f, -16.5f));
    model = glm::scale(model, glm::vec3(0.35f, 0.4f, 1.5f));
    texture.activate(textures[6],GL_TEXTURE0);
    drawCylinder(shader, model);
    model = glm::translate(model, glm::vec3(0.0f, .72f, 0.0f));
    model = glm::scale(model,glm::vec3(0.47f));
    shader.setBool("useTexture", false);
    drawSphere(shader, model,glm::vec3(0.55f,0.55f,0.55f));
}
void Renderer::drawcube(Shader shader, glm::vec3 pos) {
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    //model = glm::scale(model, glm::vec3(0.0f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

};

#endif