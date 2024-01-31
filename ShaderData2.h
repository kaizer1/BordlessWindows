#pragma once


const static char aButtonShader[] =
"#version 420                    \n"
"                                \n"
"layout (location = 0) in vec2 aVertex;           \n"
"                                \n"
"uniform mat4 matrixDraw;        \n"
"								 \n"
"out vec2 texCoord;              \n"
"                                \n"
"void main()                     \n"
" {                              \n"
"														   \n"
"  gl_Position = matrixDraw * vec4(aVertex.xy, 0.0, 1.0);  \n"
"													       \n"
" }";





const static char bButtonShader[] =
"#version 420                 \n"
"                                       \n"
"#ifdef GL_FRAGMENT_PRECISION_HIGH              \n"
"precision highp float;                         \n"
"#else                                          \n"
"precision mediump float;                       \n"
"#endif                                         \n"
"                                       \n"
"                                       \n"
"                                       \n"
"uniform vec3      colorUniform;  \n"
"								  \n"
"out vec4 finalCl;                \n"
"								  \n"		
"void main()                      \n"
" {                               \n"
"								  \n"					
"   finalCl = vec4(colorUniform.xyz, 1.0); \n"
"								  \n"
" }";

const static char aSceneShader[] = 
"#version 420                    \n"
"                                \n"
"layout (location = 0) in vec3 aVertex;           \n"
"                                \n"
"uniform mat4 matrixDraw;        \n"
"								 \n"
"//out vec2 texCoord;              \n"
"                                \n"
"void main()                     \n"
" {                              \n"
"														   \n"
"  gl_Position = matrixDraw * vec4(aVertex.xyz, 1.0);  \n"
"													       \n"
" }";



const static char bSceneShader[] =
"#version 420                 \n"
"                                       \n"
"#ifdef GL_FRAGMENT_PRECISION_HIGH              \n"
"precision highp float;                         \n"
"#else                                          \n"
"precision mediump float;                       \n"
"#endif                                         \n"
"                                       \n"
"                                       \n"
"                                       \n"
"uniform vec3      colorUniform;  \n"
"								  \n"
"out vec4 finalCl;                \n"
"								  \n"
"void main()                      \n"
" {                               \n"
"								  \n"
"   finalCl = vec4(colorUniform.xyz, 1.0); \n"
"								  \n"
" }";





const static char aMeshShader[] =
"#version 420                    \n"
"                                \n"
"layout (location = 0) in vec3 aVertex;           \n"
"                                \n"
"uniform mat4 matrixDraw;        \n"
"								 \n"
"//out vec2 texCoord;              \n"
"                                \n"
"void main()                     \n"
" {                              \n"
"														   \n"
"  gl_Position = matrixDraw * vec4(aVertex.xyz, 1.0);  \n"
"													       \n"
" }";



const static char bMeshShader[] =
"#version 420                 \n"
"                                       \n"
"#ifdef GL_FRAGMENT_PRECISION_HIGH              \n"
"precision highp float;                         \n"
"#else                                          \n"
"precision mediump float;                       \n"
"#endif                                         \n"
"                                       \n"
"                                       \n"
"                                       \n"
"uniform vec3      colorUniform;  \n"
"								  \n"
"out vec4 finalCl;                \n"
"								  \n"
"void main()                      \n"
" {                               \n"
"								  \n"
"   finalCl = vec4(colorUniform.xyz, 1.0); \n"
"								  \n"
" }";
