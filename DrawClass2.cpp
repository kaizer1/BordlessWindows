
#include "DrawClass.h"

import lOpenGL;
import lLog;

using namespace losGraphics;


#include <iostream>
#include <string>
#include "FontHeaderOne.h"


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

    lLogs::logPrintWindowsClear("logBuffer Mesh ");



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
