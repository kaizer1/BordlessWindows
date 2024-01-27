#pragma once

#define WGL_DRAW_TO_WINDOW_ARB         0x2001
#define WGL_ACCELERATION_ARB           0x2003
#define WGL_SWAP_METHOD_ARB            0x2007
#define WGL_SUPPORT_OPENGL_ARB         0x2010
#define WGL_DOUBLE_BUFFER_ARB          0x2011
#define WGL_PIXEL_TYPE_ARB             0x2013
#define WGL_COLOR_BITS_ARB             0x2014
#define WGL_DEPTH_BITS_ARB             0x2022
#define WGL_STENCIL_BITS_ARB           0x2023
#define WGL_FULL_ACCELERATION_ARB      0x2027
#define WGL_SWAP_EXCHANGE_ARB          0x2028
#define WGL_TYPE_RGBA_ARB              0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_TEXTURE0                       0x84C0
#define GL_BGRA                           0x80E1
#define GL_ELEMENT_ARRAY_BUFFER           0x8893


const static char aShader[] =
"#version 430                    \n"
"                                \n"
"layout (location = 0) in vec2 aVertex;           \n"
"layout (location = 1) in vec2 tex;            \n"
"layout (location = 2 ) in vec2 border;            \n"
"//layout (location = 2) in vec2 texturecoordinate; \n"
"                                \n"
"uniform mat4 matrixDraw;        \n"
"uniform vec2 thickness;         \n"
"uniform vec2 texBorder;		 \n"	
"//uniform vec2 bo				 \n"
"								 \n"	
"//out vec2 texColor;              \n"
"out vec2 texCoord;              \n"
"                                \n"
"void main()                     \n"
" {                              \n"
"                                \n"
"  //texColor = bColor;            \n"
"  //texCoord =  texturecoordinate; \n"
"  vec2 invBorder = vec2(1,1) - border; \n"
"  vec2 shiftedPosition = (aVertex - thickness*invBorder*aVertex); \n"
"  shiftedPosition *= 0.5; \n"
"  shiftedPosition += 0.5; \n"
"  gl_Position = matrixDraw * vec4(aVertex.xy, 0.0, 1.0);  \n"
"  texCoord =  tex + invBorder * -aVertex * texBorder; \n"
" }";





const static char bShader[] =
"#version 430                 \n"
"                                       \n"
"#ifdef GL_FRAGMENT_PRECISION_HIGH              \n"
"precision highp float;                         \n"
"#else                                          \n"
"precision mediump float;                       \n"
"#endif                                         \n"
"                                       \n"
"                                       \n"
"                                       \n"
"uniform sampler2D simpleTexture; \n"
"uniform vec3      colorUniform;  \n"
"//in vec2 texColor;              \n"
"in vec2 texCoord;                \n"
"out vec4 finalCl;                \n"
"                                 \n"
"void main()                      \n"
" {                              \n"
" finalCl = vec4(colorUniform.xyz, 1.0); \n"
" //finalCl = texture(simpleTexture, texCoord) * vec4(colorUniform.xyz, 1.0); \n"
" }";



const char aShaderTexture[] =
"#version 420       \n"
"                                      \n"
"layout(location = 0) in vec2 aVertex; \n"
"layout(location = 1) in vec2 bColor;  \n"
"                            \n"
"uniform mat4 matrixFinal;   \n"
"out vec2 colorGo;          \n"
"                                                     \n"
"                                                     \n"
"                                                     \n"
"void main()                                          \n"
"{                                                    \n"
"    colorGo = bColor;                                \n"
"gl_Position = matrixFinal * vec4(aVertex, 0.0, 1.0); \n"
"                     \n"
"}";




const char bShaderTexture[] =
"#version 420             \n"
"                         \n"
"precision mediump float; \n"
"                         \n"
"uniform sampler2D textureFinal;                 \n"
"in vec2 colorGo;							     \n"
"												 \n"
"out vec4 HalfDraw;								 \n"
"												 \n"
"void main()									 \n"
"{											     \n"
"												 \n"
"   HalfDraw = texture(textureFinal, colorGo);   \n"
"												 \n"
"}";
