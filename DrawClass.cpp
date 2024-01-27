import lOpenGL;
import lLog;
#include "DrawClass.h"
#include "shaderData.h"

#include <string_view>

using namespace losGraphics;


DrawClass::DrawClass() {
	
	
	
	buildProgram(vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw, thinkNess);
	loadBufferMesh();
	loadASTC("Diffuse2.astc", &texId);
	//buildProgram(vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw);

	for (auto& i : matrixButton) // was simple  for i : 5 < and other
		for (float& j : i)
			j = 0.0f;

	matrixButton[3][3] = 1.0f;

	

}



void DrawClass::DestroyAll() const noexcept {

	lLogs::closeLogsWrite();
	
	glDeleteVertexArraysm(1, &vaoRectDraw);
	glDeleteProgramm(programRect);

}


bool DrawClass::buildProgram(ui& vao, ui& program, ui& matrixMain, ui& colorUniform, ui& thicknessUni)  noexcept {
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
	matrixMain = glGetUniformLocationm(program, "matrixDraw");
	colorUniform = glGetUniformLocationm(program, "colorUniform");
	thicknessUni = glGetUniformLocationm(program, "thickness");
	texture = glGetUniformLocationm(program, "simpleTexture");
	texBorder = glGetUniformLocationm(program, "texBorder");
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

#include <iostream>

void DrawClass::cleanColor() {

    losGraphics::callClear(0.3f, 0.5f, 0.8f, 1.0f);
}


void DrawClass::updateMatrix() {
	 
	
	matrixButton[0][0] = (halfWidth * 200.0f);  // width
	matrixButton[1][1] = (halfHeight) * ( 320.0f); // height 
	matrixButton[3][0] = (halfWidth * 14.0f) - 1; // x_start_point to middle in this ( no, normal work ) 
	matrixButton[3][1] = (1 - (halfHeight * 340.0f));  // another to width start x point 

	
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


// RectBase& baseRect =
void DrawClass::drawRectangle() noexcept {

	//vaoRectDraw, programRect, matrixRectDraw, colorUniformMatrixDraw

	checkErrorLos(1);


	if (renderAReadyToDraw) {
		

		glUseProgramm(programRect);
		glBindVertexArraym(vaoRectDraw);


		glActiveTexturem(0x84C0);
		glUniform1i(texture, 0);
		glBindTexturem(glTex2D, texId);


		checkErrorLos(2);
		updateMatrix();


		float* sdf = new float[3];
		sdf[0] = 0.9f;
		sdf[1] = 0.5f;
		sdf[2] = 0.8f;
		

		// lLogs::logPrintWindows();
	    // lLogs::logPrintWindowsClear("sdfsdf", 1);

		
		

		glUniformMatrix4fv_m(matrixRectDraw, 1, GLFALSE, &matrixButton[0][0]);
		checkErrorLos(5);
		glUniform3fvm(colorUniformMatrixDraw, 1, sdf);
		checkErrorLos(51);
		glUniform2fm(thinkNess, 0.1f, 0.1f);
		checkErrorLos(4);	
		glUniform2fm(texBorder, 0.1f, 0.7f);
		drawElements(glTrianglesStrip, 4, glUnsignedShort, 0);
		
	}
	checkErrorLos(3);

}