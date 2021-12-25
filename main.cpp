#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdlib>
#include "time.h"

#include "include/shader.h"
#include "include/camera.h"
#include "include/model.h"
#include "const.h"
#include "Material/Material.h"
#include "Knife/Knife.h"
#include "Base/Base.h"
#include "Particle/Particle.h"
#include "Button/Button.h"
#include "CurveArea/CurveArea.h"
#include "SkyBox/SkyBox.h"


//控制是否显示命令台
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define TIMESTEP 4

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
glm::vec3 Screen2World(float x,float y, glm::mat4 projection, glm::mat4 view);
glm::vec3 BezierCurve(glm::vec3 p0,glm::vec3 p1,glm::vec3 p2,glm::vec3 p3,glm::vec3 p4,glm::vec3 p5,float t);




//time
float deltaTime = 0.0f;
float lastTime = 0.0f;
float totalTime = 0.0f;
float rotate_radius = 0.0f;

bool ifreset=true,ifdisplay=false;

glm::mat4 cupRotate=glm::mat4(1.0f);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::vec3 lightPos(-5.0f,0.0f,6.0f);
    glm::vec3 p0(-2.0f,-1.5f,0),p1(-4.0f,-0.0f,0),p2(-6.0f,-0.0f,0),p3(-8.0f,-1.5f,0);

    Material material(lightPos,camera.Position,-5.0f,3.0f,6.0f);
    ParticleSystem ps(lightPos);
    Knife knife(lightPos,camera.Position);
    Base base(lightPos,camera.Position);

    SkyBox skybox;

    CurveArea curveArea(SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY,-5.0f,3.0f,6.0f);
    Button bezierButton("Button/bezier.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-buttonDist);
    Button cursorButton("Button/cursor.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-buttonDist);
    Button startButton("Button/start.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-2*buttonDist);
    Button resetButton("Button/reset.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-3*buttonDist);
    Button textureButton("Button/texture.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-4*buttonDist);
    Button displayButton("Button/display.jpg",SCR_WIDTH,SCR_HEIGHT,
    buttonWidth,buttonHeight, buttonOffsetX,buttonOffsetY-5*buttonDist);

    glm::vec3 knifePos=p0,lastKnifePos;

    // calculate time
    float lastTime = glfwGetTime(),currentTime,bezierTime = 0,rate=0;
    srand(time(0));
    cupRotate =glm::rotate(cupRotate,-80.1f,glm::vec3(0.0,0.0,1.0f));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        totalTime += deltaTime;

        if(ifstart)
            bezierTime += deltaTime;
        lastTime = currentTime;

        rate = MIN(bezierTime/10.0f,1.0f);

        if(rate==1.0f)
            ifstart=false;

        if(ifreset){
            material.initialize();
            ifreset=false;

            bezierTime = 0;
            rate = 0;
            ifstart = false;
            
            knifePos = glm::vec3(-1.9f,-1.5f,0.0f);
        }

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        
//        cupRotate =glm::rotate(cupRotate,-80.1f,glm::vec3(0.0,0.0,1.0f));
        

        ps.updateParticle(deltaTime);

        lastKnifePos = knifePos;

        if(Mode==BEZIER){
                knifePos = curveArea.gerRealCurve(rate);
        } else
        {
            knifePos = Screen2World(lastX, lastY, projection, view);
            knifePos = glm::vec3(MAX(-8.0f,knifePos.x), MIN(0, knifePos.y), 0);
        }

        if(Select==TEXTURE){
            material.changeTexure(&ps);
            skybox.changeTexture();
            Select=CHANGED;
        }

        if(Select==AREA)
            curveArea.updateCurveArea(mouseX,mouseY);
        else
            curveArea.releaseSelect();
        
        skybox.drawSkybox(view,projection);

        // the knife shouldn't move
         if(Select==AREA)
             knifePos=lastKnifePos;
        
        if(!ifdisplay){
            model = glm::translate(glm::mat4(1.0f), knifePos);
            // !! no draw knife
            if(origin)knife.drawKnife(view,projection,model,cupRotate);

//            cupRotate=glm::rotate(cupRotate,1071*totalTime,glm::vec3(1.0,0.0,0.0f));
            //! no base
            
            base.drawBase(view,projection,glm::mat4(1.0f),cupRotate);
        }
        else {
            knifePos=glm::vec3(0.0f,-2.0f,0.0f);
            lastKnifePos=glm::vec3(0.0f,-2.0f,0.0f);

//            cupRotate=glm::rotate(cupRotate,totalTime/100,glm::vec3(1.0,0.0,0.0f));
            cupRotate=glm::rotate(cupRotate,0.01f,glm::vec3(1.0,0.0,0.0f));
        }
        if(Select!=AREA)
            material.updateRadius(knifePos,lastKnifePos,&ps,deltaTime);
//        cupRotate =glm::rotate(cupRotate,-80.1f,glm::vec3(0.0,0.0,1.0f));
        material.drawMaterial(view,projection,glm::mat4(1.0f),cupRotate,ifdisplay);


//        cupRotate=glm::mat4(1.0f);
        ps.simulate(deltaTime);
        ps.render(view, projection, glm::mat4(1.0f), cupRotate);


        
        if(Mode==CURSOR)
            cursorButton.drawButton();
        else
            bezierButton.drawButton();
        startButton.drawButton();
        resetButton.drawButton();
        textureButton.drawButton();
        displayButton.drawButton();

        curveArea.drawCurveArea();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        ifreset=true;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        mouseControlCamera=!mouseControlCamera;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        cupRotate=glm::rotate(cupRotate,0.1f,glm::vec3(0.0,1.0,0.0f));
    }
        
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cupRotate=glm::rotate(cupRotate,-0.1f,glm::vec3(0.0,1.0,0.0f));
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
//        cupRotate=glm::rotate(cupRotate,0.1f,glm::vec3(1.0,0.0,0.0f));
//    }
//        
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//        cupRotate=glm::rotate(cupRotate,-0.1f,glm::vec3(1.0,0.0,0.0f));
    
    
    //if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    //    rotate_radius -= (deltaTime/TIMESTEP)* 360.0f;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    //    rotate_radius += (deltaTime/TIMESTEP)* 360.0f;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        cout<<"Select:"<<Select<<endl;
        if(Select==NONE){
            cout<<"Select:"<<Select<<endl;
            if(SCR_WIDTH/2.0+buttonOffsetX-buttonWidth/2.0<=lastX&&lastX<=SCR_WIDTH/2.0+buttonOffsetX+buttonWidth/2.0){
                if(!ifstart&&
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2<=lastY&&lastY<= SCR_HEIGHT /2-buttonOffsetY+buttonHeight/2){
                    mouseX=MAX(MIN(lastX-SCR_WIDTH/2-buttonOffsetX,buttonWidth/2),-buttonWidth/2);
                    mouseY=MAX(MIN(SCR_HEIGHT/2-lastY-buttonOffsetY,buttonHeight/2),-buttonHeight/2);
                    Select=AREA;
                    cout<<mouseX<<" "<<mouseY<<endl;
                } else
                if(!ifdisplay&&
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2+buttonDist<=lastY&&lastY<= SCR_HEIGHT /2-buttonOffsetY+buttonHeight/2+buttonDist){
                    Select=MODE;
                    ifreset=true;
                    Mode=(Mode==BEZIER)?CURSOR:BEZIER;
                } else
                if(!ifdisplay&&Mode==BEZIER&&
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2+2*buttonDist<=lastY&&lastY<=SCR_HEIGHT/2-buttonOffsetY+buttonHeight/2+2*buttonDist){
                    Select=START;
                    ifstart=true;
                } else
                if(!ifdisplay&&
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2+3*buttonDist<=lastY&&lastY<= SCR_HEIGHT/2-buttonOffsetY+buttonHeight/2+3*buttonDist){
                    Select=RESET;
                    ifreset = true;
                } else
                if(
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2+4*buttonDist<=lastY&&lastY<= SCR_HEIGHT/2-buttonOffsetY+buttonHeight/2+4*buttonDist){
                    Select=TEXTURE;
                }
                if(!ifstart&&
                SCR_HEIGHT/2-buttonOffsetY-buttonHeight/2+5*buttonDist<=lastY&&lastY<= SCR_HEIGHT/2-buttonOffsetY+buttonHeight/2+5*buttonDist){
                    Select=DISPLAY;
                    ifdisplay=!ifdisplay;
                    totalTime=0;
                }
            }
        } else if(Select==AREA)
        {
            mouseX=MAX(MIN(lastX-SCR_WIDTH/2-buttonOffsetX,buttonWidth/2),-buttonWidth/2);
            mouseY=MAX(MIN(SCR_HEIGHT/2-lastY-buttonOffsetY,buttonHeight/2),-buttonHeight/2);
        }
    }
    else {
        Select=NONE;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    if (firstMouse) {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    lastX = xpos;
//    lastY = ypos;
//    //printf("%d %d\n",xpos,ypos);
//    // camera.ProcessMouseMovement(xoffset, yoffset);
//}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if(mouseControlCamera)camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

glm::vec3 Screen2World(float x,float y,glm::mat4 projection,glm::mat4 view ){
    float clipX=x/SCR_WIDTH*2-1,clipY=1-y/SCR_HEIGHT*2;
    glm::vec4 pos=glm::vec4(clipX,clipY,1,1);
    glm::mat4 invProj=glm::inverse(projection);
    glm::mat4 invView=glm::inverse(view);
    pos = invView * invProj * pos;
    pos /= pos.w;
    return glm::vec3(
        pos.x * camera.Position.z / (100.0 - 0.1) + camera.Position.x*(100.0-0.1-camera.Position.z)/(100-0.1),
        pos.y * camera.Position.z / (100.0 - 0.1) + camera.Position.y*(100.0-0.1-camera.Position.z)/(100-0.1),
        0);
}

glm::vec3 BezierCurve(glm::vec3 p0,glm::vec3 p1,glm::vec3 p2,glm::vec3 p3,glm::vec3 p4,glm::vec3 p5,float t){
//    glm::vec3 v=p0*((float)pow(1-t,3))+p1*((float)(3*t*pow(1-t,2)))+p2*((float)(3*pow(t,2)*(1-t)))+p3*((float)pow(t,3));
//
//
//    return v;
    
    glm::vec3 v=p0*((float)pow(1-t,5))+p1*((float)(5*t*pow(1-t,4)))+p2*((float)(10*pow(t,2)*pow(1-t,3)))+p3*((float)(10*pow(t,3)*pow(1-t,2)))+p4*((float)(5*pow(t,4)*(1-t)))+p5*((float)pow(t,5));
    return v;
    
}
