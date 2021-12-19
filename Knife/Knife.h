#include "include/shader.h"
#include "include/model.h"
#include <glm/gtc/matrix_transform.hpp>

class Knife
{
private:
    Model sliceModel;
    Model holderModel;
    Model baseModel;
    Model gearModel;

    // utility function for loading a 2D texture from file
    // ---------------------------------------------------
    unsigned int knifeVAO, knifeVBO;
    unsigned int cubemapTexture;
public:
    Shader knifeShader;

    Knife(glm::vec3 lightPos, glm::vec3 viewPos): 
        knifeShader(Shader("Knife/Knife.vs", "Knife/Knife.fs")),
        sliceModel(Model("resources/Knife/knife_slice.obj")),
        holderModel(Model("resources/Knife/knife_holder.obj")),
        baseModel(Model("resources/Knife/knife_base.obj")),
        gearModel(Model("resources/Knife/knife_gear.obj"))

    {
        knifeShader.use();
        knifeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        knifeShader.setVec3("lightPos", lightPos);
        knifeShader.setVec3("viewPos", viewPos);
    }
    void drawKnife(glm::mat4 view, glm::mat4 projection, glm::mat4 model ,glm::mat4 rotate)
    {
        model = glm::scale(model, glm::vec3(0.2f));
        rotate = glm::rotate(rotate, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotate = glm::rotate(rotate, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


        knifeShader.use();
        knifeShader.setMat4("view", view);
        knifeShader.setMat4("projection", projection);
        knifeShader.setMat4("model", model);
        knifeShader.setMat4("rotate",rotate);

        sliceModel.Draw(knifeShader);
        holderModel.Draw(knifeShader);
        baseModel.Draw(knifeShader);
        gearModel.Draw(knifeShader);
    }
};
