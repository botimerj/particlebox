#include <object.h>

Object::Object(){
    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    float vertices[] = {
         // Loc       // TexCoord
        -1.0f,  1.0f,  0.0f, 1.0f, 
         1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f, -1.0f,  0.0f, 0.0f, 
        -1.0f,  1.0f,  0.0f, 1.0f, 
         1.0f, -1.0f,  1.0f, 0.0f
    };

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);

    this->pos = glm::vec2(0.0f,0.0f);
    this->rot = 0;
    this->vel = glm::vec2(0.0f,0.0f);
    this->rot_vel = 0;
    this->size = glm::vec2(0.1f,0.1f);
    this->color = glm::vec3(1.0f,1.0f,1.0f);
    this->shape = CIRCLE;
    this->num_corners = 4;
    this->player = false;
    this->movable = true;
}

Object::~Object(){
    //glDeleteVertexArrays(1, &this->VAO);
}

void Object::copy(Object &objToCopy){
    this->pos = objToCopy.pos;
    this->rot = objToCopy.rot;
    this->vel = objToCopy.vel;
    this->rot_vel = objToCopy.rot_vel;
    this->size = objToCopy.size;
    this->color = objToCopy.color;
    this->shape = objToCopy.shape;
    this->num_corners = objToCopy.num_corners;
    this->player = objToCopy.player;
    this->movable = objToCopy.movable;
}


void Object::draw(Shader &shader, Texture2D &texture){ 
    
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos, 0.0f));
    model = glm::rotate(model, glm::radians(this->rot), glm::vec3(0.0,0.0,1.0));
    model = glm::scale(model, glm::vec3(this->size, 1.0f));

    if(this->movable && !this->player)
        this->vel2Color();
    shader.SetMatrix4f("model", model);
    shader.SetVector3f("color", this->color);
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Object::update(float dt){
    //if(this->movable)
    this->pos = this->pos + this->vel*dt;
    this->rot = this->rot + this->rot_vel*dt;
}

void Object::getCorners(glm::vec2 * corners){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos, 0.0f));
    model = glm::rotate(model, glm::radians(this->rot), glm::vec3(0.0,0.0,1.0));
    model = glm::scale(model, glm::vec3(this->size, 1.0f));

    glm::vec2 vert[] = {glm::vec2(-1.0f, 1.0f),
                        glm::vec2( 1.0f, 1.0f),
                        glm::vec2( 1.0f,-1.0f),
                        glm::vec2(-1.0f,-1.0f)
                       };
    glm::vec4 result;
    for(int i = 0; i < this->num_corners; i++){
        result = model*glm::vec4(vert[i].x,vert[i].y,0.0f,1.0f);
        corners[i] = glm::vec2(result.x, result.y);
    }
}


void Object::vel2Color(){
    float vel_max = glm::length(glm::vec2(1.0f,1.0f));
    float vel_mag = glm::length(this->vel);
    if(vel_mag > vel_max)
        vel_mag = vel_max;
    float red = vel_mag/vel_max;
    float blue = (vel_max-vel_mag)/vel_max;
    this->color = glm::vec3(red,0.0f,blue);
}

