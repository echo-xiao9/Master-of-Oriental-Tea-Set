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
    Shader curveShader;
    unsigned int VBO, VAO;
    unsigned int curveVBO, curveVAO;
    float points[MAX_CTRL_POINT_DATA];
    float curvePoints[POINTS_IN_CURVES_DATA];
    int crtlPoint=0;
    int curves=0;
    float maxy=-100.0f;
    float miny=100.0f;
    Button bezierButton;
    map<float,float> ctrlPoints;
    
public:
    CurveArea3():testShader(Shader("CurveArea/9.1.geometry_shader.vs", "CurveArea/9.1.geometry_shader.fs")),curveShader(Shader("CurveArea/CurveShader.vs", "CurveArea/CurveShader.fs")),bezierButton("Button/bezier2.png",SCR_WIDTH,SCR_HEIGHT,buttonWidth,4*buttonHeight, buttonOffsetX,buttonOffsetY+buttonDist){
        
        for(int i=0;i<MAX_CTRL_POINT_DATA;i++)points[i]=2.0f;
        for(int i=0;i<POINTS_IN_CURVES_DATA;i++)curvePoints[i]=2.0f;

        
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
        glGenBuffers(1, &curveVBO);
        glGenVertexArrays(1, &curveVAO);
        glBindVertexArray(curveVAO);
        glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(curvePoints), &curvePoints, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
        
        
    }
    
    void reset(){
        for(int i=0;i<MAX_CTRL_POINT_DATA;i++)points[i]=2.0f;
        for(int i=0;i<POINTS_IN_CURVES_DATA;i++)curvePoints[i]=2.0f;
        crtlPoint=0;
        curves=0;
        ctrlPoints.clear();
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glGenBuffers(1, &curveVBO);
        glGenVertexArrays(1, &curveVAO);
        glBindVertexArray(curveVAO);
        glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(curvePoints), &curvePoints, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
    }
    
    
    void testDraw(){
       
        testShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, crtlPoint*2);
        
        curveShader.use();
        glBindVertexArray(curveVAO);
        glDrawArrays(GL_POINTS, 0, curves*POINTS_IN_CURVE*2);
        //test
//        glDrawArrays(GL_POINTS, 0, 200);
        
        bezierButton.drawButton();
    }
    
    void addPoint(float newX, float newY){
        
//        if(ctrlPoints[newX]==newY)return;
        if(newX<=0.0f || newX>=1.0f ||newY<=-1.0f || newY>=1.0f)return;
        
        else ctrlPoints.insert({newX,newY});
//        else return;
        
        
        points[2*crtlPoint]=newX;
        points[2*crtlPoint+1]=newY;
        crtlPoint++;
        if(newY>maxy)maxy=newY;
        if(newY<miny)miny=newY;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        
        if(crtlPoint%4==0){
            // every curve is controlled by 4 points
            // need to add one curve
            float x0=points[curves*4*2];
            float y0=points[curves*4*2+1];
            float x1=points[curves*4*2+2];
            float y1=points[curves*4*2+3];
            float x2=points[curves*4*2+4];
            float y2=points[curves*4*2+5];
            float x3=points[curves*4*2+6];
            float y3=points[curves*4*2+7];
            
            for(int i=0;i<POINTS_IN_CURVE;i++){
                float fi=i;
                float t = fi/POINTS_IN_CURVE; // Calculate the points to plot the curve
                float x,y=0;
                getPosition(t, x, y, x0, y0, x1, y1, x2, y2, x3, y3);
                curvePoints[2*curves*POINTS_IN_CURVE+2*i]=x;
                curvePoints[2*curves*POINTS_IN_CURVE+2*i+1]=y;
            }
            curves++;
            // generate and bind the buffer
            glGenBuffers(1, &curveVBO);
            glGenVertexArrays(1, &curveVAO);
            glBindVertexArray(curveVAO);
            glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
            //  glBufferData function copies the previously defined vertex data into the buffer's memory
            glBufferData(GL_ARRAY_BUFFER,sizeof(curvePoints), &curvePoints, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
            
            // use the latest control point of this curve as the first control point of next one.
            addPoint(x3,y3);
        }
    }
    
    
   


    bool getRadius(float radius[]){
        if(curves==0)return false;
        int n = rNum/curves;
        float x0=0,y0=0,x1=0,y1=0,x2=0,y2=0,x3=0,y3=0,x=0,y=0;
        for(int i=0;i<curves;i++){
            // get four point control curve i
            getCtrlPoint(i, x0, y0, x1, y1, x2, y2, x3, y3);
            for(int j=0;j<n && (i*n+j)<rNum+1 ;j++){
                float fj=j;
                float t=fj/n;
                getPosition(t,x,y,x0,y0,x1,y1,x2,y2,x3,y3);
                //calculate the radius array
                radius[i*n+j]=worldXtoRadius(x);
            }
        }
        float max=0;float min=1;
        for(int i=0;i<rNum;i++){
            if(radius[i]<min)min=radius[i];
            if(radius[i]>max)max=radius[i];
        }
        LENGTH = (maxy-miny)*LENGTH_SCALE;
//        cout<<"length:"<<LENGTH;
        return true;
        
    }
    
    void getCtrlPoint(int curveId,float &x0, float &y0, float &x1, float &y1, float &x2, float &y2, float &x3, float &y3){
        x0=points[curveId*2*4];
        y0=points[curveId*2*4+1];
        x1=points[curveId*2*4+2];
        y1=points[curveId*2*4+3];
        x2=points[curveId*2*4+4];
        y2=points[curveId*2*4+5];
        x3=points[curveId*2*4+6];
        y3=points[curveId*2*4+7];

    }
    void getPosition(float t,float &x, float &y, float x0, float y0, float x1, float y1, float x2, float y2, float x3,float y3){
        x=x0*((float)pow(1-t,3))+x1*((float)(3*t*pow(1-t,2)))+x2*((float)(3*pow(t,2)*(1-t)))+x3*((float)pow(t,3));
        y=y0*((float)pow(1-t,3))+y1*((float)(3*t*pow(1-t,2)))+y2*((float)(3*pow(t,2)*(1-t)))+y3*((float)pow(t,3));
    };
    
    float worldXtoRadius(float wx){
        float right=0.97f;
        float left=0.745715f;
        float scale = RADIUS/(right-left);
        float rx = (wx-left)*scale;
        return rx;
    }
    
    void saveCurve(){
        outfile << curves << endl;
        outfile << crtlPoint << endl;
        for(int i=0;i<crtlPoint;i++) outfile<< points[2*i]<<' '<< points[2*i+1]<<endl;
    }
   
    bool loadCurve(){
        int curves1,crtlPoint1;
        infile>>curves1 >> crtlPoint1;
        if(curves1==curves && crtlPoint1 == crtlPoint)return false;
        for(int i=0;i<crtlPoint1;i++){
            float x;float y;
            infile>>x>>y;
            if((i==0) || i%4!=0)addPoint(x,y);
            cout<<"load point:"<<x<<" "<<y<<endl;
        }
        cout<<"curves:"<<curves<<" curves1:"<<curves1<<endl;
        cout<<"crtlPoint:"<<crtlPoint<<" crtlPoint1:"<<crtlPoint1<<endl;
        return true;
    }
  
    
};
#endif /* CurveArea3_h */

