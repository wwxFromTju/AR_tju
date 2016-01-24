
#include "renderer.hpp"
#if defined __APPLE__
#include <OpenGLES/ES2/gl.h>
#else
#include <GLES2/gl2.h>
#endif
#include "banana.h"
#import "chr_fox.h"
#import "monu9.h"
#import "tju.h"

const char* box_vert=
        "uniform mat4 trans;\n"
        "uniform mat4 proj;\n"
        "attribute vec4 coord;\n"
        "attribute vec4 color;\n"
        "attribute vec4 color2;\n"
        "varying vec4 vcolor;\n"
        "attribute vec2 a_texCoord;\n"
        "//attribute vec3 a_normal;\n"
        "varying vec2 v_texcoord;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    vcolor = color;\n"
        "    gl_Position = proj*trans*coord;\n"
        //  "    gl_texCooord = a_texCoord;\n"
        "     v_texcoord = a_texCoord;\n"
        "}\n"
        "\n"
;

const char* box_frag=
        "#ifdef GL_ES\n"
        "precision highp float;\n"
        "#endif\n"
        "varying vec4 vcolor;\n"
        "varying vec2 v_texcoord;\n"
        "\n"
        "uniform sampler2D s_texture;                        \n"
        "void main(void)\n"
        "{\n"
//        "  s_texture = vec4(0,0,0,1);\n"
//       "  gl_FragColor = vec4(vec3(v_texcoord.s), 1.0);     \n"
//        "    gl_FragColor = vcolor;\n"
        "    gl_FragColor =   vec4(0.6,0.5,0.8,1) + vec4(0.1,0.1,0.1,1) * vcolor;\n"
        "}\n"
        "\n"
;


typedef struct
{
    // Handle to a program object
    GLuint programObject;
    
    // VertexBufferObject Ids
    GLuint vboIds[2];
    
    // VertexArrayObject Id
    GLuint vaoId;
    
} UserData;

    GLuint vboIds[3];
    GLuint vaoId;
    unsigned int vbo_color_box2;
    GLuint scaleM;
    unsigned int   texcoord;
    GLuint textureId;
    unsigned int samplerLoc;
#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

#define VERTEX_STRIDE         ( sizeof(GLfloat) *     \
( VERTEX_POS_SIZE +    \
VERTEX_COLOR_SIZE ) )



namespace EasyAR{
namespace samples{

void Renderer::init()
{
    program_box = glCreateProgram();
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &box_vert, 0);
    glCompileShader(vertShader);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &box_frag, 0);
    glCompileShader(fragShader);
    glAttachShader(program_box, vertShader);
    glAttachShader(program_box, fragShader);
    glLinkProgram(program_box);
    glUseProgram(program_box);
    pos_coord_box = glGetAttribLocation(program_box, "coord");
    pos_color_box = glGetAttribLocation(program_box, "color");
    vbo_color_box2 = glGetAttribLocation(program_box, "color2");
    pos_trans_box = glGetUniformLocation(program_box, "trans");
    pos_proj_box = glGetUniformLocation(program_box, "proj");
    texcoord = glGetAttribLocation(program_box, "a_texCoord");
    samplerLoc = glGetUniformLocation ( program_box, "s_texture" );

//    glGenBuffers(1, &vbo_coord_box);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord_box);
//    const GLfloat cube_vertices[8][3] = {
//        /* +z */{1.0f / 2, 1.0f / 2, 0.01f / 2}, {1.0f / 2, -1.0f / 2, 0.01f / 2}, {-1.0f / 2, -1.0f / 2, 0.01f / 2}, {-1.0f / 2, 1.0f / 2, 0.01f / 2},
//        /* -z */{1.0f / 2, 1.0f / 2, -0.01f / 2}, {1.0f / 2, -1.0f / 2, -0.01f / 2}, {-1.0f / 2, -1.0f / 2, -0.01f / 2}, {-1.0f / 2, 1.0f / 2, -0.01f / 2}};
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);
//
    glGenBuffers(1, &vbo_color_box);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color_box);
    const GLubyte cube_vertex_colors[8][4] = {
        {255, 0, 0, 128}, {0, 255, 0, 128}, {0, 0, 255, 128}, {0, 0, 0, 128},
        {0, 255, 255, 128}, {255, 0, 255, 128}, {255, 255, 0, 128}, {255, 255, 255, 128}};
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_colors), cube_vertex_colors, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &vbo_color_box_2);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_color_box_2);
//    const GLubyte cube_vertex_colors_2[8][4] = {
//        {255, 0, 0, 255}, {255, 255, 0, 255}, {0, 255, 0, 255}, {255, 0, 255, 255},
//        {255, 0, 255, 255}, {255, 255, 255, 255}, {0, 255, 255, 255}, {255, 0, 255, 255}};
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_colors_2), cube_vertex_colors_2, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &vbo_faces_box);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_faces_box);
//    const GLushort cube_faces[6][4] = {
//        /* +z */{3, 2, 1, 0}, /* -y */{2, 3, 7, 6}, /* +y */{0, 1, 5, 4},
//        /* -x */{3, 0, 4, 7}, /* +x */{1, 2, 6, 5}, /* -z */{4, 5, 6, 7}};
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_faces), cube_faces, GL_STATIC_DRAW);
//    
//    
//    
    glGenTextures ( 1, &textureId );
    
    glGenBuffers ( 3,vboIds );
    
    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[0] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( tjuVerts ),
                 tjuVerts, GL_STATIC_DRAW );
    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[1] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( tjuNormals ),
                  tjuNormals, GL_STATIC_DRAW );
    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[2] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( tjuTexCoords ),
                  tjuTexCoords, GL_STATIC_DRAW );
    
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // Set the sampler texture unit to 0
    glUniform1i(samplerLoc, 0);
