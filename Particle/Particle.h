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
    Particle(glm::vec3 _position,glm::vec3 _velocity){
        position=_position;
        velocity=_velocity;
        rotate = glm::mat4(1.0f);
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(1.0f, 0.0f, 0.0f));
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(0.0f, 1.0f, 0.0f));
        rotate = glm::rotate(rotate, glm::radians((float)(rand()%360)), glm::vec3(0.0f, 0.0f, 1.0f));
        
        size = (rand()%450+50)/3000.0;
        length = (rand()%450+50)/250.0;
        age==0;

        float vertices[] = {
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

        glGenVertexArrays(1, &particleVAO);
		glGenBuffers(1, &particleVBO);
		glBindVertexArray(particleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
    }
    ~Particle(){}
    void renderParticle(){
        glBindVertexArray(particleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
};

class ParticleSystem {
private:
    float gravity;
    std::vector<Particle> particles;
public:
    Shader particleShader;
    ParticleSystem(glm::vec3 lightPos,float _gravity=-9):
        particleShader("Particle/Particle.vs","Particle/Particle.fs"){
        gravity = _gravity;
        particleShader.use();
        particleShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        particleShader.setVec3("lightPos", lightPos);
        particleShader.setVec3("particleColor",0.7f,0.7f,0.7f);
    }
    ~ParticleSystem(){}
    void init() {
        this->particles.clear();
    }
    void changeColor(string texture){
        particleShader.use();
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
            iter->velocity = glm::vec3(iter->velocity.x,iter->velocity.y+gravity*dt,iter->velocity.z); 
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
