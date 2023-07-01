#include <iostream>
#include <string>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Window"

void glfwErrorCallback(int err, const char *desc) {
	std::cerr << "GLFW Error (" << err << "): " << desc;
}

int main() {
	// Launch GLFW and create a window
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
	glfwSetErrorCallback(glfwErrorCallback);
	glfwMakeContextCurrent(wind);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return 0;
	}

	// OpenGL - General Setup
	int width, height;
	glfwGetFramebufferSize(wind, &width, &height);
	glViewport(0, 0, width, height);

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
	const char* src[1] = {R"(#version 330 core
layout(location = 0) in vec3 pos;

out vec3 position;

void main() {
	position = pos;
})"};
	glShaderSource(vertShader, 1, src, nullptr);
	glCompileShader(vertShader);

	src[0] = R"(#version 330 core
in vec3 position;

out vec4 color;

void main() {
	color = vec4(1, 0, 0, 1);
})";
	glShaderSource(fragShader, 1, src, nullptr);
	glCompileShader(fragShader);

	GLuint shader = glCreateProgram();
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	glUseProgram(shader);

	// Render loop
	while (!glfwWindowShouldClose(wind)) {
		glfwPollEvents();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(object) / sizeof(float) / 3);
		glfwSwapBuffers(wind);
	}

	// Cleanup & Termination
	glfwDestroyWindow(wind);
	glfwTerminate();

	return 0;
}
