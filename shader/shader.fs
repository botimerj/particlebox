#version 330 core

in vec2 TexCoord;
out vec4 color; 

uniform sampler2D image; 
uniform vec3 spriteColor;

void main(){
    color = texture(image, TexCoord)*vec4(spriteColor, 1.0);
}
