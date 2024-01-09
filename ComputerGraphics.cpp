#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include<Camera.h>
#include "Shape.h"
#include "Vertex.h"
#include "Renderer.h"
#include "Model.h"
#include "Texture.h"
#include <bits/stdc++.h>
//textures
unsigned int wall;
unsigned int stone;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::vec3 mosque_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 wall_position = glm::vec3(-20.0f, 0.0f, -10.0f);

// camera
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//Camera camera(glm::vec3(0.0f, 12.0f, 30.0f));
Camera camera(glm::vec3(1500.0f,0.0f,-1500.0f));
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
    Shader light_shader("light_cube.vs", "light_cube.fs");
    Shape shape;
    Shape cube_box;
    Texture cube_textures;
    Renderer renderer;
    //textures
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
    unsigned int sandstone = texture.genTexture("images/sandstone.jpg");
    unsigned int smooth_stone = texture.genTexture("images/smooth-stone.jpg");
    unsigned int mosque_cylinder2 = texture.genTexture("images/mosque-cylinder2.jpg");
    unsigned int rockdome_roof = texture.genTexture("images/rockdome-roof.jpg");
    unsigned int rockdome_wall = texture.genTexture("images/rockdome-wall.jpg");
    unsigned int smooth_quartz=texture.genTexture("images/smooth-quartz.jpg");
    unsigned int mosque_wall_inside = texture.genTexture("images/mosque-wall-inside.jpg");
    unsigned int mosque_wall_inside2 = texture.genTexture("images/test.jpg");
    unsigned int grass= texture.genTexture("images/grass.jpg");
    unsigned int garden_border= texture.genTexture("images/garden-border.jpg");
    //------------------------------------------------------------------------
    //cubebox stuff
    std::vector<std::string>faces{
        "images/box/clifflf.png",
        "images/box/cliffrt.png",
        "images/box/cliffup.png",
        "images/box/cliffdn.png",
        "images/box/cliffft.png",
        "images/box/cliffbk.png"
    };
    unsigned int cube_Sky = cube_textures.make_sky_box(faces);
    std::vector <float> cubebox_vertices = cube_box.sky_box_cube;
    unsigned int CVAO, CVBO;
    glGenVertexArrays(1, &CVAO);
    glBindVertexArray(CVAO);
    glGenBuffers(1, &CVBO);
    glBindBuffer(GL_ARRAY_BUFFER,CVBO);
    glBufferData(GL_ARRAY_BUFFER, 3, cubebox_vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    Shader Cube_box_shader("sky_box.vs", "sky_box.fs");
    Cube_box_shader.use();
    Cube_box_shader.setInt("sky", 0);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<TexVertex> vertices = shape.texRegtangle;
    // world space positions of our cubes
    unsigned int VBO, VAO, LVAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TexVertex), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1); 
    //normal vec attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
    glEnableVertexAttribArray(2);
    ourShader.use();
    ourShader.setInt("mat.diffuse", 0);

    glGenVertexArrays(1, &LVAO);
    glBindVertexArray(LVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TexVertex), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertex), (void*)0);
    glEnableVertexAttribArray(0);

    light_shader.use();
    // vectors of stored textures
    std::vector<unsigned int> rockdomeTextures = { mosque_wall,mosque_roof,mosque_cylinder,rockdome_roof,quartz,rockdome_wall,smooth_quartz};
    std::vector<unsigned int> minaretTextures = { sandstone_brick,stone_brick};
    std::vector<unsigned int>mosqueTextures = { windowed_wall,entrance_wall2,wall2,sandstone,smooth_stone,arch_frame,mosque_cylinder2,mosque_wall_inside,mosque_wall_inside2,quartz};
    std::vector<unsigned int>floortextures = { sandstone,quartz,grass,garden_border,smooth_stone};
    //Model tree("tree1_3ds/Tree1.3ds");
    Model tree("Tree/Tree.fbx");
    Model Gordon("Gordon/gordon.obj");
    Shader Mshader("model_vertex.vs", "model_fragment.fs");
    Mshader.use();
    camera.firstperson = false;
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
        //sky box
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5600.0f);
            glDepthMask(GL_FALSE);
            renderer.bind(CVAO, CVBO, Cube_box_shader);
            Cube_box_shader.use();
            texture.activate(cube_Sky, GL_TEXTURE0);
            glm::mat4 cube_view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
            Cube_box_shader.setMat4("view", cube_view);
            Cube_box_shader.setMat4("projection", projection);
            renderer.draw_sky_box(Cube_box_shader);
            glDepthMask(GL_TRUE);
        
        glBindVertexArray(VAO);
        ourShader.use();
        //lighting
        glm::vec3 lightColor = glm::vec3(1.0f-glfwGetTime()/255);
        glm::vec3 lightposition = glm::vec3(42.0f,200.0f,-15.0f);
        ourShader.setVec3("light.position", lightposition);
        glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        ourShader.setVec3("light.ambient", ambientColor);
        ourShader.setVec3("light.diffuse", diffuseColor);
        ourShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setVec3("matt2.diffuse", 1.0f, 1.0f, 1.0f);
        ourShader.setFloat("mat.shine", 0.5f);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        // render 
        renderer.bind(VAO, VBO, ourShader);
        renderer.drawRockDome(ourShader, texture, glm::vec3(39.5f, 1.3f, -45.5f),glm::vec3(155.0f), rockdomeTextures);
        renderer.drawWall(ourShader, texture,glm::vec3(10.0f,0.4f,-11.0f), glm::vec3(1150.0f), {wall});
        renderer.drawMinaret(ourShader,texture,glm::vec3(2.5f,0.0f,-24.8f), glm::vec3(450.0f,350.0f,450.0f),minaretTextures);
        renderer.drawMinaret(ourShader, texture, glm::vec3(25.5f, 0.0f, -24.8f), glm::vec3(450.0f, 350.0f, 450.0f), minaretTextures);
        renderer.drawMosque(ourShader, texture, glm::vec3(28.0f, 0.35f, -34.5f) , glm::vec3(265.0f,385.0f,265.0f), mosqueTextures);
        renderer.drawfloor(ourShader, texture, glm::vec3(1.0f,-120.0f,0.0f),glm::vec3(370.0f,1.0f,370.0f), floortextures);
        //render models
        Mshader.use();
        Mshader.setMat4("view", view);
        Mshader.setMat4("projection", projection);
        renderer.drawAllTrees(ourShader, glm::vec3(15.0f, -1.0f, -15.0f), glm::vec3(200.0f), tree);
        renderer.drawAllTrees(ourShader, glm::vec3(15.0f, -1.0f, -40.0f) , glm::vec3(200.0f), tree);
        renderer.drawAllTrees(ourShader, glm::vec3(40.0f, -1.0f, -15.0f) , glm::vec3(200.0f), tree);
        renderer.drawAllTrees(ourShader, glm::vec3(40.0f, -1.0f, -40.0f) , glm::vec3(200.0f), tree);
        
        ourShader.setMat4("model", model);
        if (!camera.firstperson) 
        {
            model = glm::translate(model, camera.GetPlayer());
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            ourShader.setMat4("model", model);
            Gordon.Draw(ourShader);  
        }
        
       // model = glm::scale(model, glm::vec3(0.01f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
      
        
        renderer.bind(LVAO, VBO, light_shader);
        light_shader.use();
        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection); 
        renderer.drawcube(light_shader, lightposition);
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
    float yoffset = lastY - ypos; 

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
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.firstperson = !camera.firstperson;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}