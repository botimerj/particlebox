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

    void set(glm::vec2 pos,
             glm::vec2 size,
             glm::vec2 vel,
             glm::vec3 color);

    void draw(Shader &, Texture2D &);

    void update(float dt);
};

#endif
