#include <stdio.h> 
#include <stdlib.h>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <shader.h>
#include <texture.h>
#include <object.h>
#include <game.h>

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void create_objects(GameState & gs);
void test_collision(GameState & gs);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    srand( time(NULL));
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable blending
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float ar = static_cast<float>(SCR_WIDTH)/static_cast<float>(SCR_HEIGHT);
    GameState gs(ar);
    create_objects(gs);
    //test_collision(gs);

    float oldTime, curTime, dt;
    oldTime = glfwGetTime();
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // Time logic
        curTime = glfwGetTime();
        dt = curTime-oldTime;
        oldTime = curTime;

        // input
        gs.processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(!gs.pause){
            gs.physics(dt);
        }

        // render container
        gs.render();

        // glfw: swap buffers and poll IO events 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate
    glfwTerminate();
    return 0;
}


// glfw: whenever the window size changed this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void test_collision(GameState& gs){
    gs.add_obj(glm::vec2 (0.01f,0.01f), // pos
               glm::vec2 (0.3f,0.3f),  // size
               glm::vec2 (0.1f,0.1f),  // vel
               glm::vec3 (0.0f,0.0f,0.0f));
    gs.add_obj(glm::vec2 (0.0f,0.0f), // pos
               glm::vec2 (0.3f,0.3f),
               glm::vec2 (-0.1f,-0.1f),
               glm::vec3 (1.0f,1.0f,1.0f));
}

void create_objects(GameState& gs){
    int N = 100;
    for(int i = 0; i < N; i++){
        gs.add_obj_rand();
    }
}

