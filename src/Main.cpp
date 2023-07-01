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

	// Render loop
	while (!glfwWindowShouldClose(wind))
		glfwPollEvents();

	// Cleanup & Termination
	glfwDestroyWindow(wind);
	glfwTerminate();

	return 0;
}
