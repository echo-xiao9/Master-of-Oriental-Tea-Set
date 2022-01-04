#pragma once
#include "include/shader.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Particle {
private:
    unsigned int particleVAO, particleVBO;

public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::mat4 rotate;
    float size;
    float length;
    float age;
    Particle(glm::vec3 _position,glm::vec3 _velocity,int type=1){
        position=_position;
        velocity=_velocity;
        rotate = glm::mat4(1.0f);
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(1.0f, 0.0f, 0.0f));
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(0.0f, 1.0f, 0.0f));
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(0.0f, 0.0f, 1.0f));
        
        size = (rand()%450+50)/500.0;
//        length = (rand()%450+50)/250.0;
        age=0;

        float cube[] = { // type=1

            -length/2, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            length/2, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            length/2,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            length/2,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -length/2,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -length/2, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -length/2, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
            length/2, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
            length/2,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
            length/2,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
            -length/2,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
            -length/2, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.2f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.2f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.2f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.2f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.2f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.2f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.2f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.2f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.2f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.2f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.2f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.2f,  1.0f,  0.0f,  0.0f,

            -length/2, -0.5f, -0.2f,  0.0f, -1.0f,  0.0f,
            length/2, -0.5f, -0.2f,  0.0f, -1.0f,  0.0f,
            length/2, -0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            length/2, -0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            -length/2, -0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            -length/2, -0.5f, -0.2f,  0.0f, -1.0f,  0.0f,

            -length/2, 0.5f, -0.2f,  0.0f, -1.0f,  0.0f,
            length/2, 0.5f, -0.2f,  0.0f, -1.0f,  0.0f,
            length/2, 0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            length/2, 0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            -length/2, 0.5f,  0.2f,  0.0f, -1.0f,  0.0f,
            -length/2, 0.5f, -0.2f,  0.0f, -1.0f,  0.0f,
        };
        
        float leave[] = { // type=2
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            0.667f, 0.333f, -0.5f, 0.0f,  0.0f, -1.0f,
            1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            0.333f, 0.667f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f
            
        };
        
        float flower[] = { // type=3
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            0.667f, 0.333f, -0.5f, 0.0f,  0.0f, -1.0f,
            1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            0.333f, 0.667f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            -0.667f, 0.333f, -0.5f, 0.0f,  0.0f, -1.0f,
            -1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            -1.0f,   1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            -0.333f, 0.667f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            0.667f, -0.333f, -0.5f, 0.0f,  0.0f, -1.0f,
            1.0f,   -1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            1.0f,   -1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            0.333f, -0.667f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            -0.667f, -0.333f, -0.5f, 0.0f,  0.0f, -1.0f,
            -1.0f,   -1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            -1.0f,   -1.0f,-0.5f,0.0f,  0.0f, -1.0f,
            -0.333f, -0.667f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.0f,   0.0f, -0.5f,   0.0f,  0.0f, -1.0f,
            
        };
        float flower2[] ={ // type=4
            0.000, 0.000, -0.300, 0.0999, -0.2001,  0.167,
            0.667, 0.333, -0.300, 0.0999, -0.2001,  0.167,
            0.500, 0.500,  0.000, 0.0999, -0.2001,  0.167,
            0.500, 0.500,  0.000, 0.2001, -0.0999,  0.167,
            0.667, 0.333, -0.300, 0.2001, -0.0999,  0.167,
            1.000, 1.000, -0.300, 0.2001, -0.0999,  0.167,
            0.000, 0.000, -0.300, -0.2001,  0.0999,  0.167,
            0.500, 0.500,  0.000, -0.2001,  0.0999,  0.167,
            0.333, 0.667, -0.300, -0.2001,  0.0999,  0.167,
            0.500, 0.500,  0.000,  0.0999, -0.2001, -0.167,
            0.333, 0.667, -0.300,  0.0999, -0.2001, -0.167,
            1.000, 1.000, -0.300,  0.0999, -0.2001, -0.167,
            
            
            -0.000, 0.000, -0.300,  0.0999, 0.2001,  -0.167,
            -0.667, 0.333, -0.300,  0.0999, 0.2001,  -0.167,
            -0.500, 0.500,  0.000,  0.0999, 0.2001,  -0.167,
            -0.500, 0.500,  0.000,  0.2001, 0.0999,  -0.167,
            -0.667, 0.333, -0.300,  0.2001, 0.0999,  -0.167,
            -1.000, 1.000, -0.300,  0.2001, 0.0999,  -0.167,
            -0.000, 0.000, -0.300, -0.2001, -0.0999,-0.167,
            -0.500, 0.500,  0.000, -0.2001, -0.0999,-0.167,
            -0.333, 0.667, -0.300, -0.2001, -0.0999,-0.167,
            -0.500, 0.500,  0.000,  0.0999, 0.2001, 0.167,
            -0.333, 0.667, -0.300,  0.0999, 0.2001, 0.167,
            -1.000, 1.000, -0.300,  0.0999, 0.2001, 0.167,
            
            
            0.000, -0.000, -0.300, -0.0999, -0.2001, -0.167,
            0.667, -0.333, -0.300, -0.0999, -0.2001, -0.167,
            0.500, -0.500,  0.000, -0.0999, -0.2001, -0.167,
            0.500, -0.500,  0.000, -0.2001, -0.0999, -0.167,
            0.667, -0.333, -0.300, -0.2001, -0.0999, -0.167,
            1.000, -1.000, -0.300, -0.2001, -0.0999, -0.167,
            0.000, -0.000, -0.300,  0.2001,  0.0999, -0.167,
            0.500, -0.500,  0.000,  0.2001,  0.0999, -0.167,
            0.333, -0.667, -0.300,  0.2001,  0.0999, -0.167,
            0.500, -0.500,  0.000, -0.0999, -0.2001, 0.167,
            0.333, -0.667, -0.300, -0.0999, -0.2001, 0.167,
            1.000, -1.000, -0.300, -0.0999, -0.2001, 0.167,
            
            
            -0.000, -0.000, -0.300, -0.0999,  0.2001,  0.167,
            -0.667, -0.333, -0.300, -0.0999,  0.2001,  0.167,
            -0.500, -0.500,  0.000, -0.0999,  0.2001,  0.167,
            -0.500, -0.500,  0.000, -0.2001,  0.0999,  0.167,
            -0.667, -0.333, -0.300, -0.2001,  0.0999,  0.167,
            -1.000, -1.000, -0.300, -0.2001,  0.0999,  0.167,
            -0.000, -0.000, -0.300,  0.2001, -0.0999,  0.167,
            -0.500, -0.500,  0.000,  0.2001, -0.0999,  0.167,
            -0.333, -0.667, -0.300,  0.2001, -0.0999,  0.167,
            -0.500, -0.500,  0.000, -0.0999,  0.2001, -0.167,
            -0.333, -0.667, -0.300, -0.0999,  0.2001, -0.167,
            -1.000, -1.000, -0.300, -0.0999,  0.2001, -0.167
            
            
        };
        
    
        

        glGenVertexArrays(1, &particleVAO);
        glGenBuffers(1, &particleVBO);
        glBindVertexArray(particleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
        
        switch (type) {
            case 1:
                glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &cube, GL_STATIC_DRAW);
                break;
            case 2:
                glBufferData(GL_ARRAY_BUFFER, sizeof(leave), &leave, GL_STATIC_DRAW);
                break;
            case 3:
                glBufferData(GL_ARRAY_BUFFER, sizeof(flower), &flower, GL_STATIC_DRAW);
                break;
            default:
                glBufferData(GL_ARRAY_BUFFER, sizeof(flower2), &flower2, GL_STATIC_DRAW);
                break;
        }
        

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    ~Particle(){}
    void renderParticle(){
        glBindVertexArray(particleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 48);
        glBindVertexArray(0);
    }
};