//    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
//    
//    // Generate a texture object
//    glGenTextures ( 1, &textureId );
//    
//    // Bind the texture object
//    glBindTexture ( GL_TEXTURE_2D, textureId );
//    
//    
//    // Load the texture
//    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, chr_foxTexCoords );
//    
//    // Set the filtering mode
//    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
//    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
//    
    
    
    
//    glGenBuffers ( 3,vboIds );
//    
//    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[0] );
//    glBufferData ( GL_ARRAY_BUFFER, sizeof ( chr_foxVerts ),
//                  chr_foxVerts, GL_STATIC_DRAW );
//    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[1] );
//    glBufferData ( GL_ARRAY_BUFFER, sizeof ( chr_foxNormals ),
//                  chr_foxNormals, GL_STATIC_DRAW );
//    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[2] );
//    glBufferData ( GL_ARRAY_BUFFER, sizeof ( chr_foxTexCoords ),
//                  chr_foxTexCoords, GL_STATIC_DRAW );
}

void Renderer::render(const Matrix44F& projectionMatrix, const Matrix44F& cameraview, Vec2F size)
{
    
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord_box);
//    float height = size[0] / 1000;
//    const GLfloat cube_vertices[8][3] = {
//        /* +z */{size[0] / 2, size[1] / 2, height / 2}, {size[0] / 2, -size[1] / 2, height / 2}, {-size[0] / 2, -size[1] / 2, height / 2}, {-size[0] / 2, size[1] / 2, height / 2},
//        /* -z */{size[0] / 2, size[1] / 2, 0}, {size[0] / 2, -size[1] / 2, 0}, {-size[0] / 2, -size[1] / 2, 0}, {-size[0] / 2, size[1] / 2, 0}};
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(program_box);
    
    //这部分是必须的,设置对应的投影和变换的矩阵
    float temp[16];
    for(int i = 0; i < 16; ++i)
        temp[i] =cameraview.data[i];
    for(int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j) {
            temp[i*4+j] *= 5;
        }
    
    
    glUniformMatrix4fv(pos_trans_box, 1, 0, temp);
    glUniformMatrix4fv(pos_proj_box, 1, 0, projectionMatrix.data);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_faces_box);
    
    
//   //下面的垫纸1
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord_box);
//    glEnableVertexAttribArray(pos_coord_box);
//    glVertexAttribPointer(pos_coord_box, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_color_box);
//    glEnableVertexAttribArray(pos_color_box);
//    glVertexAttribPointer(pos_color_box, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
//    
//    //这部分是必须的，这个是原来的顺序
//    glUniformMatrix4fv(pos_trans_box, 1, 0, cameraview.data);
//    glUniformMatrix4fv(pos_proj_box, 1, 0, projectionMatrix.data);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_faces_box);
    
    //下面的垫纸2
