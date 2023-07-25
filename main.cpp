#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram()
{
	// ����˼·�����ȹ���������ɫ������������ɫ���Ĵ�������
	const char* vshaderSource =
		"#version 330 \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

	const char* fshaderSource =
		"#version 330 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

	// ���������յ���ɫ�����ѱ�Ŵ��������
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

	// �Ѵ�������װ���յ���ɫ����
	glShaderSource(vshader, 1, &vshaderSource, NULL);
	glShaderSource(fshader, 1, &fshaderSource, NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);

	// ����һ��������󣬲��������ı�ţ�����˵ID
	GLuint vfProgram = glCreateProgram();
	// �������ɫ�����ص����������
	glAttachShader(vfProgram, vshader);
	glAttachShader(vfProgram, fshader);
	// �����������������GLSL������
	glLinkProgram(vfProgram);

	return vfProgram;

};

void init(GLFWwindow* window)
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
}

int main()
{
	// ��ʼ�� GLFW
	glfwInit();

	// ���� GLFW ��������ʹ���ĸ��汾�� OpenGL
	// ��ʹ�õ��� OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ��֪ GLFW ����ֻ���� Core Profile���������ļ�
	// ��������ֻ�����ִ��ĺ��� Modern Functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����һ�� 800 * 800 �Ĵ��ڣ���ȫ��������Ϊ��Youtube Window��
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeWindow", NULL, NULL);
	// ���񴰿�û�гɹ��򿪵��쳣
	if (window == NULL)
	{
		std::cout << "Not able to create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	// �� window ���뵽�����ģ���context��
	glfwMakeContextCurrent(window);

	// ����GLAD������OpenGL
	gladLoadGL();

	// �����Ӵ��ڿ��ӻ�����
	// ���������Ϊ�� x = 0, y = 0 �� x = 800, y = 800
	glViewport(0, 0, 800, 800);

	init(window);

	// �жϴ���ر��������������رջ��������йرգ�������ѭ��
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		// ������������¼�
		glfwPollEvents();
	}

	// �رմ���
	glfwDestroyWindow(window);
	// �ر� GLFW ����
	glfwTerminate();
	return 0;
}

