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
	// 初始化 GLFW
	glfwInit();
	
	// 告诉 GLFW 我们正在使用哪个版本的 OpenGL
	// 我使用的是 OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// 告知 GLFW 我们只用了 Core Profile，即核心文件
	// 所以我们只用了现代的函数 Modern Functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f,
	};

	// 创建一个 800 * 800 的窗口，不全屏，命名为“Youtube Window”
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeWindow", NULL, NULL);
	// 捕获窗口没有成功打开的异常
	if (window == NULL)
	{
		std::cout << "Not able to create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	// 把 window 引入到上下文，即context中
	glfwMakeContextCurrent(window);

	// 加载GLAD来调用OpenGL
	gladLoadGL();

	// 设置视窗内可视化窗口
	// 我这边设置为从 x = 0, y = 0 到 x = 800, y = 800
	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// 设置背景颜色
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// 清除背景缓存并分配新颜色
	glClear(GL_COLOR_BUFFER_BIT);
	// 用
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
