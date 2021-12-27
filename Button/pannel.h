//
//  pannel.h
//  Lathe-Simulation2
//
//  Created by 康艺潇 on 2021/12/27.
//

#ifndef pannel_h
#define pannel_h


#include "shader.h"
#include "Button/Button.h"


class pannel(){
private:
    Button button;
    Shader pointShader;
public:
    
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

}


#endif /* pannel_h */
