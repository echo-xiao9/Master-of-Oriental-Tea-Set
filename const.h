//
//  const.h
//  Lathe-Simulation2
//
//  Created by 康艺潇 on 2021/12/22.
//

#ifndef const_h
#define const_h
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;

enum type{BEZIER,CURSOR,UNFIRED, FIRED};
enum select{AREA,MODE,START,RESET,TEXTURE,CHANGED,DISPLAY,NONE,FIRE};

// button
const int buttonWidth=160,buttonHeight=90,buttonOffsetX=600,buttonOffsetY=320,buttonDist=100;

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


// material
#define Pi 3.1416
#define eNum 360
#define rNum 800
#define fNum 9

int mtrIdx=0; // current material index




//#define fNum 15
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define textureNum 4
string textures[]={"wood","glass","glass","porcelain"};





#endif /* const_h */
