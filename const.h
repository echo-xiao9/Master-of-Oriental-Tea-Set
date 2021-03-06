//
//  const.h
//  Lathe-Simulation2
//
//  Created by 康艺潇 on 2021/12/22.
//

#ifndef const_h
#define const_h
#include "camera.h"

#include <fstream>
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;

enum type{BEZIER,CURSOR,UNFIRED, FIRED};
enum select{AREA,MODE,START,RESET,TEXTURE,CHANGED,DISPLAY,NONE,FIRE,LIGHT,POINT,HOLLOW, SAVE,LOAD};

// button
const int buttonWidth=160,buttonHeight=45,buttonOffsetX=600,buttonOffsetY=220,buttonDist=70;

// control the points of the curve
int mouseX,mouseY;
bool ifstart=false;

// mode of program
type Mode = BEZIER;
type FIREMODE=UNFIRED;
select Select = NONE;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseControlCamera=true;
// tmp:set seen of base and knife
bool origin=1;



// light
glm::vec3 white(1.0f,1.0f,1.0f);
glm::vec3 pink(0.937f, 0.545f, 0.667f);
glm::vec3 green(0.271f,0.64f,0.216f);

glm::vec3 pink2(0.997f, 0.845f, 0.867f);
glm::vec3 pink3(0.937f, 0.845f, 0.867f);
glm::vec3 pink4(0.9f, 0.845f, 0.967f);
glm::vec3 blue2(0.85,0.81,0.97);
glm::vec3 blue3(0.8,0.8,1.0);
glm::vec3 blue4(0.75,0.8,1.0);
glm::vec3 lightColors[]={white, pink2, pink3,pink4,blue2,blue3,blue4};
int LIGHT_NUM=7;





// material
#define Pi 3.1416
#define eNum 360
#define rNum 800
#define fNum 9
float RADIUS = 3.0f;
int mtrIdx=0; // current material index




//#define fNum 15
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define textureNum 8

std::string textures[]={"wood","glass","glass","porcelain","porcelain2","tree","marble","wood2"};



// some utility function
float combine(int n, int m) {
    int i, j;
    float mat[100][100];
    if(m == 0 || n == m)
        return 1;

    for(j = 0; j <= m; j++) { // 只要计算n列就行了，不用计算后面的
        mat[j][j] = 1.0f;
        for(i = j+1; i <= n; i++) {
            if(j == 0)
                mat[i][j] = 1.0f;
            else
                mat[i][j] = mat[i-1][j-1] + mat[i-1][j];
        } // 计算Cmn
    }
    return mat[n][m];
}

//// curve area2
float BEZIER_WIDTH=2.0f;
float CRTL_LINE_WIDTH=2.0f;
float CRTL_POINT_SIZE=50.0f;
const int MAX_CURVE_NUM=20;
const int MAX_CTRL_POINT=MAX_CURVE_NUM*4;
const int MAX_CTRL_POINT_DATA=MAX_CTRL_POINT*2;
const int POINTS_IN_CURVE=100;
const int POINTS_IN_CURVES =POINTS_IN_CURVE*MAX_CURVE_NUM;
const int POINTS_IN_CURVES_DATA = POINTS_IN_CURVES*2;
const int LENGTH_SCALE=10.0f;



int LINE_NUM=100;




// particle
float PARTICLE_LIFE=10.0;



// read and save
ifstream infile;
ofstream outfile;
#endif /* const_h */
