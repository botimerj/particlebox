#include <wall.h>

Wall::Wall(){
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
}

Wall::~Wall(){
    //glDeleteVertexArrays(1, &this->VAO);
}

void Wall::set(glm::vec2 pos,
                 glm::vec2 size,
                 glm::vec3 color){
    this->pos   = pos;
    this->size  = size;
    this->color = color;
}


void Wall::draw(Shader &shader, Texture2D &texture){ 
    
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos, 0.0f));
    model = glm::scale(model, glm::vec3(this->size, 1.0f));

    shader.SetMatrix4f("model", model);
    shader.SetVector3f("color", this->color);
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
