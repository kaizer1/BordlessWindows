#pragma once

//#include <GL/GL.h>
//#include <glext.h>
#include <cstdint>
#include <memory>
#include <vector>
#include "lDefine.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <windows.h>

using ui = unsigned int;

import lOpenGL;
import lMath;

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
	[[ nodiscard ]] bool buildProgram(ui& vao, ui& program, ui& matrixMain, ui& colorUniform, ui& thicknessUni, ui& resolution)  noexcept;
	[[ nodiscaed ]] bool buildProgramButton();
	[[ nodiscard ]] inline bool buildProgramFont();
 	// RectBase& baseRect
	void drawRectangle() noexcept;
	void loadBufferMesh();
	void cleanColor();
	void pressMouse(const long& x,const long& y, losMath::PressVaraint press);

	void createRect();
	void createTeth(); 
    void createSph(); 
	void createTor();
	void createSot();


	void buildP();

	void setSize(int& widthMian, int& heightMain);

	void renderReady() {
		renderAReadyToDraw = true;
	}

	void emptyMousePlace(int xMouse, int yMouse);

	void print_atF(GLuint& programFont,
		GLuint& fonaVAO, GLuint& uniformSample, GLuint& matrixFont, GLuint& fontVBOfragment, float pen_x, float pen_y, float& number);

	
	std::function<void()> createRectangle;
	std::function<void()> createTethraeder;
	std::function<void()> createSphere;
	std::function<void()> createTorus;
	std::function<void()> createSota;
	std::function<void()> loadModel;
	std::function<void(LPWSTR szFileName)> lCallbackWinLoad;
	void changeDrawRenderAReady() { renderAReadyToDraw = false; }

	void setLoadCallback(std::function<void(LPWSTR szFileName)>& funL) {
		lCallbackWinLoad = std::move(funL);
	}

protected:

	void simpleCall();
	void loading3D_Model();
	void Parse3DFile(std::string& pathString);

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
	ui resolut;
	ui screeOffset;
	 
    void updateMatrix(float width, float height, float startX, float startY);
	void updateMatrix(const losMath::ButtonD& buttonToDraw) noexcept;
	bool renderAReadyToDraw = false;

	ui texId;
	ui texture;
	ui texBorder;
	bool MouseDownIS;
 
	ui embeddeFontGrobold;

	void loadFontGrobold();


	ui programButton;
	ui vaoButton;
	ui matrixButtonMain;
	ui colorButtonUniform;
	void loadBufferMeshforButton();
	

	ui vaoScene;
	ui programScene;
	ui matrixSceneMain;
	ui colorSceneUniform;

	void clearTouchValues();
	void loadBufferMeshScene();

	void buildProgramScene();
	void buildProgramMesh();
	void buildProgramPostProcess();

	
	std::unique_ptr<losMath::Camera> lCamera;

	void cameraReadyUpdate();
	 std::vector<losMath::ButtonD> myButton{ losMath::ButtonD { 48, 80, 24, 24 },
		losMath::ButtonD{ 73, 80, 24, 24}, losMath::ButtonD{98, 80, 24, 24 }, losMath::ButtonD{123,80, 24, 24}, losMath::ButtonD{148, 80, 24, 24}, losMath::ButtonD{66, 260, 110, 36} };



	 ui meshVao;
	 ui programMesh;
	 ui matrixMeshMain;
	 ui colorMeshUniform;
	 bool loadObject = false;
	 size_t sizeIndexes;
};

