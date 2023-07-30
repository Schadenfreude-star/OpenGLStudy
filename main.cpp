#include "Debugger.h"
#include <fstream>
#include <string>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

// 读取目标文本文件的函数，返回string类型的内容
string readShaderSource(const char* filePath)
{
	// 定义一个存储结果的变量content
	string content;
	// 定义一个ifstream类型的变量fileStream
	ifstream fileStream(filePath, ios::in);
	// 用于循环中临时存储行
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint createShaderProgram()
{
	// 大致思路是首先构造两个着色器，下面是着色器的代码设置
	// 读取glsl文件
	string vertShaderStr = readShaderSource("vertShader.glsl");
	string fragShaderStr = readShaderSource("fragShader.glsl");

	// 字符串化
	const char* vshaderSource = vertShaderStr.c_str();
	const char* fshaderSource = fragShaderStr.c_str();

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
	// 将两个已编译着色器的程序载入OpenGL的管线阶段
	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	// 绘制图形
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int renderRedBlueVertex()
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		// 监听键盘鼠标事件
		glfwPollEvents();
	}

	// 关闭窗体
	glfwDestroyWindow(window);
	// 关闭 GLFW 服务
	glfwTerminate();
}

int main()
{
	int renderState = renderRedBlueVertex();
	std::cout << renderState << std::endl;
	return 0;
}
