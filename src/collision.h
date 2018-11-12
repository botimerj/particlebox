#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <object.h>

//bool polyCirc(glm::vec2 corners1[], int len1, glm::vec2 pos, float radius);
//bool sqrCirc(glm::vec2 pos1, glm::vec2 size1, glm::vec2 pos2, float radius);
void circCirc(Object &obj1, Object &obj2);
void sqrCirc(Object &obj1, Object &obj2);
bool polyPoly(glm::vec2 corners1[], int len1, glm::vec2 corners2[], int len2);

#endif
