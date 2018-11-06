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
    this->projection = glm::ortho( -this->aspect_ratio, this->aspect_ratio, 
                                   1.0f, -1.0f, 
                                  -1.0f, 1.0f);
    this->objShader.use();
    this->objShader.SetMatrix4f("projection", projection);

    // init game
    this->pause = true;
    this->numObj = 0;
    this->maxObj = 1;
   
    this->obj = new Object[1]; 
}

GameState::~GameState(){
    delete[] obj; 
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


void GameState::add_obj_rand(){
    // Add and object
    float VEL_MIN = 0.1;
    float VEL_MAX = 0.5;
    float POS_MIN = -1.0;
    float POS_MAX = 1.0;
    float _SIZE_MIN = 0.1;
    float _SIZE_MAX = 0.1;
    float COLOR_MIN = 0;
    float COLOR_MAX = 1;

    glm::vec2 pos(randf(POS_MIN,POS_MAX),randf(POS_MIN,POS_MAX));
    float size_in = this->randf(_SIZE_MIN,_SIZE_MAX);
    glm::vec2 size(size_in,size_in);
    glm::vec3 color(this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX));
    glm::vec2 vel(this->randf(VEL_MIN,VEL_MAX),randf(VEL_MIN,VEL_MAX));
    this->add_obj(pos, size, vel, color);
}


void GameState::add_obj(glm::vec2 pos,
                        glm::vec2 size,
                        glm::vec2 vel,
                        glm::vec3 color){

    // Double object size
    if(this->numObj == maxObj){
        this->maxObj *= 2;
        Object *newObj; 
        newObj = new Object[maxObj];
        for(int i = 0; i < maxObj/2; i++){
            newObj[i].set(obj[i].pos,
                          obj[i].size,
                          obj[i].vel,
                          obj[i].color);
        }
        delete[] this->obj;
        this->obj = newObj;
    }
    this->obj[this->numObj].set(pos, size, vel, color);
    this->numObj++;
}

void GameState::physics(float dt){
    this->collisions();
    for(int i = 0; i < this->numObj; i++){
        obj[i].update(dt);
    }
}

void GameState::render(){
    for(int i = 0; i < this->numObj; i++){
        obj[i].draw(this->objShader, this->objTexture);
    }
}

void GameState::collisions(){
    // For each object in obj[] check for collision and update
    // velocity 
    for(int i = 0; i < numObj-1; i++){
        for(int j = i+1; j < numObj; j++){
            // Detect overlap
            float dist = distance(obj[i].pos,obj[j].pos);
            if(dist < obj[i].size.x+obj[j].size.x){

                glm::vec2 v1 = obj[i].vel;
                glm::vec2 v2 = obj[j].vel;
                glm::vec2 x1 = obj[i].pos;
                glm::vec2 x2 = obj[j].pos;

                if(dist < 0.0001)
                    dist = 0.0001;
                glm::vec2 v1New = v1 - dot(v1-v2,x1-x2)/(dist*dist)*(x1-x2);
                glm::vec2 v2New = v2 - dot(v2-v1,x2-x1)/(dist*dist)*(x2-x1);

                obj[i].vel = v1New;
                obj[j].vel = v2New;
               
                // Position correction if objects overlap too much 
                //if (obj[i].size.x+obj[j].size.x-dist > 0)
                float overlap = obj[i].size.x+obj[j].size.x-dist;
                obj[i].pos = x1 + 0.1f*normalize(x1-x2)*overlap;
                obj[j].pos = x2 + 0.1f*normalize(x2-x1)*overlap;
            } 
        }
    }
}
