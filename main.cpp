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
//void processInput(GLFWwindow *window);
//float randf(float a, float b);

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

    /*Object obj[N];
    for(int i = 0; i < N; i++){
        glm::vec2 pos(randf(POS_MIN,POS_MAX),randf(POS_MIN,POS_MAX));
        float size_in = randf(_SIZE_MIN,_SIZE_MAX);
        glm::vec2 size(size_in,size_in);
        glm::vec3 color(randf(COLOR_MIN,COLOR_MAX),
                        randf(COLOR_MIN,COLOR_MAX),
                        randf(COLOR_MIN,COLOR_MAX));
        glm::vec2 vel(randf(VEL_MIN,VEL_MAX),randf(VEL_MIN,VEL_MAX));
        obj[i].set(pos, size, vel, color);
    }*/
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
        gs.processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render container
        if(gs.pause){
            gs.obj.update(dt);
        }
        gs.obj.draw(gs.objShader, gs.objTexture);
        /*for(int i = 0; i < N; i++){
            obj[i].update(dt);
            obj[i].draw(ourShader, tex1);
        }*/

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react 
/*void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        pause = !pause;

}*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

