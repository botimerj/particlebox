#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <string>

//#ifndef STB_IMAGE_IMPLEMENTATION
//#define  STB_IMAGE_IMPLEMENTATION
//#include <stb_image/stb_image.h>
//#endif

class Texture2D{

public:
    unsigned int ID;
    bool alpha;
    Texture2D();
    Texture2D(unsigned char* data, int width, int height, bool EnableAlpha);
    void init(unsigned char* data, int width, int height, bool EnableAlpha);
    void bind() const;
};

#endif
