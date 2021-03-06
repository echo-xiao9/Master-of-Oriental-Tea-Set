//
//  CurveArea2.hpp
//  Lathe-Simulation2
//
//  Created by 康艺潇 on 2021/12/30.
//

#ifndef CurveArea2_hpp
#define CurveArea2_hpp

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "const.h"

using namespace std;
using namespace glm;


class CurveArea2{
private:
    int controlNum=0;// control point num
    int bezierNum=0;// bezier curves num
    vector<glm::vec3> controlPoints;
    vector<glm::vec3> curvePoints;
    float* controlPointsData; // draw every curve with 4 points.
    float* curvePointsData;
    unsigned int pointVAO, pointVBO;
    unsigned int curveVAO, curveVBO;
    unsigned int lineVAO,  lineVBO;
    Shader pointShader;
    Shader curveShader;
    Shader testShader;
    unsigned int VBO, VAO;
    
public:
    
    struct controlLine{
        //一条直线的结构体，包含两个端点
            float x1,y1,x2,y2;
    };
    
        
    CurveArea2();
    ~CurveArea2(){};
    
    void addControlPoint(float mouseX, float mouseY);
    
    void genCurve(); // generate numth bezier curve
    void genCurvePoint(float t, vec3 p, vec3 p0, vec3 p1, vec3 p2, vec3 p3);
    
    void drawCurveArea();
    void drawPoint();
    void drawCurve();
    void drawControlLines();
    void updateBuffer();
    void genCurvePoint();
    void testDraw(){
        testShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 6);
    }
};




CurveArea2::CurveArea2():
    pointShader(Shader("CurveArea/ControlPoint.vs","CurveArea/ControlPoint.fs")),
    curveShader(Shader("CurveArea/ControlPoint.vs","CurveArea/ControlPoint.fs")),
    testShader(Shader("CurveArea/9.1.geometry_shader.vs", "CurveArea/9.1.geometry_shader.fs"))
{
//    glGenVertexArrays(1, &pointVAO);
//    glGenBuffers(1, &pointVBO);
////    glGenVertexArrays(1, &curveVAO);
////    glGenBuffers(1, &curveVBO);
////    glGenVertexArrays(1, &lineVAO);
////    glGenBuffers(1, &lineVBO);
//        controlPointsData=new float[1];
//        curvePointsData = new float[1];
//        updateBuffer();
    

    float points[] = {
        -0.5f,  0.5f, // 左上
         0.5f,  0.5f, // 右上
         0.5f, -0.5f, // 右下
        -0.5f, -0.5f  // 左下
        -2,-2,
        0,0,
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);


}

void CurveArea2::updateBuffer(){
//    cout<<"update buffer"<<endl;
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//    cout<<"controlNum"<<controlNum<<endl;
//    cout<<"sizeeof controlPointsData"<<sizeof(controlPointsData)<<endl;
//    glBufferData(GL_ARRAY_BUFFER,3*controlNum*4, &controlPointsData, GL_STATIC_DRAW);
    float testPoints[]={
        0.5,0.5,0.5,
        0.7,0.7,0.7,
        -0.3,-0.3,-0.3,
        0,0,0
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(testPoints), &testPoints, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
//
//    glBindVertexArray(curveVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(curvePointsData), &curvePointsData, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//
}



void CurveArea2::addControlPoint(float mouseX, float mouseY){
    
//    cout<<"addControlPoint"<<mouseX<<" "<<mouseY<<endl;
    if(controlPoints.size()&& mouseX==controlPoints[controlPoints.size()-1].x &&
       mouseY==controlPoints[controlPoints.size()-1].y )return;
    vec3 v(mouseX, mouseY,0);
    controlPoints.push_back(v);
    controlNum++;
    
    
    
    
    if(controlNum/4==0)bezierNum++;
//    cout<<"control num:"<<controlNum<<endl;
    
    
    delete []controlPointsData;
    delete []curvePointsData;
    controlPointsData=new float[controlPoints.size()*3];
    curvePointsData = new float[curvePoints.size()*3];
    for(int i=0;i<controlPoints.size();i++){
//        float clipX=controlPoints[i].x/SCR_WIDTH*2-1,clipY=1-y/SCR_HEIGHT*2;
//
        controlPointsData[3*i]=controlPoints[i].x;
        controlPointsData[3*i+1]=1-controlPoints[i].y;
        controlPointsData[3*i+2]=0;
    }
    for(int i=0;i<curvePoints.size();i++){
        controlPointsData[3*i]=curvePoints[i].x;
        controlPointsData[3*i+1]=curvePoints[i].y;
        controlPointsData[3*i+2]=0;
    }
    
    updateBuffer();
    
    
    
}

void CurveArea2::genCurve(){
    if(controlNum != 4*bezierNum){
        cout<<"controlNum != 4*bezierNum"<<endl;
        return;
    }
    for(int i=0;i<controlNum;i+=4){
        // generate points for every bezier curve.
        
        for(float j=0;j<LINE_NUM;j++){
            vec3 tmp;
            genCurvePoint(j/LINE_NUM, tmp, controlPoints[i],controlPoints[i+1],controlPoints[i+2],controlPoints[i+3]);
            curvePoints.push_back(tmp);
        }
    }
}

void CurveArea2::genCurvePoint(float t, vec3 p, vec3 p0, vec3 p1, vec3 p2, vec3 p3){
    p=p0*((float)pow(1-t,3))+p1*((float)(3*t*pow(1-t,2)))+p2*((float)(3*pow(t,2)*(1-t)))+p3*((float)pow(t,3));
}


void CurveArea2::drawCurveArea(){
    
    
    
    
   
    drawPoint();
    drawControlLines();
    drawCurve();
    
}

void CurveArea2::drawPoint(){
//    cout<<"start draw point,size:"<< controlNum<<endl;
    
//    cout<<"first point:"<<controlPointsData[0]<<' '<<controlPointsData[1]<<' '<<controlPointsData[2]<<endl;
//    cout<<"second point:"<<controlPointsData[3]<<' '<<controlPointsData[4]<<' '<<controlPointsData[5]<<endl;
    pointShader.use();
    glBindVertexArray(pointVAO);
    glPointSize(15);
    glDrawArrays(GL_POINTS, 0, controlNum);
    
//    glBindVertexArray(0);
    
//    curveShader.use();
//    glBindVertexArray(curveVAO);
//    glLineWidth(BEZIER_WIDTH);
//    glDrawArrays(GL_LINE_STRIP, 0, bezierNum*LINE_NUM);
//    glBindVertexArray(0);
//

}
void CurveArea2::drawCurve(){
    
}

void CurveArea2::drawControlLines(){
}
//



#endif /* CurveArea2_hpp */
