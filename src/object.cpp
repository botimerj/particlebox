#include <object.h>

Object::Object(){
    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    /*GLfloat vertices[] = { 
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };*/

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

Object::~Object(){
    //glDeleteVertexArrays(1, &this->VAO);
}

void Object::draw(Shader &shader, Texture2D &texture, 
                  glm::vec2 position,
                  glm::vec2 size,
                  glm::vec3 color){
    
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.SetMatrix4f("model", model);
    shader.SetVector3f("color", color);
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

