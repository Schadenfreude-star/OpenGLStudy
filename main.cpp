#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram()
{
	// 大致思路是首先构造两个着色器，下面是着色器的代码设置
	const char* vshaderSource =
		"#version 330 \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

	const char* fshaderSource =
		"#version 330 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

	// 创建两个空的着色器，把编号存进变量里
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

	// 把代码设置装进空的着色器里
	glShaderSource(vshader, 1, &vshaderSource, NULL);
	glShaderSource(fshader, 1, &fshaderSource, NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);

	// 创建一个程序对象，并存下它的编号，或者说ID
	GLuint vfProgram = glCreateProgram();
	// 下面把着色器加载到程序对象中
	glAttachShader(vfProgram, vshader);
	glAttachShader(vfProgram, fshader);
	// 调用这个函数来请求GLSL编译器
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
	// 初始化 GLFW
	glfwInit();

	// 告诉 GLFW 我们正在使用哪个版本的 OpenGL
	// 我使用的是 OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 告知 GLFW 我们只用了 Core Profile，即核心文件
	// 所以我们只用了现代的函数 Modern Functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	init(window);

	// 判断窗体关闭条件，如果点击关闭或者命令行关闭，就跳出循环
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		// 监听键盘鼠标事件
		glfwPollEvents();
	}

	// 关闭窗体
	glfwDestroyWindow(window);
	// 关闭 GLFW 服务
	glfwTerminate();
	return 0;
}

