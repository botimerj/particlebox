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

#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float randf(float a, float b);


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

    // build and compile our shader zprogram
    Shader ourShader("shader/shader4.vs", "shader/shader4.fs");
    // Set orthographic projection for this shader
    ourShader.use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 
                                      static_cast<float>(SCR_HEIGHT), 0.0f, 
                                      -1.0f, 1.0f);
    ourShader.SetMatrix4f("projection", projection);

    // Enable blending
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Load Texture
    int width, height, nrChannels;
    unsigned char *data;
    data = stbi_load("textures/circle.png", &width, &height, &nrChannels, 0);
    Texture2D tex1(data, width, height, true);
    stbi_image_free(data);

    //glm::vec2 pos1(400.0f,300.0f);
    //glm::vec2 size1(50.0f,50.0f);
    //glm::vec3 color1(0.0f,1.0f,1.0f);
    //glm::vec2 pos2(200.0f,150.0f);
    //glm::vec2 size2(20.0f,20.0f);
    //glm::vec3 color2(1.0f,0.0f,1.0f);

    //glm::vec2 vel1(100.0f,120.0f);
    //glm::vec2 vel2(90.0f,-120.0f);

    // Create objects

    float VEL_MIN = -200;
    float VEL_MAX = 200;
    float POS_MIN = 100;
    float POS_MAX = 500;
    float _SIZE_MIN = 5;
    float _SIZE_MAX = 50;
    float COLOR_MIN = 0;
    float COLOR_MAX = 1;
    const int N = 1000;
    Object obj[N];
    for(int i = 0; i < N; i++){
        glm::vec2 pos(randf(POS_MIN,POS_MAX),randf(POS_MIN,POS_MAX));
        float size_in = randf(_SIZE_MIN,_SIZE_MAX);
        glm::vec2 size(size_in,size_in);
        glm::vec3 color(randf(COLOR_MIN,COLOR_MAX),
                        randf(COLOR_MIN,COLOR_MAX),
                        randf(COLOR_MIN,COLOR_MAX));
        glm::vec2 vel(randf(VEL_MIN,VEL_MAX),randf(VEL_MIN,VEL_MAX));
        obj[i].set(pos, size, vel, color);
    }
    //Object obj2(pos2, size2, vel2, color2);

    unsigned int count = 100;
    float oldTime, curTime, dt;
    oldTime = glfwGetTime();
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // Time logic
        curTime = glfwGetTime();
        dt = curTime-oldTime;
        oldTime = curTime;
        count++;
        if(count > 100){
            count = 0;
            std::cout << "dt: " << dt << std::endl;
        }

        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render container
        for(int i = 0; i < N; i++){
            obj[i].update(dt);
            obj[i].draw(ourShader, tex1);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react 
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

float randf(float a, float b){
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float diff = b - a;
    float r = random*diff;
    return a + r;
}

