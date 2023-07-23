#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f,
	};

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// ���ñ�����ɫ
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// ����������沢��������ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	// ��
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
