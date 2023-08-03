#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
using namespace std;

Utils::Utils() {}

void Utils::printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}

void Utils::printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

bool Utils::checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

string Utils::readShaderFile(const char* filePath)
{
	string content;

	ifstream fileStream(filePath, ios::in);
	if (!fileStream.is_open())
	{
		throw "Unable to open file.";
	}
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint Utils::prepareShader(int shaderTYPE, const char* shaderPath)
{
	GLint shaderCompiled;
	string shaderStr = readShaderFile(shaderPath);
	const char* shaderSrc = shaderStr.c_str();
	GLuint shaderRef = glCreateShader(shaderTYPE);

	if (shaderRef == 0 || shaderRef == GL_INVALID_ENUM)
	{
		printf("Error: Could not create shader \"%s\" of type:%d\n", shaderPath, shaderTYPE);
		return 0;
	}

	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	checkOpenGLError();

	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		if (shaderTYPE == GL_VERTEX_SHADER) cout << "Vertex ";
		if (shaderTYPE == GL_TESS_CONTROL_SHADER) cout << "Tess Control ";
		if (shaderTYPE == GL_TESS_EVALUATION_SHADER) cout << "Tess Eval ";
		if (shaderTYPE == GL_GEOMETRY_SHADER) cout << "Geometry ";
		if (shaderTYPE == GL_FRAGMENT_SHADER) cout << "Fragment ";
		if (shaderTYPE == GL_COMPUTE_SHADER) cout << "Compute ";
		cout << "shader compilation error for shader: '" << shaderPath << "'." << endl;
		printShaderLog(shaderRef);
	}


	//====================================
	// Custom Compilation Error Checking
	//====================================
	//checkOpenGLError();
	/*GLint compiled;
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE)
	{
		printf("Error: Failed to compile shader \"%s\".\n", shaderPath);

		GLint log_size = 0;
		glGetShaderiv(shaderRef, GL_INFO_LOG_LENGTH, &log_size);

		printf("Shader log length: %d\n", log_size);

		GLchar* info_log = (GLchar*)malloc(sizeof(GLchar)*log_size);
		glGetShaderInfoLog(shaderRef, log_size, &log_size, info_log);
		printf("Compilation Log: '%s'\n", info_log);
		printf("First 5 chars: %d %d %d %d %d\n", info_log[0], info_log[1], info_log[2], info_log[3], info_log[4]);
		free(info_log);
		glDeleteShader(shaderRef);
		return 0;

	}*/
	//====================================
	return shaderRef;
}

int Utils::finalizeShaderProgram(GLuint sprogram)
{
	GLint linked;
	glLinkProgram(sprogram);
	checkOpenGLError();
	glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "linking failed" << endl;
		printProgramLog(sprogram);
	}
	return sprogram;
}

GLuint Utils::createShaderProgram(const char* vp, const char* fp)
{
	GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
	GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
	GLuint vfprogram = glCreateProgram();
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}
