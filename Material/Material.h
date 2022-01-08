#include "include/shader.h"
#include "texture.h"
#include "Particle/Particle.h"
#include "state.h"
#include <SOIL/SOIL.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;


float rPointer[(rNum+1) * eNum * 4 * 3 * fNum];
float radius[rNum];


float normal(int j, string t)
{
    if (t == "CONSTANT")
        return 1.0f;
    else if (t == "QUADRATIC")
        return ((float)j / rNum) * ((float)j / rNum);
    else if (t == "SIN")
        return sin(Pi * j / rNum);
    else
        return 1.0f;
}

class Material
{
private:

    // utility function for loading a 2D texture from file
    // ---------------------------------------------------
    unsigned int materialVAO, materialVBO;
    unsigned int woodID,woodSurfaceID;
    unsigned int treeID,treeSurfaceID;
    unsigned int porcelainID,porcelainSurfaceID;
    unsigned int porcelain2ID,porcelain2SurfaceID;
    unsigned int marbleID,marbleSurfaceID;
    float offsetX;
    float length;
    float initR;
    string texture;
    int textureId=0;
    
    void renderPiece(int num){
        float y1, z1, y2, z2, y3, z3, y4, z4, tl,tr,tt,tb,leftR, rightR, normalX, normalY, normalZ,ifsurface;
        float ya, za, yb, zb, yc, zc, yd, zd;
        float pieceWidth = length / (2*rNum), offset;
        // if need the upper and lower bound.
        
//        if (num == 0)
//        {
//            rightR = radius[0];
//            leftR = (radius[0] + radius[1]) / 2;
//        }
//        else if (num == rNum - 1)
//        {
//            rightR = (radius[rNum - 2] + radius[rNum - 1]) / 2;
//            leftR = radius[rNum - 1];
//        }
//        else
//        {
//            rightR = (radius[num] + radius[num - 1]) / 2;
//            leftR = (radius[num] + radius[num + 1]) / 2;
//        }
        
        rightR = (radius[num] + radius[num - 1]) / 2;
        leftR = (radius[num] + radius[num + 1]) / 2;
        
        
        
        if(rightR==1.5f&&leftR==1.5f)
            ifsurface=1.5f;
        else
            ifsurface=0.0f;
        // rNum <- 0
        offset = (rNum - 1 - 2 * num) * pieceWidth;

        tl = 0.25+float(rNum-num)/rNum*0.75;
        tr = 0.25+float(rNum-num+1)/rNum*0.75;

        for (int i = 0; i < eNum; i++)
        {
            y1 = leftR * cos(2 * Pi / eNum * i);
            z1 = leftR * sin(2 * Pi / eNum * i);

            y2 = leftR * cos(2 * Pi / eNum * (i + 1));
            z2 = leftR * sin(2 * Pi / eNum * (i + 1));

            y3 = rightR * cos(2 * Pi / eNum * i);
            z3 = rightR * sin(2 * Pi / eNum * i);

            y4 = rightR * cos(2 * Pi / eNum * (i + 1));
            z4 = rightR * sin(2 * Pi / eNum * (i + 1));

            ya= leftR *0.9 * cos(2 * Pi / eNum * i);
            za= leftR *0.9 * sin(2 * Pi / eNum * i);
                        
            yb = leftR *0.9 * cos(2 * Pi / eNum * (i + 1));
            zb = leftR *0.9 * sin(2 * Pi / eNum * (i + 1));

            yc = rightR *0.9 * cos(2 * Pi / eNum * i);
            zc = rightR *0.9* sin(2 * Pi / eNum * i);

            yd = rightR *0.9* cos(2 * Pi / eNum * (i + 1));
            zd = rightR *0.9* sin(2 * Pi / eNum * (i + 1));

            
            
            
            tt = float(i)/eNum;
            tb = float(i+1)/eNum;

            normalX = ((y1 - y3) * (z2 - z1) + (y2 - y1) * (z3 - z1)) / (2 * pieceWidth);
            normalY = z2 - z1;
            normalZ = y1 - y2;
            
            
            
            // 1
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 0] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1] = y1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2] = z1;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7] = tl;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8] = tt;
            // 2
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 1] = y2;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 2] = z2;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 7] = tl;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 8] = tb;
            // 3
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 1] = y3;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 2] = z3;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 7] = tr;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 8] = tt;
            // 4
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 1] = y3;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 2] = z3;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 7] = tr;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 8] = tt;
            // 5
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 1] = y2;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 2] = z2;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 7] = tl;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 8] = tb;
            // 6
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 1] = y4;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 2] = z4;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 3] = normalX;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 4] = normalY;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 5] = normalZ;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 6] = ifsurface;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 7] = tr;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 8] = tb;
            
            
            
            
            if(IFSOLID){
                 // 7
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum] = offset - pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 1] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 2] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 3] = -1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 7] = 0.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 8] = 0.0;
                           // 8
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum] = offset - pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 1] = y1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 2] = z1;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 3] = -1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 7] = 1.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 8] = 1.0;
                           // 9
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum] = offset - pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 1] = y2;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 2] = z2;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 3] = -1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 7] = 1.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 8] = 1.0;
                           // 10
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum] = offset + pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 1] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 2] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 3] = 1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 7] = 0.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 8] = 0.0;
                           // 11
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum] = offset + pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 1] = y3;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 2] = z3;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 3] = 1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 7] = 1.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 8] = 1.0;
                           // 12
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum] = offset + pieceWidth;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 1] = y4;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 2] = z4;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 3] = 1;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 4] = 0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 5] = 0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 6] = 0.0;
               
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 7] = 1.0;
                           rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 8] = 1.0;
            }

            
            else{
            
            
            
            
            
            
            
            
            
         
            // render buttom
            
            if(num>rNum-10){
            // 7
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 1] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 2] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 3] = -1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 7] = 0.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 8] = 0.0;
            // 8
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 1] = y1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 2] = z1;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 3] = -1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 7] = 1.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 8] = 1.0;
            // 9
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum] = offset - pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 1] = y2;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 2] = z2;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 3] = -1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 7] = 1.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 8] = 1.0;
            // 10
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 1] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 2] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 3] = 1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 7] = 0.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 8] = 0.0;
            // 11
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 1] = y3;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 2] = z3;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 3] = 1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 7] = 1.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 8] = 1.0;
            // 12
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum] = offset + pieceWidth;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 1] = y4;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 2] = z4;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 3] = 1;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 4] = 0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 5] = 0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 6] = 0.0;

            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 7] = 1.0;
            rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 8] = 1.0;
            }
            else if(num>3 && num<50){
                // b
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 1] = yb;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 2] = zb;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 8] = tt;
                
                //2
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 1] = y2;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 2] = z2;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 8] = tb;
                
                
                //6
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 1] = y4;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 2] = z4;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 8] = tt;
                
                //6
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 1] = y4;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 2] = z4;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 8] = tt;
                
                
                //b
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 1] = yb;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 2] = zb;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 8] = tb;
                
                
                //d
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 1] = yd;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 2] = zd;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 8] = tb;
                
                
                
                
            }
            // render edge
            else {
                // a
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 1] = ya;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 2] = za;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 8] = tt;

                //b
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 1] = yb;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 2] = zb;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 8] = tb;

                //c
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 1] = yc;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 2] = zc;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 8] = tt;

                //c
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 1] = yc;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 2] = zc;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 8] = tt;

                // b
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum] = offset - pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 1] = yb;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 2] = zb;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 7] = tl;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 8] = tb;

                //d
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum] = offset + pieceWidth;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 1] = yd;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 2] = zd;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 3] = normalX;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 4] = normalY;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 5] = normalZ;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 6] = ifsurface;

                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 7] = tr;
                rPointer[num * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 8] = tb;



            }
            
            
            }
            
            
           

            
        }
    }

    void renderBase(){
        float y1, z1, y2, z2, tl,tr,tt,tb,leftR, rightR, normalX, normalY, normalZ,ifsurface=1.5f;
        float pieceWidth = 1.0f, offset;

        offset = -length/2-pieceWidth;

        tl = 0;
        tr = 0.25;

        for (int i = 0; i < eNum; i++)
        {
            y1 = initR * cos(2 * Pi / eNum * i);
            z1 = initR * sin(2 * Pi / eNum * i);

            y2 = initR * cos(2 * Pi / eNum * (i + 1));
            z2 = initR * sin(2 * Pi / eNum * (i + 1));
            
            

            tt = float(i)/eNum;
            tb = float(i+1)/eNum;

            normalX = 0;
            normalY = z2 - z1;
            normalZ = y1 - y2;
            
         
            //1
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 0] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1] = y1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2] = z1;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7] = tl;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8] = tt;
            
            //2
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 1] = y2;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 2] = z2;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 7] = tl;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 1 * fNum + 8] = tb;
            
            //3
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 1] = y1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 2] = z1;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 7] = tr;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 2 * fNum + 8] = tt;

            //4
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 1] = y1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 2] = z1;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 7] = tr;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 3 * fNum + 8] = tt;
            
            //5
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 1] = y2;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 2] = z2;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 7] = tl;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 4 * fNum + 8] = tb;
            
            // 6
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 1] = y2;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 2] = z2;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 3] = normalX;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 4] = normalY;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 5] = normalZ;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 6] = ifsurface;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 7] = tr;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 5 * fNum + 8] = tb;
            
            //7
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 1] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 2] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 3] = -1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 7] = 0.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 6 * fNum + 8] = 0.0;

            //8
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 1] = y1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 2] = z1;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 3] = -1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 7] = 1.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 7 * fNum + 8] = 1.0;

            // 9
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum] = offset - pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 1] = y2;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 2] = z2;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 3] = -1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 7] = 1.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 8 * fNum + 8] = 1.0;
            //10
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 1] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 2] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 3] = 1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 7] = 0.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 9 * fNum + 8] = 0.0;
            //11
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 1] = y1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 2] = z1;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 3] = 1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 7] = 1.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 10 * fNum + 8] = 1.0;
            //12
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum] = offset + pieceWidth;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 1] = y2;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 2] = z2;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 3] = 1;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 4] = 0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 5] = 0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 6] = 0.0;

            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 7] = 1.0;
            rPointer[rNum * eNum * 4 * 3 * fNum + i * 4 * 3 * fNum + 11 * fNum + 8] = 1.0;
        }
        
        
        
        
        
        
        
        
        
        
        
        
    }
    void renderInit()
    {
        for (int j = 0; j < rNum; j++)
        {
            radius[j] = initR * normal(j, "CONSTANT");
        }
        for (int j = 3; j < rNum-1; j++)
        {
            renderPiece(j);
        }
    }

