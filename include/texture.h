//
//  texture.cpp
//  OpenGLTest2
//
//  Created by 康艺潇 on 2021/12/15.
//
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include <iostream>
using namespace::std;
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    std::cout<<path<<std::endl;
    int width, height, nrComponents = 0;
    unsigned char *data = SOIL_load_image(path, &width, &height, &nrComponents, SOIL_LOAD_RGB);
//    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    // gamma
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height,  nrComponents, GL_RGB, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        cout<<"load data successfully"<<endl;
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        cout<<"nrComponents:"<<nrComponents<<endl;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        std::cout<<SOIL_last_result()<<std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}

void loadTextureSimple(char*path){
    int texwidth,texheight,nrComponents=0;//nrChannels表示通道数，R/G/B/A，一共4个通道，有些图片只有3个，A即为alpha
    unsigned char *data = SOIL_load_image(path, &texwidth, &texheight, &nrComponents, SOIL_LOAD_RGB);
    GLenum format;
    if (nrComponents == 1)
        format = GL_RED;
    else if (nrComponents == 3)
        format = GL_RGB;
    else if (nrComponents == 4)
        format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if(data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            std::cout<<SOIL_last_result()<<std::endl;
        SOIL_free_image_data(data);
    return ;
}
    

#endif
