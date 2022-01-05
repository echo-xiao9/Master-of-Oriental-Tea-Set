//
//  CurveArea3.h
//  Lathe-Simulation2
//
//  Created by 康艺潇 on 2022/1/5.
//

#ifndef CurveArea3_h
#define CurveArea3_h



#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include "shader.h"
#include "const.h"

using namespace std;
using namespace glm;


class CurveArea3{
private:
    Shader testShader;
    unsigned int VBO, VAO;
    float points[MAX_CTRL_POINT];
    int crtlPoint=0;
    map<float,float> ctrlPoints;
public:
    CurveArea3():testShader(Shader("CurveArea/9.1.geometry_shader.vs", "CurveArea/9.1.geometry_shader.fs")){
        
        for(int i=0;i<MAX_CTRL_POINT;i++)points[i]=2.0f;
        //test
//        for(int i=0;i<crtlPoint*2;i++) points[i]=0.05*i;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    }
    void testDraw(){
        testShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, crtlPoint*2);
    }
    
    void addPoint(float newX, float newY){
        if(!ctrlPoints.count(newX))ctrlPoints.insert({newX,newY});
        else{
            if(ctrlPoints[newX]==newY)return;
        }
        points[2*crtlPoint]=newX;
        points[2*crtlPoint+1]=newY;
        crtlPoint++;
        
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
    }
    
    
    
    
    
    };



#endif /* CurveArea3_h */
