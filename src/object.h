#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <texture.h>

class Object{

public:
    unsigned int VAO;
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 vel;
    glm::vec3 color;

    Object();
    ~Object();

    void draw(Shader &, Texture2D &,
              glm::vec2,
              glm::vec2,
              glm::vec3);

    void update(float dt);
};

#endif
