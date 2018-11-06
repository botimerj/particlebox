#include <iostream>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

int main(){
    std::cout << "Physics practice" << std::endl;

    glm::vec2 a(1.0f,1.0f);
    glm::vec2 b(0.0f,0.0f);

    std::cout << "a = [" << a.x << "," << a.y << "]" << std::endl;
    std::cout << "b = [" << b.x << "," << b.y << "]" << std::endl;
    
    float dist = l2Norm(glm::vec3(a,0.0f),glm::vec3(b,0.0f));
    float dist1 = distance(a,b);
    float adotb = dot(a,b);
    std::cout << "dist = " << dist1 << std::endl;
    std::cout << "dot  = " << adotb << std::endl;

    return 0;
}
