#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include <shader.h>
#include <texture.h>

enum Shape {CIRCLE, SQUARE};

class Object{

public:
    unsigned int VAO;
    glm::vec2 pos;
    float     rot;
    glm::vec2 vel;
    float     rot_vel;
    glm::vec2 size;
    glm::vec3 color;
    
    Shape shape;

    int num_corners;

    bool player;
    bool movable;

    Object();
    ~Object();

    void copy(Object &objToCopy);
    void draw(Shader &, Texture2D &);

    void update(float dt);
    void getCorners(glm::vec2 * corners);

private:
    void vel2Color();
};

#endif
