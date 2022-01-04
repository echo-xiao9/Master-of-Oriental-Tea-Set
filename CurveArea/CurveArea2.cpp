////
////  CurveArea2.cpp
////  Lathe-Simulation2
////
////  Created by 康艺潇 on 2021/12/30.
////
//
//#include "CurveArea2.hpp"
//
//
//CurveArea2::CurveArea2():
//    pointShader(Shader("CurveArea/Point.vs","CurveArea/Point.fs")),
//    curveShader(Shader("CurveArea/Point.vs","CurveArea/Point.fs")){
//    glGenVertexArrays(1, &pointVAO);
//    glGenBuffers(1, &pointVBO);
//    glGenVertexArrays(1, &curveVAO);
//    glGenBuffers(1, &curveVBO);
//    glGenVertexArrays(1, &lineVAO);
//    glGenBuffers(1, &lineVBO);
//
//
//
//
//
//
//}
//
//void CurveArea2::updateBuffer(){
//    glBindVertexArray(pointVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//    controlPointsData=new float[controlPoints.size()*3];
//    curvePointsData = new float[curvePoints.size()*3];
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(controlPointsData), &controlPointsData, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//
//
//    glBindVertexArray(curveVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(curvePointsData), &curvePointsData, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//    delete [] controlPointsData;
//    delete [] curvePointsData;
//
//}
//
//
//
//void CurveArea2::addControlPoint(float mouseX, float mouseY){
//    vec3 v(mouseX, mouseY,0);
//    controlPoints.push_back(v);
//    controlNum++;
//    if(controlNum/4==0)bezierNum++;
//    updateBuffer();
//    drawPoint();
//    drawControlLines();
//    drawCurve();
//}
//
//void CurveArea2::genCurve(){
//    if(controlNum != 4*bezierNum){
//        cout<<"controlNum != 4*bezierNum"<<endl;
//        return;
//    }
//    for(int i=0;i<controlNum;i+=4){
//        // generate points for every bezier curve.
//
//        for(float j=0;j<LINE_NUM;j++){
//            vec3 tmp;
//            genCurvePoint(j/LINE_NUM, tmp, controlPoints[i],controlPoints[i+1],controlPoints[i+2],controlPoints[i+3]);
//            curvePoints.push_back(tmp);
//        }
//    }
//}
//
//void CurveArea2::genCurvePoint(float t, vec3 p, vec3 p0, vec3 p1, vec3 p2, vec3 p3){
//    p=p0*((float)pow(1-t,3))+p1*((float)(3*t*pow(1-t,2)))+p2*((float)(3*pow(t,2)*(1-t)))+p3*((float)pow(t,3));
//}
//
//void CurveArea2::drawPoint(){
//
//    pointShader.use();
//    glBindVertexArray(pointVAO);
//    glPointSize(CRTL_POINT_SIZE);
//    glDrawArrays(GL_POINTS, 0, controlNum);
//    glBindVertexArray(0);
//
//    glBindVertexArray(curveVAO);
//    glLineWidth(BEZIER_WIDTH);
//    glDrawArrays(GL_LINE_STRIP, 0, bezierNum*LINE_NUM);
//    glBindVertexArray(0);
//
//
//}
//void CurveArea2::drawCurve(){
//
//}
//
//void CurveArea2::drawControlLines(){
//}
