#pragma once

//#include <GL/GL.h>
//#include <glext.h>
#include <cstdint>
#include <memory>
#include "lDefine.h"


using ui = unsigned int;

import lOpenGL;

//
//struct ColorM  {
//	
//	blue 
//
//};

struct RectBase {


public: 
	RectBase() {
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	 
	RectBase(float& x1, float& y1, float& width1, float& height1) {
		x = std::move(x1);
		y = std::move(y1);
		width = std::move(width1);
		height = std::move(height1);
	}


	float x;
	float y;
	float width;
	float height;

};

class DrawClass
{ 

public: 

	DrawClass();
	void DestroyAll() const noexcept;
	[[ nodiscard ]] bool buildProgram(ui& vao, ui& program, ui& matrixMain, ui& colorUniform, ui& thicknessUni)  noexcept;
	
	// RectBase& baseRect
	void drawRectangle() noexcept;
	void loadBufferMesh();
	void cleanColor();

	void buildP();

	void setSize(int& widthMian, int& heightMain);

	void renderReady() {
		renderAReadyToDraw = true;
	}


	void print_atF(GLuint& programFont,
		GLuint& fonaVAO, GLuint& uniformSample, GLuint& matrixFont, GLuint& fontVBOfragment, float pen_x, float pen_y, float& number);

private: 

	int width;
	int height;

	float halfWidth;
	float halfHeight;

	float matrixButton[4][4];

	ui programRect;
	ui programFont;

	ui vaoRectDraw;
	ui matrixRectDraw;
	ui colorUniformMatrixDraw;
	ui thinkNess;
	 
    void updateMatrix();
	bool renderAReadyToDraw = false;

	ui texId;
	ui texture;
	ui texBorder;
 
	ui embeddeFontGrobold;

	void loadFontGrobold();
};

