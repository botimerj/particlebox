#include <game.h>

GameState::GameState(float aspect_ratio){
    // Load Shader
    shaders = new Shader[1];
    this->shaders[0].init("shader/shader4.vs", "shader/shader4.fs");

    // Load Texture
    textures = new Texture2D[2];
    int width, height, nrChannels;
    unsigned char *data;
    data = stbi_load("textures/circle.png", &width, &height, &nrChannels, 0);
    this->textures[0].init(data, width, height, true);
    stbi_image_free(data);
    data = stbi_load("textures/square.png", &width, &height, &nrChannels, 0);
    this->textures[1].init(data, width, height, true);
    stbi_image_free(data);

    // Set the projection matrix for rendering
    this->aspect_ratio = aspect_ratio;
    this->projection = glm::ortho( -this->aspect_ratio, this->aspect_ratio, 
                                   1.0f, -1.0f, 
                                  -1.0f, 1.0f);
    this->shaders[0].use();
    this->shaders[0].SetMatrix4f("projection", projection);

    // init game state
    this->pause = true;

    // Init objects
    this->numObj = 0;
    this->maxObj = 1;
    this->obj = new Object[1]; 

}

GameState::~GameState(){
    delete[] shaders;
    delete[] textures;
    delete[] obj; 
}

void GameState::render(){
    for(int i = 0; i < this->numObj; i++){
        Shape shape = obj[i].shape;
        obj[i].draw(this->shaders[0],this->textures[shape]);
    }
}

void GameState::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->pause = !this->pause;

    // Player movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        obj[this->pid].vel.y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        obj[this->pid].vel.y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        obj[this->pid].vel.x -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        obj[this->pid].vel.x += 0.01;
}


void GameState::addObjRand(){
    // Add and object
    float VEL_MIN = -1.0;
    float VEL_MAX = 1.0;
    float POS_MIN = -1.0;
    float POS_MAX = 1.0;
    float _SIZE_MIN = 0.02;
    float _SIZE_MAX = 0.02;
    float COLOR_MIN = 0;
    float COLOR_MAX = 1;

    Object newObj;

    glm::vec2 pos(randf(POS_MIN,POS_MAX),randf(POS_MIN,POS_MAX));
    newObj.pos = pos;

    float size_in = this->randf(_SIZE_MIN,_SIZE_MAX);
    glm::vec2 size(size_in,size_in);
    newObj.size = size;

    glm::vec2 vel(this->randf(VEL_MIN,VEL_MAX),randf(VEL_MIN,VEL_MAX));
    newObj.vel = vel;

    glm::vec3 color(this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX),
                    this->randf(COLOR_MIN,COLOR_MAX));
    newObj.color = color;
    this->addObj(newObj);
}

void GameState::addObj(Object &objToAdd){

    // Double object list size
    if(this->numObj == maxObj){
        this->maxObj *= 2;
        Object *newObj; 
        newObj = new Object[maxObj];
        for(int i = 0; i < maxObj/2; i++){
            newObj[i].copy(obj[i]);
        }
        delete[] this->obj;
        this->obj = newObj;
    }

    this->obj[this->numObj].copy(objToAdd);
    if(objToAdd.player)
        pid = numObj;
    this->numObj++;
}

void GameState::physics(float dt){
    this->collisions();
    for(int i = 0; i < this->numObj; i++){
        obj[i].update(dt);
    }
}

void GameState::collisions(){
    // For each object in obj[] check for collision and update
    // velocity 
    for(int i = 0; i < numObj-1; i++){
        for(int j = i+1; j < numObj; j++){
            bool collision = false;
            float dist;
            if(obj[i].shape == CIRCLE){// shape 1 is a circle
                if(obj[j].shape == CIRCLE){ // both are circles 
                    circCirc(obj[i],obj[j]);
                }
                else{
                    sqrCirc(obj[j],obj[i]);
                }
            }else{ // shape 1 is a polygon
                if(obj[j].shape == CIRCLE){  
                    sqrCirc(obj[i],obj[j]);
                }else{ // both are squares
                    //glm::vec2 corners1[obj[i].num_corners];
                    //glm::vec2 corners2[obj[j].num_corners];
                    //obj[i].getCorners(corners1);
                    //obj[j].getCorners(corners2);
                    //collision = polyPoly(corners1, 4, corners2, 4);
                }
            }
        }
    }
}

void GameState::level1(){
    // Create a 'level'
    // Draw bounding box
    Object wall;
    wall.movable = false;
    wall.shape = SQUARE;
    
    // Top and Bottom walls
    wall.size = glm::vec2(this->aspect_ratio,0.5f);
    wall.pos = glm::vec2(0.0f,-1.5f);
    addObj(wall);
    wall.pos = glm::vec2(0.0f,1.5f);
    addObj(wall);
    // Left and Right walls
    wall.size = glm::vec2(0.5f,1.0f);
    wall.pos = glm::vec2(-this->aspect_ratio-0.5f,0.0f);
    addObj(wall);
    wall.pos = glm::vec2(this->aspect_ratio+0.5f,0.0f);
    addObj(wall);

    // Added Center walls
    float gap_size = 0.05;
    wall.size = glm::vec2(0.02f,0.5f-gap_size);
    wall.pos = glm::vec2(0.0f,0.5f+gap_size);
    addObj(wall);
    wall.pos = glm::vec2(0.0f,-0.5f-gap_size);
    addObj(wall);

    
    Object ball;
    ball.movable = true;
    ball.shape = CIRCLE;
    ball.size = glm::vec2(0.02f,0.02f);

    float VEL_MIN = -1.0;
    float VEL_MAX = 1.0;

    int N = 20;
    for(int i = 0; i < N; i++){
        ball.pos = glm::vec2(this->randf(0.1f,this->aspect_ratio),
                             this->randf(-1.0f,1.0f));
        ball.vel = glm::vec2(this->randf(VEL_MIN,VEL_MAX),
                             this->randf(VEL_MIN,VEL_MAX));
        addObj(ball);
    }

    VEL_MIN = -0.1;
    VEL_MAX = 0.1;

    for(int i = 0; i < N; i++){
        ball.pos = glm::vec2(this->randf(-this->aspect_ratio,-0.1f),
                             this->randf(-1.0f,1.0f));
        ball.vel = glm::vec2(this->randf(VEL_MIN,VEL_MAX),
                             this->randf(VEL_MIN,VEL_MAX));
        addObj(ball);
    }

    Object player;
    player.movable = true;
    player.shape = CIRCLE;
    player.player = true;
    player.size = glm::vec2(0.05f,0.05f);
    player.pos = glm::vec2(-0.5f,0.5f);
    addObj(player);

}

float GameState::randf(float a, float b){
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float diff = b - a;
    float r = random*diff;
    return a + r;
}

