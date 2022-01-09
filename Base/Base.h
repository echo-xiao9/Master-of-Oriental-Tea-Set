#include "shader.h"
#include "model.h"
#include "const.h"
#include <glm/gtc/matrix_transform.hpp>

extern bool origin;

class Base
{
private:
    Model baseModel;
    Model baseModel2;
//    Model ground;
    
    unsigned int baseVAO, baseVBO;
    unsigned int cubemapTexture;
public:
    Shader baseShader;

    Base(glm::vec3 lightPos, glm::vec3 viewPos): 
        baseShader(Shader("Base/Base.vs", "Base/Base.fs")),
    baseModel(Model("resources/Dolphin/10014_dolphin_v2_max2011_it2.obj")),
    baseModel2(Model("resources/Dolphin/10014_dolphin_v2_max2011_it2.obj"))
//    ground(Model("/Users/kangyixiao/EchoFile/coding/MasterOfOrientalTeaSet/resources/Models/ground.rar/map_1.obj"))
    
//    ,ground(Model("/Users/kangyixiao/EchoFile/coding/MasterOfOrientalTeaSet/resources/Models/benzaiten/Benzaiten.obj"))
    {
        baseShader.use();
        baseShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        baseShader.setVec3("lightPos", lightPos);
        baseShader.setVec3("viewPos", viewPos);
    }
    
    void drawBase(glm::mat4 view, glm::mat4 projection, glm::mat4 model ,glm::mat4 rotate, float currentTime)
    {
        glm::mat4 oriModel = model;
        
//        drawGround( view,  projection, model , rotate,  currentTime);
        
        model = glm::translate(model,glm::vec3(7*sin(currentTime/2)-5.0f, 3*cos(currentTime/2)-1.0f,5*cos(currentTime/2)));
        model = glm::scale(model, glm::vec3(0.01f));
        
//        cout<<"currentTime:"<<currentTime<<endl;
//        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(20*currentTime), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        baseShader.use();
        baseShader.setMat4("view", view);
        baseShader.setMat4("projection", projection);
        baseShader.setMat4("model", model);
        baseShader.setMat4("rotate",rotate);
        if(origin)baseModel.Draw(baseShader);
        
        
        model = glm::translate(oriModel,glm::vec3(7*sin(currentTime/2)-5.0f, 3*sin(currentTime/2)-1.0f,5*cos(currentTime/2)));
        model = glm::scale(model, glm::vec3(0.01f));
//        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(10*currentTime), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        baseShader.setMat4("model", model);
        if(origin)baseModel2.Draw(baseShader);
    }
    
    void drawGround(glm::mat4 view, glm::mat4 projection, glm::mat4 model ,glm::mat4 rotate, float currentTime){
        baseShader.use();
        model = glm::translate(model,glm::vec3(0.0f, -6.0f,-20.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        model = glm::scale(model, glm::vec3(4.0f));
        baseShader.setMat4("view", view);
        baseShader.setMat4("projection", projection);
        baseShader.setMat4("model", model);
        baseShader.setMat4("rotate",rotate);
//        if(origin)ground.Draw(baseShader);
        
    }
    
    
};