class ParticleSystem {
private:
    float gravity;
    std::vector<Particle> particles;
    int type=1;
public:
    
    Shader particleShader;
    ParticleSystem(glm::vec3 lightPos,int type=1,float _gravity=-9):
        type(type),
        particleShader("Particle/Particle.vs","Particle/Particle.fs"){
        gravity = _gravity;
        particleShader.use();
            if(type==4)particleShader.setVec3("lightColor", 0.8f, 0.3f, 0.2f);
            else particleShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        particleShader.setVec3("lightPos", lightPos);
        particleShader.setVec3("particleColor",0.7f,0.7f,0.7f);
        
    }
    ~ParticleSystem(){}
    void init() {
        this->particles.clear();
    }
    void changeColor(string texture){
        particleShader.use();
        if(type==4){
            particleShader.setVec3("particleColor",0.7f,0.3f,0.3f);
            return;
        }
        if(texture=="iron")
            particleShader.setVec3("particleColor",0.7f,0.7f,0.7f);
        else
            particleShader.setVec3("particleColor",1.0f,227.0/256,148.0/256);
    }

    void simulate(float dt){
        aging(dt);
        updateParticle(dt);
    }
    void aging(float dt){
        for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();)
        {
            iter->age+=dt;
            if(iter->age>=2.0)
            {
                particles.erase(iter);
                continue;
            }
            iter++;
        }
    }
    void insertParticle(Particle p){
        particles.push_back(p);
    }
    void updateParticle(float dt){
        for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
        {
            iter->position = iter->position+iter->velocity*dt;
            iter->velocity = glm::vec3(iter->velocity.x,iter->velocity.y+gravity*dt/5,iter->velocity.z);
        }
    }
    
    void render(glm::mat4 view, glm::mat4 projection, glm::mat4 model ,glm::mat4 rotate){

        glm::mat4 startModel=model;
        particleShader.use();
        particleShader.setMat4("view", view);
        particleShader.setMat4("projection", projection);
        for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
        {

            model = glm::translate(startModel, iter->position);
            model = glm::scale(model,glm::vec3(iter->size));
            particleShader.setMat4("model", model);
            particleShader.setMat4("rotate",iter->rotate);
            iter->renderParticle();
        }
    }
};
