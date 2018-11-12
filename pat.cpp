
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// len1,2 >= 3
bool pat(glm::vec2 corners1[], int len1, glm::vec2 corners2[], int len2);

int main(){
    glm::vec2 corners1[] = {glm::vec2(1.0f,1.0f),
                            glm::vec2(2.0f,2.0f),
                            glm::vec2(1.0f,3.0f),
                            glm::vec2(0.0f,2.0f)
                            };
    glm::vec2 corners2[] = {glm::vec2(5.0f,1.0f),
                            glm::vec2(6.0f,2.0f),
                            glm::vec2(5.0f,3.0f),
                            glm::vec2(4.0f,2.0f)
                            };
    bool overlap = pat(corners1, 4, corners2, 4);
    std::cout << "Overlap : " << overlap << std::endl;


    return 0;
}



bool pat(glm::vec2 corners1[], int len1, glm::vec2 corners2[], int len2){

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
