#ifndef WALL_H
#define WALL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <texture.h>
#include <cmath>

class Wall{
public:
    unsigned int VAO;
    glm::vec2 pos;
    glm::vec2 size; //length, width
    glm::vec3 color;

    Wall();
    ~Wall();

    void set(glm::vec2 pos,
             glm::vec2 size,
             glm::vec3 color);

    void draw(Shader &, Texture2D &);


};

#endif
