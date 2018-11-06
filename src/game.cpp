#include <game.h>


GameState::GameState(float aspect_ratio){
    // Load Shader
    this->objShader.init("shader/shader4.vs", "shader/shader4.fs");

    // Load Texture
    int width, height, nrChannels;
    unsigned char *data;
    data = stbi_load("textures/circle.png", &width, &height, &nrChannels, 0);
    this->objTexture.init(data, width, height, true);
    stbi_image_free(data);

    // Set the projection matrix for rendering
    this->aspect_ratio = aspect_ratio;
    this->projection = glm::ortho( 0.0f, this->aspect_ratio, 
                                   1.0f, 0.0f, 
                                  -1.0f, 1.0f);
    this->objShader.use();
    this->objShader.SetMatrix4f("projection", projection);

    // init game
    this->pause = true;


    // Add and object
    float VEL_MIN = 0.1;
    float VEL_MAX = 0.5;
    float POS_MIN = 0.1;
    float POS_MAX = 0.5;
    float _SIZE_MIN = 0.1;
    float _SIZE_MAX = 0.2;
    float COLOR_MIN = 0;
    float COLOR_MAX = 1;

    glm::vec2 pos(randf(POS_MIN,POS_MAX),randf(POS_MIN,POS_MAX));
    float size_in = this->randf(_SIZE_MIN,_SIZE_MAX);
    glm::vec2 size(size_in,size_in);
    glm::vec3 color(this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX));
    glm::vec2 vel(this->randf(VEL_MIN,VEL_MAX),randf(VEL_MIN,VEL_MAX));
    this->obj.set(pos, size, vel, color);

}

GameState::~GameState(){
    // Nothin to do
}

void GameState::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->pause = !this->pause;
}


float GameState::randf(float a, float b){
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float diff = b - a;
    float r = random*diff;
    return a + r;
}
