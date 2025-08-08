
#include "DrawClass.h"
#include "shaderData.h"
#include <memory>
#include <ranges>

#include <string_view>
#include <iostream>


import lOpenGL;
import lLog;
import lMath;

using namespace losGraphics;


DrawClass::DrawClass() {

	
	createRectangle = [this]() { createRect(); };
	createTethraeder = [this]() { createTeth(); };
	createSphere = [this]() { createSph(); };
	createTorus = [this]() { createTor(); };
	createSota = [this]() { createSot(); };
	loadModel = [this]() { loading3D_Model();  };
	
	

	myButton[0].setFunc(createRectangle);
	myButton[1].setFunc(createTethraeder);
	myButton[2].setFunc(createSphere);
	myButton[3].setFunc(createTorus);
	myButton[4].setFunc(createSota);
	myButton[5].setFunc(loadModel);

	
	buildProgram(vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw, thinkNess, resolut);
	loadBufferMesh();
	loadASTC("Diffuse2.astc", &texId);
	//buildProgram(vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw);
	buildProgramButton();

	for (auto& i : matrixButton)
		for (float& j : i)
			j = 0.0f;

	matrixButton[3][3] = 1.0f;

	buildProgramScene();
	buildProgramMesh();
	buildProgramPostProcess();

	float aW = 1100.0f;
	float aH = 820.0f;
	lCamera = std::make_unique<losMath::Camera>(aW, aH);
}


void DrawClass::emptyMousePlace(int xMouse, int yMouse) {

	// lLogs::logPrintWindowsClear("my empty x ", xMouse);
	// lLogs::logPrintWindowsClear("my empty y ", yMouse);
	
}

void DrawClass::DestroyAll()const noexcept {

	lLogs::closeLogsWrite();
	
	glDeleteVertexArraysm(1, &vaoRectDraw);
	glDeleteVertexArraysm(1, &vaoButton);
	glDeleteVertexArraysm(1, &vaoScene);
	glDeleteProgramm(programRect);
	glDeleteProgramm(programButton);
	glDeleteProgramm(programScene);

}


bool DrawClass::buildProgram(ui& vao, ui& program, ui& matrixMain, ui& colorUniform, ui& thicknessUni, ui& resolution)  noexcept {
	// vao 
	checkErrorLos(61);
	//ui *aaa = new ui(10);

	lLogs::fileWriteWinAPi(std::string_view(" build Program  "));
	glGenVertexArraysm(1, &vao);
	glBindVertexArraym(vao);
	// create program
	program = glCreateProgram();
	checkErrorLos(62);
	auto shader1 = loadShaderLos(0x8B31, aShader);
	auto shader2 = loadShaderLos(0x8B30, bShader);
	glAttachShader(program, shader1);
	glAttachShader(program, shader2);
	linkAndValidateProgram(program);
	checkErrorLos(63);
	glUseProgramm(program);
	glBindAttribLocationm(program, 0, "aVertex");
	glBindAttribLocationm(program, 2, "border");
	glBindAttribLocationm(program, 1, "tex");
	matrixMain =   glGetUniformLocationm(program, "matrixDraw");
	colorUniform = glGetUniformLocationm(program, "colorUniform");
	thicknessUni = glGetUniformLocationm(program, "thickness");
	resolution =   glGetUniformLocationm(program, "resolutions");
	texture =      glGetUniformLocationm(program, "simpleTexture");
	texBorder =    glGetUniformLocationm(program, "texBorder");
	screeOffset = glGetUniformLocationm(program, "sccreenOFf");
	checkErrorLos(64);
	if (matrixMain == -1) {
		std::printf(" error in matrixMain ");
		return false;
	}

	glDeleteShader(shader1);
	glDeleteShader(shader2);
	return true;
}




void DrawClass::buildP() {

}



void DrawClass::cleanColor() {

    losGraphics::callClear(110.0f/255.0f, 107.0f/255.0f, 102.f/255.0f, 1.0f); // 0.3f, 0.5f, 0.8f 
}

void DrawClass::zoomIn() {

	lCamera->zoomIn();

}


void DrawClass::zoomOut()  {

	lCamera->zoomOut();
}


void DrawClass::pressMouse(const long& x,const long& y, losMath::PressVaraint press) {

	if (press == losMath::PressVaraint::MouseDown) {
		std::cout << " mouse press Down " << " \n";

		for (int i = 0; auto & elem : myButton)
		{
			if (x >= elem.x && x <= (elem.x + elem.width) && (y <= elem.y) && (y > elem.y - elem.height)) {
				std::cout << " in buttons contains1 " << " \n";
				//elem.callBackFunc();
				elem.setPr(true);
			}
		}

		MouseDownIS = true;
		lCamera->StartDown(x, y);

	} else if (press == losMath::PressVaraint::MouseUp) {
		std::cout << " mouse press  Up" << " \n";

		for (int i = 0; auto & elem : myButton)
		{
			if (x >= elem.x && x <= (elem.x + elem.width) && (y <= elem.y) && (y > elem.y - elem.height)) {
				std::cout << " in buttons contains22 " << " \n";
				//elem.callBackFunc();
				if (elem.returnPress()) {
					//std::cout << " ok press M  " << " \n";
					elem.callBackFunc();
				}
			}
		}


		


		clearTouchValues();
		MouseDownIS = false;
	 }


	if (press == losMath::PressVaraint::MouseMove && MouseDownIS) {
		lCamera->Motion(x, y, press);
	}


	if (press == losMath::PressVaraint::MouseDownRight) {

		MouseDownIS = true;
		//MouseDownIS = 
	}


	if (press == losMath::PressVaraint::MouseDownRigthUp) {

		MouseDownIS = false;
		//MouseDownIS = 
	}

	// check contains press to Button 
	
}

