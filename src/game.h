#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <cstdlib>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/geometric.hpp>


#include <shader.h>
#include <texture.h>
#include <object.h>

#include <stb_image/stb_image.h>

class GameState{
public:
    // Static things
    Shader objShader;
    Texture2D objTexture;

    // Dynamic things
    float aspect_ratio;
    glm::mat4 projection;

    bool pause;
    int numObj;
    int maxObj;
    Object * obj;

    GameState(float aspect_ratio); 
    ~GameState();

    void add_obj(glm::vec2 pos,
                 glm::vec2 size,
                 glm::vec2 vel,
                 glm::vec3 color);
    void add_obj_rand();

    void physics(float dt);
    void render();


    void processInput(GLFWwindow *window);
    float randf(float a, float b);

    private: 
    void collisions();

};



#endif
