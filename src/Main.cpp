#include <iostream>
#include <string>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Window"

void glfwErrorCallback(int err, const char *desc) {
	std::cerr << "GLFW Error (" << err << "): " << desc;
}

void printGLErrors() {
	for (auto x = glGetError(); x != GL_NO_ERROR; x = glGetError())
		std::cout << "Error: " << x << std::endl;
}

void glfwWindowResizeCallback(GLFWwindow *win, int, int) {
	int w, h;
	glfwGetFramebufferSize(win, &w, &h);
	if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);
}

int main() {
	// Launch GLFW and create a window
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		std::cerr << "Error initializing GLFW." << std::endl;
		return 0;
	}

	GLFWwindow *wind = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
	WINDOW_TITLE, nullptr, nullptr);
	if (!wind) {
		std::cerr << "Error creating window." << std::endl;
		return 0;
	}

	// Setup window
	glfwMakeContextCurrent(wind);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return 0;
	}
	glfwSetWindowSizeCallback(wind, glfwWindowResizeCallback);

	// OpenGL - General Setup
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// OpenGL - Shader Input Setup
	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	float object[] = {
				-.5, .5, 0,
				-.5, .5, 1,
				.5, .5, 0,

				.5, .5, 0,
				-.5, .5, 1,
				.5, .5, 1,

				-.5, .5, 0,
				0, -.5, .5,
				.5, .5, 0,

				-.5, .5, 1,
				0, -.5, .5,
				-.5, .5, 0,

				.5, .5, 1,
				0, -.5, .5,
				-.5, .5, 1,
		};
	glBufferData(GL_ARRAY_BUFFER, sizeof object, object, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(0);

	// OpenGL - Shader Setup
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER), fragShader =
	glCreateShader(GL_FRAGMENT_SHADER);
	const char *src[1] =
			{
					R"(#version 330 core
layout(location = 0) in vec3 pos;

out vec3 position;

void main() {
	gl_Position = vec4(position = pos, 1);
})" };
	glShaderSource(vertShader, 1, src, nullptr);
	glCompileShader(vertShader);

	src[0] =
			R"(#version 330 core
uniform float curtime;

in vec3 position;

out vec4 color;

void main() {
	color = vec4(1, curtime / 25, 0, 1);
})";
	glShaderSource(fragShader, 1, src, nullptr);
	glCompileShader(fragShader);

	GLuint shader = glCreateProgram();
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	glUseProgram(shader);

	GLuint curtimeUniform = glGetUniformLocation(shader, "curtime");

	// Render loop
	double curtime = glfwGetTime();
	while (!glfwWindowShouldClose(wind)) {
		glfwPollEvents();
		glUniform1f(curtimeUniform, glfwGetTime() - curtime);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(object) / sizeof(float) / 3);
		printGLErrors();
		glfwSwapBuffers(wind);
	}

	// Cleanup & Termination
	glfwDestroyWindow(wind);
	glfwTerminate();

	return 0;
}