void DrawClass::updateMatrix(const losMath::ButtonD& buttonToDraw) noexcept{
	matrixButton[0][0] = (halfWidth * buttonToDraw.width);  // width
	matrixButton[1][1] = (halfHeight) * (buttonToDraw.height); // height 
	matrixButton[3][0] = (halfWidth * buttonToDraw.x) - 1; // x_start_point to middle in this ( no, normal work ) 
	matrixButton[3][1] = (1 - (halfHeight * buttonToDraw.y));  // another to width start x point 

}

void DrawClass::updateMatrix(float width, float height, float startX, float startY ) {
	 
	
	// 200, 320, 14, 340 
	matrixButton[0][0] = (halfWidth * width);  // width
	matrixButton[1][1] = (halfHeight) * ( height); // height 
	matrixButton[3][0] = (halfWidth * startX) - 1; // x_start_point to middle in this ( no, normal work ) 
	matrixButton[3][1] = (1 - (halfHeight * startY));  // another to width start x point 

	
	//lLogs::logPrintWindowsClearFloat(" [0][0]", matrixButton[0][0]);
	//lLogs::logPrintWindowsClearFloat(" [1][1]", matrixButton[1][1]);
	//lLogs::logPrintWindowsClearFloat(" [3][0]", matrixButton[3][0]);
	//lLogs::logPrintWindowsClearFloat(" [3][1]", matrixButton[3][1]);
	//std::cout << " width = " << width << " \n";   // 820
	//std::cout << " height = " << height << " \n"; // 1100 
	//std::cout << " [0][0] " << matrixButton[0][0] << " \n";
	//std::cout << " [1][1] " << matrixButton[1][1] << " \n";
	//std::cout << " [3][0] " << matrixButton[3][0] << " \n";
	//std::cout << " [3][1] " << matrixButton[3][1] << " \n";
	
	//  width1 = 61056
	//	height1 = 61679
	//	width2 = 61056
	//	height2 = 61679
}


void DrawClass::cameraReadyUpdate() {

}

// RectBase& baseRect =
void DrawClass::drawRectangle() noexcept {

	//vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw

	checkErrorLos(1);


	if (renderAReadyToDraw) {
		


		// TODO:: main 3D Scene Draw 

		float* sdf = new float[3];
		sdf[0] = 1.0f;
		sdf[1] = 1.0f;
		sdf[2] = 1.0f;


		cameraReadyUpdate();


		glBindVertexArraym(vaoScene);
		glUseProgramm(programScene);
		
		glUniform3fvm(colorSceneUniform, 1, sdf);
		glUniformMatrix4fv_m(matrixSceneMain, 1, GLFALSE, &lCamera->getPALMatrix().elements[0][0]);
		glDrawArraysm(glLines, 0, 32);


		// main 3D  Object 

		

		if (loadObject) {

			

			//std::cout << " in object's print and draw " << " \n";

			glUseProgramm(programMesh);
			glBindVertexArraym(meshVao);
			glUniformMatrix4fv_m(matrixMeshMain, 1, GLFALSE, &lCamera->getPALMatrix().elements[0][0]);

			sdf[0] = 0.1f;
			sdf[1] = 0.2f;
			sdf[2] = 0.1f;

			glUniform3fvm(colorMeshUniform, 1, sdf);
			drawElements(glTriangles, sizeIndexes, glUnsignedInt, 0);

			
		}


		// UI draw start 

		glUseProgramm(programRect);
		glBindVertexArraym(vaoRectDraw);


		glActiveTexturem(0x84C0);
		glUniform1im(texture, 0);
		glBindTexturem(glTex2D, texId);

		

		checkErrorLos(2);
		updateMatrix(200.0f, 320.0f, 14.0f, 340.0f);


		//float* sdf = new float[3];
		sdf[0] = 0.9f;
		sdf[1] = 0.5f;
		sdf[2] = 0.8f;
		


		// lLogs::logPrintWindows();
	    // lLogs::logPrintWindowsClear("sdfsdf", 1);


		glEnablem(glBlend);
		glBlendFuncmOne();
		glEnablem(glDepthTest);


		glUniformMatrix4fv_m(matrixRectDraw, 1, GLFALSE, &matrixButton[0][0]);
		checkErrorLos(5);
		glUniform3fvm(colorUniformMatrixDraw, 1, sdf);
		checkErrorLos(51);
		glUniform2fm(thinkNess, 0.1f, 0.1f);
		checkErrorLos(4);
		// 1100 820
		glUniform2fm(resolut, 200.0f, 320.0f);  // 200.0f, 320.0f 
		glUniform2fm(screeOffset, 14.0f, 480.0f); // 14.0f, 480.0f 
		glUniform2fm(texBorder, 0.1f, 0.7f);
		drawElements(glTrianglesStrip, 4, glUnsignedShort, 0);
		
		

		// drawButton's to menu select 

		glDisablem(glBlend);
		glDisablem(glDepthTest);

		checkErrorLos(40);
	
		glUseProgramm(programButton);
		glBindVertexArraym(vaoButton);


		checkErrorLos(34);

		sdf[0] = 0.1f;
		sdf[1] = 0.3f;
		sdf[2] = 0.3f;
		checkErrorLos(33);


		for (int i = 0; const auto & elem : myButton | std::views::reverse)
		{
			updateMatrix(elem);
			glUniformMatrix4fv_m(matrixButtonMain, 1, GLFALSE, &matrixButton[0][0]);
			glUniform3fvm(colorButtonUniform, 1, sdf);
			checkErrorLos(31);
			drawElements(glTrianglesStrip, 4, glUnsignedShort, 0);
		}


	}
	checkErrorLos(3);

}