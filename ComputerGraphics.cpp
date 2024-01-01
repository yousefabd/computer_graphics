#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <Camera.h>
#include "Shape.h"
#include "Vertex.h"
#include "Renderer.h"
#include "Texture.h"
#include <bits/stdc++.h>
//textures
unsigned int wall;
unsigned int stone;
//textures

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::vec3 mosque_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 wall_position = glm::vec3(-20.0f, 0.0f, -10.0f);

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//Camera camera(glm::vec3(0.0f, 12.0f, 30.0f));
Camera camera(glm::vec3(0.0f,0.0f,0.0f));
bool firstMouse = true;

float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jerusalem", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shape shape;
    Renderer renderer;
    Texture texture; 
    unsigned int wall = texture.genTexture("images/wall.jpg");
    unsigned int stone = texture.genTexture("images/wall-windowed.jpeg");
    unsigned int mosque_wall = texture.genTexture("images/building-wall-outside.jpg");
    unsigned int mosque_roof = texture.genTexture("images/mosque_roof2.jpg");;
    unsigned int mosque_cylinder = texture.genTexture("images/cylinder.jpg");
    unsigned int stone_brick = texture.genTexture("images/stone-brick.jpg");
    unsigned int quartz = texture.genTexture("images/quartz.jpg");
    unsigned int sandstone_brick = texture.genTexture("images/sandstone-brick.jpg");
    unsigned int windowed_wall = texture.genTexture("images/wall-windowed.jpeg");
    unsigned int entrance_wall = texture.genTexture("images/entrance-wall.jpg");
    unsigned int entrance_wall2= texture.genTexture("images/arch-wall.jpg");
    unsigned int wall2 = texture.genTexture("images/wall2.jpg");
    unsigned int arch_frame = texture.genTexture("images/arch-frame.jpg");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<TexVertex> vertices = shape.texRegtangle;
    // world space positions of our cubes
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TexVertex), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));
    glEnableVertexAttribArray(2);
    ourShader.use();
    ourShader.setInt("mat.diffuse", 0);
    // vectors of stored textures
    std::vector<unsigned int> rockdomeTextures = { mosque_wall,mosque_roof,mosque_cylinder };
    std::vector<unsigned int> minaretTextures = { sandstone_brick,stone_brick};
    std::vector<unsigned int>mosqueTextures = { windowed_wall,entrance_wall2,wall2,sandstone_brick,arch_frame};
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        ourShader.setBool("useTexture", true);

        // input
        // -----
        processInput(window);
        // clear buffer and depth
        // ------
        renderer.clear();
        ourShader.use();

        glm::vec3 lightColor = glm::vec3(1.0f);
        glm::vec3 lightposition = wall_position;
        //lightposition = glm::vec3(lightposition.x * glm::cos(glm::radians(glfwGetTime())), lightposition.y, lightposition .z * glm::sin(glm::radians(glfwGetTime())));
        ourShader.setVec3("lightpos", lightposition);
        glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f, 0.5f, 0.31f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        ourShader.setVec3("light.ambient", ambientColor);
        ourShader.setVec3("light.diffuse", diffuseColor);
        ourShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setFloat("mat.shine", 0.5f);


        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        // render boxes
        renderer.drawRockDome(ourShader, texture, glm::vec3(1.0f), glm::vec3(0.2f), rockdomeTextures);
        renderer.bind(VAO,VBO,ourShader);
        texture.activate(stone, GL_TEXTURE0);
        renderer.drawGate(ourShader,wall_position);
        texture.activate(wall, GL_TEXTURE0);
        //renderer.drawWall(ourShader, mosque_position,glm::vec3(20.0f));
        //renderer.drawMinaret(ourShader,texture,glm::vec3(0.0f), glm::vec3(6.0f),minaretTextures);
        renderer.drawMosque(ourShader, texture, glm::vec3(3.0f), glm::vec3(3.0f), mosqueTextures);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}