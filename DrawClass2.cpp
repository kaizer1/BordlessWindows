
#include "DrawClass.h"

import lOpenGL;
import lLog;

using namespace losGraphics;


#include <iostream>
#include <string>
#include "FontHeaderOne.h"
#include "ShaderData2.h"
#include <ranges>
#include <windows.h>
#include <filesystem>
#include <iomanip>
#include <fstream>

uint32_t  utf8_to_utf32(const char* character)
{
    uint32_t result = -1;

    if (!character)
    {
        return result;
    }

    if ((character[0] & 0x80) == 0x0)
    {
        result = character[0];
    }

    if ((character[0] & 0xC0) == 0xC0)
    {
        result = ((character[0] & 0x3F) << 6) | (character[1] & 0x3F);
    }

    if ((character[0] & 0xE0) == 0xE0)
    {
        result = ((character[0] & 0x1F) << (6 + 6)) | ((character[1] & 0x3F) << 6) | (character[2] & 0x3F);
    }

    if ((character[0] & 0xF0) == 0xF0)
    {
        result = ((character[0] & 0x0F) << (6 + 6 + 6)) | ((character[1] & 0x3F) << (6 + 6)) | ((character[2] & 0x3F) << 6) | (character[3] & 0x3F);
    }

    if ((character[0] & 0xF8) == 0xF8)
    {
        result = ((character[0] & 0x07) << (6 + 6 + 6 + 6)) | ((character[1] & 0x3F) << (6 + 6 + 6)) | ((character[2] & 0x3F) << (6 + 6)) | ((character[3] & 0x3F) << 6) | (character[4] & 0x3F);
    }

    return result;
}


void DrawClass::setSize(int& widthMian, int& heightMain) {
    std::cout << " width1 = " << widthMian << " \n";
    std::cout << " height1  = " << heightMain << " \n";
    width = std::move(widthMian);
    height = std::move(heightMain);
    halfWidth = 2.0f / (float) width;
    halfHeight = 2.0f / (float) height;

    std::cout << " width2 = " << width << " \n";
    std::cout << " height2  = " << height << " \n";

}


