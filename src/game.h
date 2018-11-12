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
#include <glm/geometric.hpp>


#include <shader.h>
#include <texture.h>
#include <object.h>
#include <collision.h>

#include <stb_image/stb_image.h>

class GameState{
public:
    // Drawing things
    Shader    *shaders;
    Texture2D *textures;
    //Texture2D objTexture;
    //Texture2D squareTexture;
    //Texture2D circle_line;

    float aspect_ratio;
    glm::mat4 projection;

    // Game State
    bool pause;

    // Objects
    int numObj;
    int maxObj;
    Object * obj;
    // Player id
    unsigned int pid;


    // Gamestate functions
    GameState(float aspect_ratio); 
    ~GameState();
    void level1();

    void addObj(Object &objToAdd);
    void addObjRand();

    void physics(float dt);
    void render();

    void processInput(GLFWwindow *window);

    private: 
    void collisions();
    float randf(float a, float b);
    

};



#endif
