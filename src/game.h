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
   bool pause;
   float aspect_ratio;
   glm::mat4 projection;
   
   int numObj;
   Object obj;

   GameState(float aspect_ratio); 
   ~GameState();

    void processInput(GLFWwindow *window);
    float randf(float a, float b);


};

#endif