//    for(int i = 0; i < 6; i++) {
//        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, (void*)(i * 4 * sizeof(GLushort)));
//    }

    //每一个渲染的部分
    //这里是上面的彩色的矩形
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_coord_box);
//    const GLfloat cube_vertices_2[8][3] = {
//        /* +z */{size[0] / 4, size[1] / 4, size[0] / 4},{size[0] / 4, -size[1] / 4, size[0] / 4},{-size[0] / 4, -size[1] / 4, size[0] / 4},{-size[0] / 4, size[1] / 4, size[0] / 4},
//        /* -z */{size[0] / 4, size[1] / 4, 0},{size[0] / 4, -size[1] / 4, 0},{-size[0] / 4, -size[1] / 4, 0},{-size[0] / 4, size[1] / 4, 0}};
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices_2), cube_vertices_2, GL_DYNAMIC_DRAW);
//    glEnableVertexAttribArray(pos_coord_box);
//    glVertexAttribPointer(pos_coord_box, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_color_box_2);
//    glEnableVertexAttribArray(pos_color_box);
//    glVertexAttribPointer(pos_color_box, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
////
//    for(int i = 0; i < 6; i++) {
//        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, (void*)(i * 4 * sizeof(GLushort)));
//    }
////
    
    
    
       // Generate VAO Id
//    glGenVertexArrays ( 1, &vaoId );
//    
//    // Bind the VAO and then setup the vertex
//    // attributes
//    glBindVertexArray ( userData->vaoId );
//    
//    glBindBuffer ( GL_ARRAY_BUFFER, userData->vboIds[0] );
//    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1] );
    
    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[0] );
    glEnableVertexAttribArray ( pos_coord_box );
    glVertexAttribPointer ( pos_coord_box, 3,
                           GL_FLOAT, GL_TRUE, sizeof(float) * 3, 0 );
//    
//
    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[1] );
    glEnableVertexAttribArray ( pos_color_box );
    glVertexAttribPointer ( pos_color_box, 3,
                           GL_FLOAT, GL_TRUE, sizeof(float) * 3, 0);

    glBindBuffer ( GL_ARRAY_BUFFER, vboIds[2] );
    glEnableVertexAttribArray ( texcoord );
    glVertexAttribPointer (texcoord, 2,
                           GL_FLOAT, GL_TRUE, sizeof(float) * 2, 0 );
    
//    glActiveTexture ( GL_TEXTURE0 );
//
//    glBindTexture ( GL_TEXTURE_2D, textureId );
//    //glActiveTexture ( GL_TEXTURE0 );
//    
//     glUniform1i ( samplerLoc, 0 );
    
    glDrawArrays(GL_TRIANGLES, 0,tjuNumVerts);

    // Reset to the default VAO
//    glBindVertexArray ( 0 );

    
////    glVertexPointer(3, GL_FLOAT, 0, bananaVerts);
////    glNormalPointer(GL_FLOAT, 0, bananaNormals);
////    glTexCoordPointer(2, GL_FLOAT, 0, bananaTexCoords);
////
//    glGenBuffers(1, &temp1);
//    glBindBuffer(GL_ARRAY_BUFFER, temp1);
//    glVertexAttribPointer(23123, 3, GL_FLOAT, GL_FALSE, 0,
//                         bananaVerts);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(bananaVerts), bananaVerts, GL_DYNAMIC_DRAW);
//    glGenBuffers(1, &temp2);
//    glBindBuffer(GL_ARRAY_BUFFER, temp2);
//    glVertexAttribPointer(224124, 3, GL_FLOAT, GL_FALSE, 0,
//                          bananaNormals);
////    glVertexAttribPointer(33213, 2, GL_FLOAT, GL_FALSE, 0,
////                          bananaTexCoords);
//    glEnableVertexAttribArray(23123);
//    glEnableVertexAttribArray(224124);
////    glEnableVertexAttribArray(33213);
////    
//    glDrawArrays(GL_TRIANGLES, 0, bananaNumVerts);
}

}
}
