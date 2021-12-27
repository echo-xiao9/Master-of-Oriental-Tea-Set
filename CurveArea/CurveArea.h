#include "shader.h"
#include "Button/Button.h"
#include <glm/gtc/matrix_transform.hpp>

#define LINENUM 101

float curvePoint[LINENUM*3];

class CurveArea{
private:
    glm::vec3 p0,p1,p2,p3,p4,p5;
    glm::vec3 b0,b1,b2,b3,b4,b5;

    float offsetX,initR,length;
    float normW,normH;
    int selected;//-1,0,1,2,3,4,5
    int screenW,screenH;
    glm::mat4 model;

    Button button;
    Shader pointShader;
	unsigned int pointVAO, pointVBO;
    unsigned int curveVAO, curveVBO;

    bool inRange(float normX,float normY,glm::vec3 p){
        float halfRangeW=15.0f/screenW,halfRangeH=15.0f/screenH;
        if(p.x-halfRangeW<=normX&&normX<=p.x+halfRangeW&&p.y-halfRangeH<=normY&&normY<=p.y+halfRangeH)
            return true;
        else
            return false;
    }
    glm::vec3 areaCurve(float t){
//        glm::vec3 b=b0*((float)pow(1-t,3))+b1*((float)(3*t*pow(1-t,2)))+b2*((float)(3*pow(t,2)*(1-t)))+b3*((float)pow(t,3));
        glm::vec3 b=b0*((float)pow(1-t,5))+b1*((float)(5*t*pow(1-t,4)))+b2*((float)(10*pow(t,2)*pow(1-t,3)))+b3*((float)(10*pow(t,3)*pow(1-t,2)))+b4*((float)(5*pow(t,4)*(1-t)))+b5*((float)pow(t,5));
        return b;
    }
    
    void updatePoint(float normX,float normY){
        float worldX=normX*length/normW/2,worldY=(normY/normH/2-0.5)*initR;
        switch(selected){
            case 0:b0=glm::vec3(normX,normY,0);p0=glm::vec3(worldX+offsetX,worldY,0);break;
            case 1:b1=glm::vec3(normX,normY,0);p1=glm::vec3(worldX+offsetX,worldY,0);break;
            case 2:b2=glm::vec3(normX,normY,0);p2=glm::vec3(worldX+offsetX,worldY,0);break;
            case 3:b3=glm::vec3(normX,normY,0);p3=glm::vec3(worldX+offsetX,worldY,0);break;
            case 4:b4=glm::vec3(normX,normY,0);p4=glm::vec3(worldX+offsetX,worldY,0);break;
            case 5:b5=glm::vec3(normX,normY,0);p5=glm::vec3(worldX+offsetX,worldY,0);break;
            default:break;
        }
    }
    void updateBuffer(){
        float point[]={
             b0.x,b0.y,0,
             b1.x,b1.y,0,
             b2.x,b2.y,0,
             b3.x,b3.y,0,
             b4.x,b4.y,0,
             b5.x,b5.y,0,
        };

        glm::vec3 p;
        for(int t=0;t<LINENUM;t++){
            p=areaCurve(t*0.01);
            curvePoint[t*3+0]=p.x;
            curvePoint[t*3+1]=p.y;
            curvePoint[t*3+2]=0;
        }

        glBindVertexArray(pointVAO);
		glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), &point, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);


        glBindVertexArray(curveVAO);
		glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(curvePoint), &curvePoint, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
    }
public:
    CurveArea(int screenWidth,int screenHeight,int width=100,int height=80,
    int posX=0,int posY=0,float offsetX=0.0f,float initR=1.5f,float length=6.0f)
    :button(Button("Button/bezier2.jpg",screenWidth,screenHeight,width,height,posX,posY))
    ,pointShader(Shader("CurveArea/Point.vs","CurveArea/Point.fs"))
    {
		this->offsetX=offsetX;
		this->initR=initR;
		this->length=length;
        this->screenW=screenWidth;
        this->screenH=screenHeight;
        this->selected=-1;
        
        normW=float(width)/screenWidth;
        normH=float(height)/screenHeight;

        model=glm::mat4(1.0f);
        glm::vec3 position(float(posX) *2 / screenWidth, float(posY) * 2 / screenHeight, 0);
        model=glm::translate(model,position);

        pointShader.use();
        pointShader.setMat4("model",model);

		glGenVertexArrays(1, &pointVAO);
		glGenBuffers(1, &pointVBO);
		glGenVertexArrays(1, &curveVAO);
		glGenBuffers(1, &curveVBO);

        p0=glm::vec3(length/2+offsetX,-initR,0.0f);
        p1=glm::vec3(length/3+offsetX,-initR/2,0.0f);
        p2=glm::vec3(length/4+offsetX, 0.0f, 0.0f);
        p3=glm::vec3(-length/4+offsetX, 0.0f, 0.0f);
        p4=glm::vec3(-length/3+offsetX,-initR/2,0.0f);
        p5=glm::vec3(-length/2+offsetX,-initR,0.0f);
        
        b0=glm::vec3(normW,-normH,0);
        b1=glm::vec3(5*normW/6,0,0);
        b2=glm::vec3(normW/3,normH,0);
        b3=glm::vec3(-normW/3,normH,0);
        b4=glm::vec3(-5*normW/6,0,0);
        b5=glm::vec3(-normW,-normH,0);
        
        updateBuffer();
    };
    ~CurveArea(){}
    void updateCurveArea(int mouseX,int mouseY){
        float normX=float(mouseX)*2/screenW,normY=float(mouseY)*2/screenH;
        if(selected==-1){
            cout<<"updateCurveArea selected:"<<selected<<endl;
            cout<<"normX:"<<normX<<" normY:"<<normY<<endl;
            if(inRange(normX,normY,b0))
                selected=0;
            else if(inRange(normX,normY,b1))
                selected=1;
            else if(inRange(normX,normY,b2))
                selected=2;
            else if(inRange(normX,normY,b3))
                selected=3;
            else if(inRange(normX,normY,b4))
                selected=4;
            else if(inRange(normX,normY,b5))
                selected=5;
            
        }
        updatePoint(normX,normY);
        updateBuffer();
    }
    void releaseSelect(){
        selected=-1;
    }
    glm::vec3 gerRealCurve(float t){
        // Bessel curve formula to the third power
        glm::vec3 v=p0*((float)pow(1-t,5))+p1*((float)(5*t*pow(1-t,4)))+p2*((float)(10*pow(t,2)*pow(1-t,3)))+p3*((float)(10*pow(t,3)*pow(1-t,2)))+p4*((float)(5*pow(t,4)*(1-t)))+p5*((float)pow(t,5));
        return v;
    }

    void drawCurveArea(){
        // draw the Bézier panel
		pointShader.use();
        glBindVertexArray(pointVAO);
        glPointSize(15);
		glDrawArrays(GL_POINTS, 0, 6);
		glBindVertexArray(0);

        glBindVertexArray(curveVAO);
        glLineWidth(3);
		glDrawArrays(GL_LINE_STRIP, 0, 101);
		glBindVertexArray(0);

        button.drawButton();
    }
};