public:
    Shader ironShader,woodShader,glassShader,porcelainShader,treeShader,porcelain2Shader,marbleShader;
    unsigned int woodNormalMap;
    unsigned int porcelainNormalMap;
    Material(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos,float offsetX,float initR,float length)
    :ironShader(Shader("Material/Iron.vs", "Material/Iron.fs")),
    woodShader(Shader("Material/Wood.vs","Material/Wood.fs")),
    glassShader(Shader("Material/glass.vs","Material/glass.fs")),
    porcelainShader(Shader("Material/porcelain.vs","Material/porcelain.fs")),
    treeShader(Shader("Material/Wood.vs","Material/Wood.fs")),
    porcelain2Shader(Shader("Material/porcelain.vs","Material/porcelain.fs")),
    marbleShader(Shader("Material/porcelain.vs","Material/porcelain.fs"))
    {
        this->offsetX=offsetX;
        this->initR=initR;
        this->length=length;
        this->texture="wood";

        this->initialize();

        glGenVertexArrays(1, &materialVAO);
        glGenBuffers(1, &materialVBO);
        
        // glGenTextures函数首先需要输入生成纹理的数量，然后把它们储存在第二个参数的woodId，就像其他对象一样，我们需要绑定它，让之后任何的纹理指令都可以配置当前绑定的纹理：
        glGenTextures(1, &this->woodID);
        glBindTexture(GL_TEXTURE_2D, this->woodID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        
//        string path="Material/Wood.jpg";
//        string path="Material/Marble021_1K_Color.jpg";
        string path="Material/clay/clayColor.png";
//        string path="Material/clay/p2.png";
//        string path="Material/porcelain/cloud1.jpg";
//        string path="Material/porcelain/tree1.jpg";
//        string path="Material/porcelain/tree2.jpg";
//        loadTextureSimple(path.data());
        loadTextureSimple(path.data());
        glGenTextures(1, &this->woodSurfaceID);
        glBindTexture(GL_TEXTURE_2D, this->woodSurfaceID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        woodNormalMap  = loadTexture("Material/clay/clayNormal.png");
        
        
     
        woodShader.use();
        woodShader.setInt("woodTexture",0);
        woodShader.setInt("surfaceTexture",1);
        woodShader.setInt("woodNormalMap",2);
        woodShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        woodShader.setVec3("lightPos", lightPos);
        woodShader.setVec3("viewPos", viewPos);

        woodShader.setVec3("wood.ambient", 0.30000, 0.30000, 0.30000);
        woodShader.setVec3("wood.diffuse", 0.35, 0.35, 0.35);
        woodShader.setVec3("wood.specular", 0.344597, 0.344597, 0.344597);
        woodShader.setFloat("wood.shininess",  5.800003);

        woodShader.setVec3("surface.ambient", 0.305882, 0.305882, 0.305882);
        woodShader.setVec3("surface.diffuse", 0.127451, 0.127451, 0.127451);
        woodShader.setVec3("surface.specular", 0.333333, 0.333333, 0.521569);
        woodShader.setFloat("surface.shininess",  5.846150);


        ironShader.use();
        ironShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ironShader.setVec3("lightPos", lightPos);
        ironShader.setVec3("viewPos", viewPos);

        ironShader.setVec3("steel.ambient", 0.250000, 0.250000, 0.250000);
        ironShader.setVec3("steel.diffuse", 0.65, 0.65, 0.65);
        ironShader.setVec3("steel.specular", 0.774597, 0.774597, 0.774597);
        ironShader.setFloat("steel.shininess",  76.800003);

        ironShader.setVec3("surface.ambient", 0.305882, 0.305882, 0.305882);
        ironShader.setVec3("surface.diffuse", 0.427451, 0.427451, 0.427451);
        ironShader.setVec3("surface.specular", 0.333333, 0.333333, 0.521569);
        ironShader.setFloat("surface.shininess",  9.846150);
        
        glassShader.use();
        glassShader.setInt("texture1", 0);
        
        
        glGenTextures(1, &this->porcelainID);
        glBindTexture(GL_TEXTURE_2D, this->porcelainID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        path="Material/porcelain/moutain.png";
//        path="Material/porcelain/p1.png";
//        path="Material/porcelain/tree1.png";
        loadTextureSimple(path.data());
        glGenTextures(1, &this->porcelainSurfaceID);
        glBindTexture(GL_TEXTURE_2D, this->porcelainSurfaceID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
    
        

        porcelainShader.use();
        porcelainShader.setInt("porcelainTexture",3);
        porcelainShader.setInt("porcelainSurfaceTexture",4);
        porcelainShader.setInt("porcelainNormalMap",5);
        
        porcelainShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        porcelainShader.setVec3("lightPos", lightPos);
        porcelainShader.setVec3("viewPos", viewPos);

        porcelainShader.setVec3("porcelain.ambient", 1.0000, 1.00000, 1.00000);
        porcelainShader.setVec3("porcelain.diffuse",0.5, 0.5, 0.5);
        porcelainShader.setVec3("porcelain.specular", 0.844597, 0.844597, 0.844597);
        porcelainShader.setFloat("porcelain.shininess",  60.846150);

        porcelainShader.setVec3("surface.ambient", 0.7000, 0.70000, 0.70000);
        porcelainShader.setVec3("surface.diffuse", 0.5, 0.5, 0.5);
        porcelainShader.setVec3("surface.specular", 0.844597, 0.844597, 0.844597);
        porcelainShader.setFloat("surface.shininess",  60.846150);

        
        
        
        // glGenTextures函数首先需要输入生成纹理的数量，然后把它们储存在第二个参数的woodId，就像其他对象一样，我们需要绑定它，让之后任何的纹理指令都可以配置当前绑定的纹理：
        glGenTextures(1, &this->treeID);
        glBindTexture(GL_TEXTURE_2D, this->treeID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        
//        string path="Material/Wood.jpg";
//        string path="Material/Marble021_1K_Color.jpg";
//        string path="Material/clay/p2.png";
//        string path="Material/porcelain/cloud1.jpg";
        path="Material/porcelain/tree1.jpg";
//        path="Material/marbleYellow.jpg";

       

//        string path="Material/porcelain/tree2.jpg";
//        loadTextureSimple(path.data());
        loadTextureSimple(path.data());
        glGenTextures(1, &this->treeSurfaceID);
        glBindTexture(GL_TEXTURE_2D, this->treeSurfaceID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        treeShader.use();
        treeShader.setInt("woodTexture",6);
        treeShader.setInt("surfaceTexture",7);
        treeShader.setInt("woodNormalMap",2);
        treeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        treeShader.setVec3("lightPos", lightPos);
        treeShader.setVec3("viewPos", viewPos);

        treeShader.setVec3("wood.ambient", 0.30000, 0.30000, 0.30000);
        treeShader.setVec3("wood.diffuse", 0.35, 0.35, 0.35);
        treeShader.setVec3("wood.specular", 0.344597, 0.344597, 0.344597);
        treeShader.setFloat("wood.shininess",  5.800003);

        treeShader.setVec3("surface.ambient", 0.305882, 0.305882, 0.305882);
        treeShader.setVec3("surface.diffuse", 0.127451, 0.127451, 0.127451);
        treeShader.setVec3("surface.specular", 0.333333, 0.333333, 0.521569);
        treeShader.setFloat("surface.shininess",  5.846150);
        
        
        
        
        
        
        glGenTextures(1, &this->porcelain2ID);
        glBindTexture(GL_TEXTURE_2D, this->porcelain2ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        path="Material/porcelain/moutain.png";
        path="Material/porcelain/p1.png";
//        path="Material/marbleYellow.jpg";
//        path="Material/porcelain/tree1.png";
        loadTextureSimple(path.data());
        glGenTextures(1, &this->porcelain2SurfaceID);
        glBindTexture(GL_TEXTURE_2D, this->porcelain2SurfaceID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        porcelain2Shader.use();
        porcelain2Shader.setInt("porcelainTexture",8);
        porcelain2Shader.setInt("porcelainSurfaceTexture",9);
        porcelain2Shader.setInt("porcelainNormalMap",10);
        
        porcelain2Shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        porcelain2Shader.setVec3("lightPos", lightPos);
        porcelain2Shader.setVec3("viewPos", viewPos);

        porcelain2Shader.setVec3("porcelain.ambient", 1.0000, 1.00000, 1.00000);
        porcelain2Shader.setVec3("porcelain.diffuse",0.5, 0.5, 0.5);
        porcelain2Shader.setVec3("porcelain.specular", 0.844597, 0.844597, 0.844597);
        porcelain2Shader.setFloat("porcelain.shininess",  60.846150);

        porcelain2Shader.setVec3("surface.ambient", 0.7000, 0.70000, 0.70000);
        porcelain2Shader.setVec3("surface.diffuse", 0.5, 0.5, 0.5);
        porcelain2Shader.setVec3("surface.specular", 0.844597, 0.844597, 0.844597);
        porcelain2Shader.setFloat("surface.shininess",  60.846150);
        
        
        
        
        
        glGenTextures(1, &this->marbleID);
        glBindTexture(GL_TEXTURE_2D, this->marbleID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        path="Material/marbleYellow.jpg";
        loadTextureSimple(path.data());
        glGenTextures(1, &this->marbleSurfaceID);
        glBindTexture(GL_TEXTURE_2D, this->marbleSurfaceID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        

        marbleShader.use();
        marbleShader.setInt("porcelainTexture",11);
        marbleShader.setInt("porcelainSurfaceTexture",12);
        marbleShader.setInt("porcelainNormalMap",13);
        
        marbleShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        marbleShader.setVec3("lightPos", lightPos);
        marbleShader.setVec3("viewPos", viewPos);

        marbleShader.setVec3("porcelain.ambient", 1.0000, 1.00000, 1.00000);
        marbleShader.setVec3("porcelain.diffuse",0.5, 0.5, 0.5);
        marbleShader.setVec3("porcelain.specular", 0.844597, 0.844597, 0.844597);
        marbleShader.setFloat("porcelain.shininess",  60.846150);

        marbleShader.setVec3("surface.ambient", 0.7000, 0.70000, 0.70000);
        marbleShader.setVec3("surface.diffuse", 0.5, 0.5, 0.5);
        marbleShader.setVec3("surface.specular", 0.844597, 0.844597, 0.844597);
        marbleShader.setFloat("surface.shininess",  60.846150);
        
        
        
        
        
    }
    

    void initialize(){
        this->renderInit();
//        this->renderBase();

        glBindVertexArray(materialVAO);
        glBindBuffer(GL_ARRAY_BUFFER, materialVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rPointer), &rPointer, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(7 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void drawMaterial(glm::mat4 view, glm::mat4 projection, glm::mat4 model,glm::mat4 rotate,bool ifdisplay)
    {
        model=glm::translate(model,glm::vec3(offsetX,0.0f,0.0f));
        if(texture=="wood"){
            // 2 texture unit combined
            glActiveTexture(GL_TEXTURE0);//在绑定纹理之前先激活纹理单元
            glBindTexture(GL_TEXTURE_2D, this->woodID);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->woodSurfaceID);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, woodNormalMap);
            
            woodShader.use();
            woodShader.setVec3("lightColor",lightColors[lightId]);
            woodShader.setMat4("view", view);
            woodShader.setMat4("projection", projection);
            woodShader.setMat4("model", model);
            woodShader.setMat4("rotate",rotate);
        } else if(texture=="iron"){
            ironShader.use();
            ironShader.setVec3("lightColor",lightColors[lightId]);
            ironShader.setMat4("view", view);
            ironShader.setMat4("projection", projection);
            ironShader.setMat4("model", model);
            ironShader.setMat4("rotate",rotate);
        } else if(texture == "glass"){
            glassShader.use();
            
            glassShader.setVec3("lightColor",lightColors[lightId]);
            glassShader.setMat4("view", view);
            glassShader.setMat4("projection", projection);
            glassShader.setMat4("model", model);
            glassShader.setMat4("rotate",rotate);
            glassShader.setVec3("cameraPos", camera.Position);
        } else if(texture=="porcelain"){
            glActiveTexture(GL_TEXTURE3);//在绑定纹理之前先激活纹理单元
            glBindTexture(GL_TEXTURE_2D, this->porcelainID);
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, this->porcelainSurfaceID);
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, porcelainNormalMap);
            porcelainShader.use();
            porcelainShader.setVec3("lightColor",lightColors[lightId]);
            porcelainShader.setMat4("view", view);
            porcelainShader.setMat4("projection", projection);
            porcelainShader.setMat4("model", model);
            porcelainShader.setMat4("rotate",rotate);
        }else if(texture =="tree"){
            glActiveTexture(GL_TEXTURE6);//在绑定纹理之前先激活纹理单元
            glBindTexture(GL_TEXTURE_2D, this->treeID);
            glActiveTexture(GL_TEXTURE7);
            glBindTexture(GL_TEXTURE_2D, this->treeSurfaceID);
         
            
            treeShader.use();
            treeShader.setVec3("lightColor",lightColors[lightId]);
            treeShader.setMat4("view", view);
            treeShader.setMat4("projection", projection);
            treeShader.setMat4("model", model);
            treeShader.setMat4("rotate",rotate);
            
        }else if(texture == "porcelain2"){
            glActiveTexture(GL_TEXTURE8);//在绑定纹理之前先激活纹理单元
            glBindTexture(GL_TEXTURE_2D, this->porcelain2ID);
            glActiveTexture(GL_TEXTURE9);
            glBindTexture(GL_TEXTURE_2D, this->porcelain2SurfaceID);
            glActiveTexture(GL_TEXTURE10);
            glBindTexture(GL_TEXTURE_2D, porcelainNormalMap);
            porcelain2Shader.use();
            porcelain2Shader.setVec3("lightColor",lightColors[lightId]);
            porcelain2Shader.setMat4("view", view);
            porcelain2Shader.setMat4("projection", projection);
            porcelain2Shader.setMat4("model", model);
            porcelain2Shader.setMat4("rotate",rotate);
        }
        else if(texture == "marble"){
            glActiveTexture(GL_TEXTURE11);//在绑定纹理之前先激活纹理单元
            glBindTexture(GL_TEXTURE_2D, this->marbleID);
            glActiveTexture(GL_TEXTURE12);
            glBindTexture(GL_TEXTURE_2D, this->marbleSurfaceID);
            glActiveTexture(GL_TEXTURE13);
            glBindTexture(GL_TEXTURE_2D, porcelainNormalMap);
            porcelain2Shader.use();
            porcelain2Shader.setVec3("lightColor",lightColors[lightId]);
            porcelain2Shader.setMat4("view", view);
            porcelain2Shader.setMat4("projection", projection);
            porcelain2Shader.setMat4("model", model);
            porcelain2Shader.setMat4("rotate",rotate);
        }

        glBindVertexArray(materialVAO);
        if(ifdisplay)
            glDrawArrays(GL_TRIANGLES, 0, rNum * eNum * 4 * 3);
        else
            glDrawArrays(GL_TRIANGLES, 0, (rNum+1) * eNum * 4 * 3);
        glBindVertexArray(0);
    }

    void changeTexure(ParticleSystem *ps,string texture1=""){
    //        texture=(texture=="wood")?"iron":"wood";
        if(texture1=="")texture=textures[(++textureId) % textureNum];
        else texture = texture1;
            cout<<"texture:"<<texture<<endl;
            ps->changeColor(texture);
        }
    
    
    
    

    void updateRadius(glm::vec3 knifePos,glm::vec3 lastPos,ParticleSystem *ps,float dt){
        float pieceWidth = length / (2*rNum),leftLimit=offsetX-length/2,rightLimit=offsetX+length/2;
        glm::vec3 leftPos,rightPos;
        bool toLeft;

        if(knifePos.x < lastPos.x){
            leftPos=knifePos;
            rightPos=lastPos;
            toLeft = true;
        }
        else {
            leftPos=lastPos;
            rightPos=knifePos;
            toLeft = false;
        }

        if(leftPos.x > rightLimit || rightPos.x < leftLimit){
            return;
        }

        if(leftPos.x==rightPos.x){
            return;
        }
        else {
            float k=(rightPos.y-leftPos.y)/(rightPos.x-leftPos.x),
                b=(rightPos.x*leftPos.y-leftPos.x*rightPos.y)/(rightPos.x-leftPos.x);
            
            if(leftPos.x < leftLimit) leftPos=glm::vec3(leftLimit,k*leftLimit+b,0);
            if(rightPos.x > rightLimit) rightPos=glm::vec3(rightLimit,k*rightLimit+b,0);

            int leftNum=((offsetX-leftPos.x)/length+0.5)*rNum,rightNum=((offsetX-rightPos.x)/length+0.5)*rNum;
            float knifeX,knifeY;
            for(int i=rightNum;i<=leftNum;i++){
                knifeX=(rNum -1-2*i)*pieceWidth+offsetX;
                knifeY=k*knifeX+b;
                if(knifeY<=0&&(-knifeY)<radius[i]){
                    int pNum=MAX((-knifeY-radius[i]) * 8 /1.5f,1);
                    for(int j=0;j<pNum;j++){
                        //!delete particle
                        ps->insertParticle(Particle(glm::vec3(knifeX,knifeY,0),glm::vec3((toLeft?1:-1)*rand()%10,-rand()%10,-5+rand()%10)));
                    }

                    radius[i]=-knifeY;
                }
                    
            }
            for(int i=MAX(0,rightNum-1);i<=MIN(rNum-1,leftNum+1);i++){
                renderPiece(i);
                
                
                
                
                
                
            }
        }

        glBindVertexArray(materialVAO);
        glBindBuffer(GL_ARRAY_BUFFER, materialVBO);
        // position changes so maybe use dynamic
//        glBufferData(GL_ARRAY_BUFFER, sizeof(rPointer), &rPointer, GL_STATIC_DRAW);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(rPointer), &rPointer, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(7 * sizeof(float)));
        glEnableVertexAttribArray(3);
        
        return;
    }
    
    void updateRadiusAll(float newRadius[] ){
        for(int i=0;i<rNum;i++){
            radius[i]=newRadius[i];
        }
        for (int j = 3; j < rNum; j++)
        {
            renderPiece(j);
        }
        glBindVertexArray(materialVAO);
        glBindBuffer(GL_ARRAY_BUFFER, materialVBO);
        // position changes so maybe use dynamic
//        glBufferData(GL_ARRAY_BUFFER, sizeof(rPointer), &rPointer, GL_STATIC_DRAW);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(rPointer), &rPointer, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, fNum * sizeof(float), (void *)(7 * sizeof(float)));
        glEnableVertexAttribArray(3);
        
    }
    void loadTextureSimple(const char*path){
        int texwidth,texheight,nrComponents=0;//nrChannels表示通道数，R/G/B/A，一共4个通道，有些图片只有3个，A即为alpha
        unsigned char *data = SOIL_load_image(path, &texwidth, &texheight, &nrComponents, SOIL_LOAD_RGB);
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            if(data){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwidth, texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
                std::cout<<SOIL_last_result()<<std::endl;
            SOIL_free_image_data(data);
        return ;
    }
    
    
    void saveModel(){
        outfile << textureId << endl;
        outfile << IFSOLID << endl;
        cout<<"material save model:"<< textureId << IFSOLID<<endl;
    }
    void loadModel(){
        
        infile >> textureId >> IFSOLID;
        cout<<"material load model:"<< textureId<<IFSOLID<<endl;
        texture = textures[textureId];
    }
};