void DrawClass::loadBufferMeshforButton() {

    GLuint b1, shot;
    glGenBuffersm(1, &b1);
    glGenBuffersm(1, &shot);
    checkErrorLos(66);
    GLfloat vertexM1[8] = {
             1.0f,0.0f,
            0.0f,0.0f,
            0.0f,1.0f,
            1.0f,1.0f
    };


    //lLogs::logPrintWindowsClear("logBuffer Mesh ");



    glBindBufferm(glArrayBuf, b1);
    {
        glBufferDatam(glArrayBuf, 8 * sizeof(GLfloat), vertexM1, glStatDraw);
        glVertexAttribPointerm(0, 2, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(0);
    }

    GLushort myShot[4] = {
          1, 0, 2, 3
    };



    glBindBufferm(glElementArrayBuffer, shot);
    glBufferDatam(glElementArrayBuffer, 4 * sizeof(glUnsignedShort), myShot, 0x88E4);

    glUseProgramm(0);
    glBindVertexArraym(0);
    checkErrorLos(66);

}


void DrawClass::loadBufferMesh() {

    GLuint b1, b2, b3;
    GLuint shot;
    glGenBuffersm(1, &b1);
    glGenBuffersm(1, &b2);
    glGenBuffersm(1, &b3);
    glGenBuffersm(1, &shot);
    checkErrorLos(65);
    GLfloat vertexM1[8] = {
             1.0f,0.0f,
            0.0f,0.0f,
            0.0f,1.0f,
            1.0f,1.0f  
    };

    GLfloat vertexM2[8] = {
         0.2f,0.3f,
        0.1f,0.4f,
        0.2f,0.7f,
        1.0f,0.0f
    };
    


    GLfloat vertexM3[8] = {
        0.3f, 0.2f,
        0.1f, 0.1f,
        0.1f, 0.1f,
        0.0f, 0.0f
    };

    //lLogs::logPrintWindowsClear("logBuffer Mesh ");



    glBindBufferm(glArrayBuf, b1);
    {
        glBufferDatam(glArrayBuf, 8 * sizeof(GLfloat), vertexM1, glStatDraw);
        glVertexAttribPointerm(0, 2, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(0);
    }


    glBindBufferm(glArrayBuf, b3);
    {
        glBufferDatam(glArrayBuf, 8 * sizeof(GLfloat), vertexM3, glStatDraw);
        glVertexAttribPointerm(2, 2, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(2);
    }

    glBindBufferm(glArrayBuf, b2);
    {
        glBufferDatam(glArrayBuf, 8 * sizeof(GLfloat), vertexM2, glStatDraw);
        glVertexAttribPointerm(1, 2, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(1);
    }


    GLushort myShot[4] = {
          1, 0, 2, 3
    };

    

    glBindBufferm(glElementArrayBuffer, shot);
    glBufferDatam(glElementArrayBuffer, 4 * sizeof(glUnsignedShort), myShot, 0x88E4);

    glUseProgramm(0);
    glBindVertexArraym(0);
    checkErrorLos(66);


}


void DrawClass::loadFontGrobold() {


    FontTextureLoad(&embeddeFontGrobold, LosFontos.tex_width, LosFontos.tex_height, LosFontos.tex_data);
    //glBindTexturem(glTex2D, 0);
    // LosFontBigs
    // 
    //glGenTextures(1, &embeddeFontGrobold); // was texid
    //glBindTexture(glTex2D, embeddeFontGrobold);
    //glTexParameteri(glTex2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // GL_CLAMP
    //glTexParameteri(glTex2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(glTex2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(glTex2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // was font
    //// was LosFontBigs .tex_width, LosFontBigs.tex_height
    //glTexImage2D(glTex2D, 0, GL_ALPHA, LosFontos.tex_width, LosFontos.tex_height,
    //    0, GL_ALPHA, GL_UNSIGNED_BYTE, LosFontos.tex_data);
    //glBindTexture(glTex2D, embeddeFontGrobold);

    //// glClearColor( 1, 1, 1, 1 );
    //// glEnable( GL_BLEND );
    //// glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glEnable(glTex2D);

}


void DrawClass::createRect() {
    std::cout << " create Rectangle " << " \n";
}

void DrawClass::createTeth() {
    std::cout << " create Tethraeder " << " \n";
}

void DrawClass::createSph() {
    std::cout << " create Sphere " << " \n";

}

void DrawClass::createTor() {
    std::cout << " create Torus " << " \n";
}

void DrawClass::createSot() {
    std::cout << " create Sota " << " \n";
}


void DrawClass::clearTouchValues() {

    for (int i = 0; auto & elem : myButton | std::views::reverse)
    {
        elem.setPr(false);
    }
}


void DrawClass::buildProgramScene() {

    lLogs::fileWriteWinAPi(std::string_view(" build Program Scene "));
    glGenVertexArraysm(1, &vaoScene);
    glBindVertexArraym(vaoScene);
    // create program
    programScene = glCreateProgram();
    checkErrorLos(62);
    auto shader1 = loadShaderLos(0x8B31, aSceneShader);
    auto shader2 = loadShaderLos(0x8B30, bSceneShader);
    glAttachShader(programScene, shader1);
    glAttachShader(programScene, shader2);
    linkAndValidateProgram(programScene);
    checkErrorLos(63);
    glUseProgramm(programScene);
    glBindAttribLocationm(programScene, 0, "aVertex");
    matrixSceneMain = glGetUniformLocationm(programScene, "matrixDraw");
    colorSceneUniform = glGetUniformLocationm(programScene, "colorUniform");
    checkErrorLos(64);
    if (matrixButtonMain == -1) {
        std::printf(" error in matrixMain ");
        return;
    }


    glDeleteShader(shader1);
    glDeleteShader(shader2);

    loadBufferMeshScene();

}


void DrawClass::loadBufferMeshScene() {

    GLuint b1, shot;
    glGenBuffersm(1, &b1);

    glGenBuffersm(1, &shot);
    checkErrorLos(65);
    GLfloat vertexM1[102] = {
             15.0f,0.0f, 0.0f,
             -15.0f, 0.0f, 0.0f,
             15.0f, 0.0f, -5.0f,
            -15.0f, 0.0f, -5.0f,
             15.0f,0.0f, 1.0f,
             -15.0f, 0.0f, 1.0f,
             15.0f, 0.0f, 2.0f,
            -15.0f, 0.0f, 2.0f,
               15.0f,0.0f, 3.0f,
             -15.0f, 0.0f, 3.0f,
             15.0f, 0.0f, 4.0f,
            -15.0f, 0.0f, 4.0f,
             15.0f,0.0f, 5.0f,
             -15.0f, 0.0f, 5.0f,
             15.0f, 0.0f, -4.0f,
            -15.0f, 0.0f, -4.0f,
            15.0f, 0.0f, -3.0f,
            -15.0f, 0.0f, -3.0f,
            15.0f, 0.0f, -2.0f,
            -15.0f, 0.0f, -2.0f,
             15.0f, 0.0f, -1.0f,
            -15.0f, 0.0f, -1.0f,
            2.0f, 0.0f, 10.0f,
            2.0f, 0.0f, -10.0f,  // 72 26 

             1.0f, 0.0f, 10.0f,
            1.0f, 0.0f, -10.0f,
             0.0f, 0.0f, 10.0f,
            0.0f, 0.0f, -10.0f,
             -1.0f, 0.0f, 10.0f,
            -1.0f, 0.0f, -10.0f,
             2.0f, 0.0f, 10.0f,
             2.0f, 0.0f, -10.0f,
            -2.0f, 0.0f, 10.0f,
            -2.0f, 0.0f, -10.0f,

            //0.0f,1.0f,
            //1.0f,1.0f
    };

    std::vector<float> myData;
    myData.reserve(60 * 3 * sizeof(float));
 
    for (int i = -30; i >= 30; i++) {
        

        float a = { 50.0f };
        float b = { float(i) }; 
        float c = { -50.0f };
        myData.push_back(a);
        myData.push_back(b);
        myData.push_back(c);

     }

    glBindBufferm(glArrayBuf, b1);
    {
        glBufferDatam(glArrayBuf, 102 * sizeof(GLfloat), vertexM1, glStatDraw);
        glVertexAttribPointerm(0, 3, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(0);
    }

  /*  GLushort myShot[4] = {
          1, 0, 2, 3
    };*/



    //glBindBufferm(glElementArrayBuffer, shot);
    //glBufferDatam(glElementArrayBuffer, 4 * sizeof(glUnsignedShort), myShot, 0x88E4);

    glUseProgramm(0);
    glBindVertexArraym(0);
    checkErrorLos(66);

}

void DrawClass::Parse3DFile(std::string& pathString) {


    std::fstream getModel;
    getModel.open(pathString.c_str(), std::ios::in);

    using std::operator""sv;

    std::vector<float> myElements;
    std::vector<int>  myIndexes;

    if (getModel.is_open()) {
        std::string tp;
        while (getline(getModel, tp)) {
            //std::printf(R"(my line string = %s )", tp ); 
            //std::cout << " my string " << tp << " \n";
    
            auto a = tp.find_first_of(" ");
            std::string ad = tp.substr(0, a);
            //std::cout << " my lenght = " << tp.length() << " \n";
            auto adNew = tp.substr(a+1, tp.length());
            constexpr auto delim{" "sv};
            //std::cout << " my first symbol " << ad << " \n";

            if (ad == "v") {
                //std::cout << "V !  " << " \n";
                for (const auto word : std::views::split(adNew, delim)) {
                    //std::cout << std::quoted(std::string_view(word)) << " \n";
                    myElements.push_back(std::stof(std::string(std::string_view(word))));
                    
                }
            }
            else if (ad == "vn") {
                //std::cout << "VN !  " << " \n";
            }
            else if (ad == "vt") {
                //std::cout << "VT !  " << " \n";
            }
            else if (ad == "f") {
               // std::cout << "fF " << " \n";

                for (const auto word : std::views::split(adNew, delim)) {
                    //std::cout << std::quoted(std::string_view(word)) << " \n";
                    
                    auto sOne = std::string(std::string_view(word));
                    //std::cout << " my piece f string = " << sOne << " \n";
                    auto a = sOne.find_first_of("/");
                    auto a2 = sOne.substr(0, a);
                    //std::cout << " value final " << a2 <<  " \n";
                    myIndexes.push_back(std::stol(a2));
                    //myElements.push_back(std::stof(std::string(std::string_view(word))));
                }

            }
            else {
                std::cout << " no this other " << " \n";
            }
            

           // std::string_view ad4 = tp.substr(-1, a + 3);
           // std::cout << " my first symbol " << ad4 << " \n";
            
        }
        getModel.close();
    }



 /*   std::cout << " my size buffer " << myElements.size() << " \n";
    for (int i = 0; i < 100; i++) {
        std::cout << " elem = " << i << " " << myElements[i] << " \n";
    }*/


    //glGenVertexArraysm(1, &meshVao);

    glUseProgramm(programMesh);
    glBindVertexArraym(meshVao);

    
    GLuint bVertex, shotIndexes;
    glGenBuffersm(1, &bVertex);
    glGenBuffersm(1, &shotIndexes);
    checkErrorLos(35);

    
    


    glBindBufferm(glArrayBuf, bVertex);
    {
        glBufferDatam(glArrayBuf, myElements.size() * sizeof(GLfloat), myElements.data(), glStatDraw);
        glVertexAttribPointerm(0, 3, glFloat, GLFALSE, 0, (const void*)0);
        glEnableVertexAttribArraym(0);
    }


    glBindBufferm(glElementArrayBuffer, shotIndexes);
    glBufferDatam(glElementArrayBuffer, myIndexes.size() * sizeof(glUnsignedInt), myIndexes.data(), 0x88E4);

    glUseProgramm(0);
    glBindVertexArraym(0);
    checkErrorLos(66);

    loadObject = true;
    sizeIndexes = myIndexes.size();
    
    

}


void DrawClass::loading3D_Model() {
     

    WCHAR pathNames[MAX_PATH] = L"";
    LPWSTR openedFileName = pathNames;  //[MAX_PATH]; // = new LPWSTR{ "sdlkfjalskdjf" };
    lCallbackWinLoad(openedFileName);

    

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, pathNames, (int)wcslen(pathNames), NULL, 0, NULL, NULL);
    char* strTo = (char*)malloc(size_needed);
    WideCharToMultiByte(CP_UTF8, 0, pathNames, (int)wcslen(pathNames), strTo, size_needed, NULL, NULL);

    //WideCharToMultiByte

    std::cout << " my values = " << strTo << " \n";

    std::string path{ strTo };

    std::size_t found = path.find_last_of(".obj");
    auto aNewString = path.substr(0, found+1);
    std::cout << " my new path == " << aNewString.c_str() << " \n";
    
    std::filesystem::path myCurrentPath{ aNewString };
    if (std::filesystem::exists(myCurrentPath) && myCurrentPath.extension() == ".obj") {
        std::printf(" ok, my file exists and extension == obj \n");


        //loadObject = false;
        //glDeleteVertexArraysm(1, &meshVao);

        //athre.join();
        Parse3DFile(aNewString);
        

    }
    else {
        std::printf("file no exists  ");
        return;
    }

 
}

void DrawClass::buildProgramMesh() {

    glGenVertexArraysm(1, &meshVao);
    glBindVertexArraym(meshVao);
    programMesh = glCreateProgram();
    checkErrorLos(62);
    auto shader1 = loadShaderLos(0x8B31, aMeshShader);
    auto shader2 = loadShaderLos(0x8B30, bMeshShader);
    glAttachShader(programMesh, shader1);
    glAttachShader(programMesh, shader2);
    linkAndValidateProgram(programMesh);
    checkErrorLos(63); 
    glUseProgramm(programMesh);
    glBindAttribLocationm(programMesh, 0, "aVertex");
    matrixMeshMain = glGetUniformLocationm(programMesh, "matrixDraw");
    colorMeshUniform = glGetUniformLocationm(programMesh, "colorUniform");
    checkErrorLos(64);
    if (matrixMeshMain == -1) {
        std::printf(" error in matrixMain ");
        return;
    }


    glDeleteShader(shader1);
    glDeleteShader(shader2);


}

void DrawClass::buildProgramPostProcess() {

}



 bool DrawClass::buildProgramButton()
{

    checkErrorLos(62);
    //ui *aaa = new ui(10);

    lLogs::fileWriteWinAPi(std::string_view(" build Program Button"));
    glGenVertexArraysm(1, &vaoButton);
    glBindVertexArraym(vaoButton);
    // create program
    programButton = glCreateProgram();
    checkErrorLos(62);
    auto shader1 = loadShaderLos(0x8B31, aButtonShader);
    auto shader2 = loadShaderLos(0x8B30, bButtonShader);
    glAttachShader(programButton, shader1);
    glAttachShader(programButton, shader2);
    linkAndValidateProgram(programButton);
    checkErrorLos(63);
    glUseProgramm(programButton);
    glBindAttribLocationm(programButton, 0, "aVertex");
    matrixButtonMain = glGetUniformLocationm(programButton, "matrixDraw");
    colorButtonUniform = glGetUniformLocationm(programButton, "colorUniform");
    checkErrorLos(64);
    if (matrixButtonMain == -1) {
        std::printf(" error in matrixMain ");
        return false;
    }
    

    glDeleteShader(shader1);
    glDeleteShader(shader2);

    loadBufferMeshforButton();

    return true;
    
}


 bool DrawClass::buildProgramFont()
{


}


inline static const std::string ior = ".";
void DrawClass::print_atF(GLuint& programFont,
    GLuint& fonaVAO, GLuint& uniformSample, GLuint& matrixFont, GLuint& fontVBOfragment,
    float pen_x, float pen_y, float& number)
{
    const std::string ae = std::to_string(number);
    const std::string ae2 = ae.substr(0, 6);
    std::size_t fIl = ae2.find(ior);
    bool existsPoint = false;
    if (fIl != std::string::npos) {
        existsPoint = true;
        // logRun(" ok this ! %d \n", fIl);
    }

    const char* text = ae2.c_str();
    glUseProgramm(programFont); // programFont
    glBindVertexArraym(fonaVAO);

    glEnablem(glBlend);
    glDisablem(glDepthTest);

    glActiveTexturem(0x84C0);
    glUniform1im(uniformSample, 0);  //
    glBindTexturem(glTex2D, embeddeFontGrobold);  // embeddedFont embeddeFontGrobold

    size_t j;
    //for( i=0; i < strlen(text); ++i)
   // i=0; i < strlen(text); ++i
    const auto serr = strlen(text);
    for (auto a = 0; a < serr; a++)
    {

        texture_glyph_tS* glyph = nullptr;

        for (j = 0; j < LosFontos.glyphs_count; ++j)
        {
            if (LosFontos.glyphs[j].codepoint == utf8_to_utf32(text + a))
            {
                glyph = &LosFontos.glyphs[j];
                break;
            }
        }
        if (!glyph)
        {
            continue;
        }
        float x = pen_x + glyph->offset_x;
        float y = pen_y + glyph->offset_y;
        float w = glyph->width;
        float h = glyph->height;



        GLfloat fontFrag[] =
        {
                glyph->s1, glyph->t0,
                glyph->s0, glyph->t0,
                glyph->s1, glyph->t1,
                glyph->s0, glyph->t1,
        };

        const auto VERTEXOf = 0;


        glBindBufferm(glArrayBuf, fontVBOfragment);
        glBufferDatam(glArrayBuf, 8 * sizeof(GLfloat), fontFrag, glStatDraw);
        glVertexAttribPointerm(1, 2, glFloat, GLFALSE, 0, (const void*)VERTEXOf);
        glEnableVertexAttribArraym(1);


        float aWidthH;
        if (existsPoint && a == fIl) {
            aWidthH = 12.0f;
        }
        else {
            aWidthH = 42.0f;
        }

        matrixButton[0][0] = (halfWidth * aWidthH);
        matrixButton[1][1] = (halfHeight * aWidthH);
        matrixButton[3][0] = (halfWidth * pen_x) - 1;  // x_midToPlace   xMidFont
        matrixButton[3][1] = (1 - (halfHeight * pen_y));


        //        const float texLLev = 65536.0f;
        //        const float texWWl = 140.0f;
        //         glUniform1f(texwLevel, 65536.0f);
        //           glUniform1f(texW, 140.0f);
        glUniformMatrix4fv(matrixFont, 1, GLFALSE, &(matrixButton[0][0]));
        glDrawArraysm(glTrianglesStrip, 0, 4);

        if (existsPoint && a == fIl) {
            pen_x += 8.0f;
        }
        else {
            pen_x += 37.0f;
        }
        //  pen_y += glyph->advance_y;
    }

    glDisablem(glBlend);
}
