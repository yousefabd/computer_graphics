#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <Shader.h>
#include <glm/glm/glm.hpp>
#include "Shape.h"
#include "Vertex.h"
#include "Texture.h"
#include<Model.h>

class Renderer {
public:
	void clear() const;
	void bind(unsigned int VAO, unsigned int VBO, Shader shader);
    void drawRockDome(Shader, Texture,glm::vec3,glm::vec3,std::vector<unsigned int>);
    void drawGate(Shader,Texture,glm::vec3,glm::vec3,std::vector<unsigned int>);
    void drawWall(Shader,Texture, glm::vec3 ,glm::vec3,std::vector<unsigned int> );
    void drawMinaret(Shader ,Texture, glm::vec3 , glm::vec3 ,std::vector<unsigned int>);
    void drawMosque(Shader, Texture, glm::vec3, glm::vec3, std::vector<unsigned int>);
    void drawcube(Shader,glm::vec3);
    void draw_sky_box(Shader);
    void drawfloor(Shader, Texture, glm::vec3, glm::vec3, std::vector<unsigned int>);
    void drawAllTrees(Shader, glm::vec3, glm::vec3, Model);
    void drawHim(Shader, glm::vec3, glm::vec3, Model);

    
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
    void drawPillar(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.texCube1;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = glm::translate(model, glm::vec3(0.0f, .7f, 0.0f));
        model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.7f));
        shader.setMat4("model", model);
        glm::mat4 temp = model;
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = glm::translate(model, glm::vec3(0.0f, 61.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        model = temp;
        model = glm::scale(model, glm::vec3(0.17f, 10.0f, 0.17f));
        model = glm::translate(model,glm::vec3(0.0f,.55f,-2.5f));
        for (int i = 0; i < 6; i++) {
            drawCylinder(shader, model);
            model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
    void drawRectangle(Shader shader, glm::mat4 model) {
        std::vector<TexVertex> vertices = shape.texRegtangle;
        glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    void drawTree(Shader shader, glm::mat4 model, Model tree) {
        shader.use();
        shader.setMat4("model", model);
        tree.Draw(shader);
    }
    void drawGordon(Shader shader, glm::mat4 model, Model Gordon) {
            shader.use();
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
            shader.setMat4("model", model);
            Gordon.Draw(shader);  
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
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model,position);
    model = glm::translate(model, glm::vec3(0.0, 6.0f, 3.69f));
    model = glm::scale(model, glm::vec3(0.95, 1.425, 0.95f));
    shader.setBool("useTexture", false);
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
    //inside roof
    model = glm::scale(model, glm::vec3(0.98f, 0.98f, 0.98f));
    texture.activate(textures[3], GL_TEXTURE0);
    drawTriangles(shader, model);
    //floor
    model = glm::translate(model, glm::vec3(0.0f, -0.55f, 0.0f));
    model = glm::scale(model,glm::vec3(1.0f, 0.1f, 1.0f));
    texture.activate(textures[4], GL_TEXTURE0);
    drawTriangles(shader, model);
    model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(.08f, 0.6f, .08f));
    model = glm::translate(model, glm::vec3(0.3f,1.0f,9.0f));
    glm::mat4 temp = model;
    texture.activate(textures[6],GL_TEXTURE0);
    for (int i = 0; i < 8; i++) {
        drawPillar(shader, model);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-4.3f, 0.0f, -1.5f));
    }
    model = temp;
    //octgone
    texture.activate(mosque_wall, GL_TEXTURE0);
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(7.0f, 4.0f, 7.0f));
    drawOctagon(shader, model);
    model = glm::scale(model, glm::vec3(0.98f, 1.0f, 0.98f));
    model = glm::translate(model, glm::vec3(-0.02f, 0.0f, 0.02f));
    texture.activate(textures[5], GL_TEXTURE0);
    drawOctagon(shader, model);
}
void::Renderer::drawWall(Shader shader,Texture texture, glm::vec3 position,glm::vec3 scale,std::vector<unsigned int> textures) {
    texture.activate(textures[0], GL_TEXTURE0);
    std::vector<TexVertex> vertices = shape.texCube1;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
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
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
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
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //right wall outside
    texture.activate(textures[0], GL_TEXTURE0);
    drawWallSide2(shader, model,0.0f,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f),6,1);
    //right wall inside
    texture.activate(textures[7], GL_TEXTURE0);
    drawWallSide2(shader, model, 0.0f, glm::vec3(0.0f, 0.0f, .1f), glm::vec3(1.0f), 6, 1);
    texture.activate(textures[1], GL_TEXTURE0);
    //front wall outside
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.65f, 0.0f, -2.3f), glm::vec3(1.05f, 1.0f, 1.0f), 6, 1);
    //front wall inside
    texture.activate(textures[8], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.65f, 0.0f, -2.4f), glm::vec3(1.05f, 1.0f, 1.0f), 6, 1);
    //left wall outside
    texture.activate(textures[2], GL_TEXTURE0);
    drawWallSide2(shader, model, 0.0f, glm::vec3(0.0f, 0.2f, 8.9f), glm::vec3(1.0f, 1.3f, 1.0f), 6, 1);
    //left wall inside
    texture.activate(textures[7], GL_TEXTURE0);
    drawWallSide2(shader, model, 0.0f, glm::vec3(0.0f, 0.2f, 8.8f), glm::vec3(1.0f, 1.3f, 1.0f), 6, 1);
    //back wall inside
    texture.activate(textures[8], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.65f, 0.0f, -9.1f), glm::vec3(1.05f, 1.0f, 1.0f), 6, 1);
    //roof
    texture.activate(textures[3], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 4.5f, -0.71f), glm::vec3(1.05f, 7.4f, 4.0f), 6, 0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 5.17f, -1.0f), glm::vec3(1.05f, 1.75f, 5.0f), 6, 0);
    //floor
    texture.activate(textures[9], GL_TEXTURE0);
    drawWallSide2(shader, model, 90.0f, glm::vec3(0.0f, 4.5f, 0.8f), glm::vec3(1.05f, 7.4f, 4.0f), 6, 0);
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
    //inside decoration
    shader.setBool("useTexture", true);
    texture.activate(textures[3], GL_TEXTURE0);
    glm::mat4 source = model;
    float pos = 9.25f;
    for(int i = 0; i < 2; i++) {
        model = source;
        model = glm::translate(model, glm::vec3(11.2f, -7.1f, pos));
        model = glm::scale(model, glm::vec3(5.7f, 2.0f, 1.6f));
        drawArch(shader, model);
        for (int i = 0; i < 4; i++) {
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
            drawArch(shader, model);
        }
        model = glm::translate(model, glm::vec3(-0.46f, -2.0f, -0.28f));
        model = glm::scale(model, glm::vec3(0.2f, 0.076f, 0.8f));
        drawPillar(shader, model);
        float untrust = 0.0f;
        float inc = 0.2f;
        for (int i = 0; i < 4; i++) {
            model = glm::translate(model, glm::vec3(4.8f + untrust, 0.0f, 0.0f));
            drawPillar(shader, model);
            untrust += inc;
            inc /= 6.0f;
        }
        pos -= 14.0f;
    }
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
void Renderer::draw_sky_box(Shader shader) {
    std::vector<float> vertices = shape.sky_box_cube;
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Renderer::drawfloor(Shader shader, Texture texture, glm::vec3 position, glm::vec3 scale, std::vector<unsigned int>textures) {
    std::vector<TexVertex> vertices = shape.texRegtangle;
    unsigned int sandstone = textures[0];
    unsigned int quartz = textures[1];
    unsigned int grass = textures[2];
    unsigned int garden_border = textures[3];
    unsigned int smooth_stone = textures[4];
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);
    shader.setBool("useTexture", true);
    for (unsigned int i = 0; i < 32; i++) {
        for (unsigned int j = 0; j < 32; j++) {

            if (((i==5 or i==12 or i ==19 or i==26 ) and (j>=5 and j<= 12 or j>= 19 and j<=26)) or((j == 5 or j == 12 or j == 19 or j == 26) and (i >= 5 and i <= 12 or i >= 19 and i <= 26))) {
                texture.activate(garden_border, GL_TEXTURE0);
            }
            else if ((i >= 6 and i <= 11 or i >= 20 and i <= 25) and (j >= 6 and j <= 11 or j >= 20 and j <= 25)) {
                texture.activate(grass, GL_TEXTURE0);
            }
            else if (i == 15 or i == 16 or j == 15 or j == 16) {
                texture.activate(smooth_stone, GL_TEXTURE0);
            }
            else {
                texture.activate(sandstone, GL_TEXTURE0);
            }

            model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
            drawRectangle(shader, model);
        }
        model = glm::translate(model, glm::vec3(-32.0f, -1.0f, 0.0f));
    }
}
void Renderer::drawAllTrees(Shader shader, glm::vec3 pos, glm::vec3 scale, Model Trees) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, pos);
    
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            drawTree(shader, model, Trees);
            model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
        }
        model = glm::translate(model, glm::vec3(-8.0f, 0.0f, 1.0f));
    }

    

}
void Renderer::drawHim(Shader shader, glm::vec3 position, glm::vec3 scale, Model Gordon) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    
    drawGordon(shader,model,Gordon);
}


#endif