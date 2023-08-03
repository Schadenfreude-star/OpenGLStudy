#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>

class Utils
{
private:
	static std::string readShaderFile(const char* filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static GLuint prepareShader(int shaderTYPE, const char* shaderPath);
	static int finalizeShaderProgram(GLuint sprogram);
public:
	Utils();
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char* cp);
	static GLuint createShaderProgram(const char* vp, const char* fp);
};
