#include <texture.h> 

Texture2D::Texture2D(){
    // Do nothin
}
Texture2D::Texture2D(unsigned char* data, int width, int height, bool EnableAlpha){
    this->init(data,width,height,EnableAlpha);
}

void Texture2D::init(unsigned char* data, int width, int height, bool EnableAlpha){

    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, EnableAlpha ? GL_RGBA : GL_RGB,
                     width, height, 0, EnableAlpha ? GL_RGBA : GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

}

void Texture2D::bind() const{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
