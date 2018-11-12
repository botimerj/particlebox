#include <collision.h>

/*bool polyCirc(glm::vec2 corners1[], int len1, glm::vec2 pos, float radius){
    // find parallel axis for shape 1
    for(int e = 0; e < len1; e++){
        // Find parallel axis
        glm::vec2 pa = corners1[(e+1)%len1] - corners1[e];

        // Calc all points projected onto PA from shape1 and find max and min
        float proj = glm::dot(pa,corners1[0]);
        float max1 = proj;
        float min1 = proj;
        for(int p = 0; p < len1; p++){
            proj = glm::dot(pa,corners1[p]);
            if(proj > max1)
                max1 = proj;
            if(proj < min1)
                min1 = proj;
        }
        // the min/max for a circle is just the projection of pos +/- the radius
        proj = glm::dot(pa,pos);
        float max2 = proj+radius;
        float min2 = proj-radius;

        std::cout << "edge" << e << " (" << min1 << " " << max1 << ") ("
                                         << min2 << " " << max2 << ")\n";

        //Check if there is overlap and return false if there is any gaps
        if(min1 < min2 && min2 > max1)
            return false;
        if(min2 < min1 && min1 > max2)
            return false;
    }

    return true;
}*/

void circCirc(Object &obj1, Object &obj2){
    float dist = distance(obj1.pos,obj2.pos);
    bool collision = (dist < obj1.size.x+obj2.size.x); 
    if(collision){
        //obj1.color = glm::vec3(0.0f,0.0f,1.0f);
        //obj2.color = glm::vec3(0.0f,1.0f,0.0f);
        
        glm::vec2 v1 = obj1.vel;
        glm::vec2 v2 = obj2.vel;
        glm::vec2 x1 = obj1.pos;
        glm::vec2 x2 = obj2.pos;
        obj1.vel = v1 - dot(v1-v2,x1-x2)/(dist*dist)*(x1-x2);
        obj2.vel = v2 - dot(v2-v1,x2-x1)/(dist*dist)*(x2-x1);
        
        float overlap = obj1.size.x+obj2.size.x-dist;
        obj1.pos = x1 + 0.5f*normalize(x1-x2)*overlap;
        obj2.pos = x2 + 0.5f*normalize(x2-x1)*overlap;
    } else {
        //obj1.color = glm::vec3(1.0f,1.0f,1.0f);
        //obj2.color = glm::vec3(1.0f,1.0f,1.0f);
    }
}


//bool sqrCirc(glm::vec2 pos1, glm::vec2 size1, glm::vec2 pos2, float radius){
void sqrCirc(Object &obj1, Object &obj2){
    glm::vec2 half_extents(obj1.size.x, obj1.size.y);
    glm::vec2 center2center = obj2.pos - obj1.pos;
    glm::vec2 clamped = glm::clamp(center2center, -half_extents, half_extents);

    glm::vec2 closest;
    glm::vec2 distance;
    float dist;
    float overlap;
    // Circle center is inside rectangle, just reverse time steps to back it out 
    while(clamped == center2center){
        obj2.pos = obj2.pos + obj2.vel*-0.005f;
        center2center = obj2.pos - obj1.pos;
        clamped = glm::clamp(center2center, -half_extents, half_extents);
    }
    closest = obj1.pos + clamped;
    distance = closest - obj2.pos;
    dist = glm::length(distance);
    overlap = dist - obj2.size.x;

    // Circle has intersected rectangle
    glm::vec2 v1 = obj1.vel;
    glm::vec2 v2 = obj2.vel;
    glm::vec2 x1 = closest;
    glm::vec2 x2 = obj2.pos;
    if(overlap < 0){
        //obj1.color = glm::vec3(0.0f,0.0f,1.0f);
        //obj2.color = glm::vec3(0.0f,1.0f,0.0f);
        if(obj1.movable){
            if(obj2.movable){
                obj1.pos -= normalize(distance)*overlap/2.0f;
                obj2.pos += normalize(distance)*overlap/2.0f;
                obj1.vel = v1 - dot(v1-v2,x1-x2)/(dist*dist)*(x1-x2);
                obj2.vel = v2 - dot(v2-v1,x2-x1)/(dist*dist)*(x2-x1);
            }else{
                obj1.pos -= normalize(distance)*overlap;
                obj1.vel = v1 - 2.0f*dot(v1-v2,x1-x2)/(dist*dist)*(x1-x2);
            }
        }else{
            if(obj2.movable){
                obj2.pos += normalize(distance)*overlap;
                obj2.vel = v2 - 2.0f*dot(v2-v1,x2-x1)/(dist*dist)*(x2-x1);
            }else{
                // Neither object can be moved
            }
        }
    } else { // No collision
        //obj1.color = glm::vec3(1.0f,1.0f,1.0f);
        //obj2.color = glm::vec3(1.0f,1.0f,1.0f);
    }
}


bool polyPoly(glm::vec2 corners1[], int len1, glm::vec2 corners2[], int len2){

    // find parallel axis for shape 1
    for(int e = 0; e < len1; e++){
        // Find parallel axis
        glm::vec2 pa = corners1[(e+1)%len1] - corners1[e];

        // Calc all points projected onto PA from shape1 and find max and min
        float proj = glm::dot(pa,corners1[0]);
        float max1 = proj;
        float min1 = proj;
        for(int p = 0; p < len1; p++){
            proj = glm::dot(pa,corners1[p]);
            if(proj > max1)
                max1 = proj;
            if(proj < min1)
                min1 = proj;
        }
        // Calc all points projected onto PA from shape2 and find max and min
        proj = glm::dot(pa,corners2[0]);
        float max2 = proj;
        float min2 = proj;
        for(int p = 0; p < len2; p++){
            proj = glm::dot(pa,corners2[p]);
            if(proj > max2)
                max2 = proj;
            if(proj < min2)
                min2 = proj;
        }

        //Check if there is overlap and return false if there is any gaps
        if(min1 < min2 && min2 > max1)
            return false;
        if(min2 < min1 && min1 > max2)
            return false;
    }

    // find parallel axis for shape 2
    for(int e = 0; e < len2; e++){
        // Find parallel axis
        glm::vec2 pa = corners2[(e+1)%len2] - corners2[e];

        // Calc all points projected onto PA from shape1 and find max and min
        float proj = glm::dot(pa,corners1[0]);
        float max1 = proj;
        float min1 = proj;
        for(int p = 0; p < len1; p++){
            proj = glm::dot(pa,corners1[p]);
            if(proj > max1)
                max1 = proj;
            if(proj < min1)
                min1 = proj;
        }
        // Calc all points projected onto PA from shape2 and find max and min
        proj = glm::dot(pa,corners2[0]);
        float max2 = proj;
        float min2 = proj;
        for(int p = 0; p < len2; p++){
            proj = glm::dot(pa,corners2[p]);
            if(proj > max2)
                max2 = proj;
            if(proj < min2)
                min2 = proj;
        }

        //Check if there is overlap and return false if there is any gaps
        if(min1 < min2 && min2 > max1)
            return false;
        if(min2 < min1 && min1 > max2)
            return false;
    }
    return true;
}

