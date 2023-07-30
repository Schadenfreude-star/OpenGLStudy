#include "Debugger.h"
#include <fstream>
#include <string>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

// ��ȡĿ���ı��ļ��ĺ���������string���͵�����
string readShaderSource(const char* filePath)
{
	// ����һ���洢����ı���content
	string content;
	// ����һ��ifstream���͵ı���fileStream
	ifstream fileStream(filePath, ios::in);
	// ����ѭ������ʱ�洢��
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
	// ����˼·�����ȹ���������ɫ������������ɫ���Ĵ�������
	// ��ȡglsl�ļ�
	string vertShaderStr = readShaderSource("vertShader.glsl");
	string fragShaderStr = readShaderSource("fragShader.glsl");

	// �ַ�����
	const char* vshaderSource = vertShaderStr.c_str();
	const char* fshaderSource = fragShaderStr.c_str();

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
	// �������ѱ�����ɫ���ĳ�������OpenGL�Ĺ��߽׶�
	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	// ����ͼ��
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int renderRedBlueVertex()
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		// ������������¼�
		glfwPollEvents();
	}

	// �رմ���
	glfwDestroyWindow(window);
	// �ر� GLFW ����
	glfwTerminate();
}

int main()
{
	int renderState = renderRedBlueVertex();
	std::cout << renderState << std::endl;
	return 0;
}
