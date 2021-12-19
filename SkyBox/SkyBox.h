#pragma once
#include "include/shader.h"
#include "include/stb_image.h"
#include <vector>
#include <SOIL/SOIL.h>

using namespace std;

float skyboxVertices[] = {
    // positions          
    -30.0f,  30.0f, -30.0f,
    -30.0f, -30.0f, -30.0f,
     30.0f, -30.0f, -30.0f,
     30.0f, -30.0f, -30.0f,
     30.0f,  30.0f, -30.0f,
    -30.0f,  30.0f, -30.0f,

    -30.0f, -30.0f,  30.0f,
    -30.0f, -30.0f, -30.0f,
    -30.0f,  30.0f, -30.0f,
    -30.0f,  30.0f, -30.0f,
    -30.0f,  30.0f,  30.0f,
    -30.0f, -30.0f,  30.0f,

     30.0f, -30.0f, -30.0f,
     30.0f, -30.0f,  30.0f,
     30.0f,  30.0f,  30.0f,
     30.0f,  30.0f,  30.0f,
     30.0f,  30.0f, -30.0f,
     30.0f, -30.0f, -30.0f,

    -30.0f, -30.0f,  30.0f,
    -30.0f,  30.0f,  30.0f,
     30.0f,  30.0f,  30.0f,
     30.0f,  30.0f,  30.0f,
     30.0f, -30.0f,  30.0f,
    -30.0f, -30.0f,  30.0f,

    -30.0f,  30.0f, -30.0f,
     30.0f,  30.0f, -30.0f,
     30.0f,  30.0f,  30.0f,
     30.0f,  30.0f,  30.0f,
    -30.0f,  30.0f,  30.0f,
    -30.0f,  30.0f, -30.0f,

    -30.0f, -30.0f, -30.0f,
    -30.0f, -30.0f,  30.0f,
     30.0f, -30.0f, -30.0f,
     30.0f, -30.0f, -30.0f,
    -30.0f, -30.0f,  30.0f,
     30.0f, -30.0f,  30.0f
};

class SkyBox {
private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int forestTexture,factoryTexture;
	string texture;

	unsigned int loadCubemap(vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

//		int width, height, nrComponents;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
//			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//			if (data)
//			{
//				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//                std::cout<<"load picture:"<<faces[i]<<endl;
//                 glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
//            }
//			else
//			{
//				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//			}
            
//			stbi_image_free(data);
            const char* path =faces[i].data();
            int texwidth,texheight,nrComponents=0;//nrChannels表示通道数，R/G/B/A，一共4个通道，有些图片只有3个，A即为alpha
            unsigned char *data = SOIL_load_image(path, &texwidth, &texheight, &nrComponents, SOIL_LOAD_RGB);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                if(data){
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                    std::cout<<"load picture:"<<faces[i]<<endl;
                }
                else
                    std::cout<<SOIL_last_result()<<std::endl;
                SOIL_free_image_data(data);
            
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

public:
	Shader forestShader,factoryShader;

	SkyBox():forestShader(Shader("SkyBox/Forest.vs", "SkyBox/Forest.fs")),
			factoryShader(Shader("SkyBox/Factory.vs", "SkyBox/Factory.fs")) {
		this->texture="factory";
		// skybox VAO
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// load textures
		// -------------
		vector<std::string> faces1
		{
//			"SkyBox/Forest/PX.jpg",//+x
//			"SkyBox/Forest/NX.jpg",//-x
//			"SkyBox/Forest/PY.jpg",//+y
//			"SkyBox/Forest/NY.jpg",//-y
//			"SkyBox/Forest/PZ.jpg",//+z
//			"SkyBox/Forest/NZ.png",//-z
            
           "skybox/Lake/right.jpg",
            "skybox/Lake/left.jpg",
            "skybox/Lake/top.jpg",
            "skybox/Lake/bottom.jpg",
            "skybox/Lake/front.jpg",
            "skybox/Lake/back.jpg"
		};
		forestTexture = loadCubemap(faces1);
		forestShader.use();
		forestShader.setInt("forest", 0);

		vector<std::string> faces2
		{
//			"SkyBox/Factory/PX.jpg",//+x
//			"SkyBox/Factory/NX.jpg",//-x
//			"SkyBox/Factory/PY.jpg",//+y
//			"SkyBox/Factory/NY.jpg",//-y
//			"SkyBox/Factory/PZ.jpg",//+z
//			"SkyBox/Factory/NZ.png",//-z
            "skybox/Lake/right.jpg",
             "skybox/Lake/left.jpg",
             "skybox/Lake/top.jpg",
             "skybox/Lake/bottom.jpg",
             "skybox/Lake/front.jpg",
             "skybox/Lake/back.jpg"
		};
		factoryTexture = loadCubemap(faces2);
		factoryShader.use();
		factoryShader.setInt("factory", 0);

	}

	void drawSkybox(glm::mat4 view, glm::mat4 projection) {
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		if(texture=="forest"){
			glBindTexture(GL_TEXTURE_CUBE_MAP, forestTexture);
		
    	    forestShader.use();
			forestShader.setMat4("view", view);
			forestShader.setMat4("projection", projection);
		} else
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, factoryTexture);
		
    	    factoryShader.use();
			factoryShader.setMat4("view", view);
			factoryShader.setMat4("projection", projection);
		}
		
		glBindVertexArray(skyboxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
	}

	void changeTexture(){
		texture=(texture=="factory")?"forest":"factory";
	}
};
