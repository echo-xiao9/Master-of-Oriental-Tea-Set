#include "shader.h"
#include "model.h"
#include <glm/gtc/matrix_transform.hpp>

class Base
{
private:
    Model baseModel;

    unsigned int baseVAO, baseVBO;
    unsigned int cubemapTexture;
public:
    Shader baseShader;

    Base(glm::vec3 lightPos, glm::vec3 viewPos): 
        baseShader(Shader("Base/Base.vs", "Base/Base.fs")),
        baseModel(Model("resources/Base/Base.obj"))
    {
        baseShader.use();
        baseShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        baseShader.setVec3("lightPos", lightPos);
        baseShader.setVec3("viewPos", viewPos);
    }
    void drawBase(glm::mat4 view, glm::mat4 projection, glm::mat4 model ,glm::mat4 rotate)
    {
        model = glm::translate(model,glm::vec3(-11.0f,0.0f,0.0f));
        model = glm::scale(model, glm::vec3(0.1f));
        rotate = glm::rotate(rotate, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));


        baseShader.use();
        baseShader.setMat4("view", view);
        baseShader.setMat4("projection", projection);
        baseShader.setMat4("model", model);
        baseShader.setMat4("rotate",rotate);

        baseModel.Draw(baseShader);
    }
};
