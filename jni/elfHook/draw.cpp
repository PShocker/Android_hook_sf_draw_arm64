#include "draw.h"


#define LOG_TAG "INJECT"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)

extern EGLint w, h;

// const GLfloat gTriangleVertices[] = {0.0f, 0.5f, -0.5f, -0.5f,
//                                      0.5f, -0.5f};

// static const GLfloat vVertices[] = { 
//             -0.5f,-0.5f,0.0f,
//             0.5f,-0.5f,0.0f,
//             0.5f,0.5f,0.0f,
//             -0.5f,0.5f,0.0f,
//            };

void drawRect(int x,int y,int width,int height){    
    EGLint init_x=w/2;
    EGLint init_y=h/2;

    float draw_x=((float)x-(float)init_x)/(float)init_x;
    float draw_y=((float)init_y-(float)y)/(float)init_y;

    float draw_width=(float)width/(float)w;
    float draw_height=(float)height/(float)h;
    LOGD("w:%d\n",w);
    LOGD("h:%d\n",h);

    const GLfloat Vertices[] = { 
            draw_x,draw_y,0.0f,
            draw_x+draw_width,draw_y,0.0f,
            draw_x+draw_width,draw_y-draw_height,0.0f,
            draw_x,draw_y-draw_height,0.0f,
           };
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, Vertices);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}