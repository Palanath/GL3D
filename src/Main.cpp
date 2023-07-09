/*
 * Main.cpp
 *
 *  Created on: Jul 8, 2023
 *      Author: Palanath
 */

#include <iostream>
#include "Utils.h"

void glfwWindowResizeCallback(GLFWwindow *win, int, int) {
	int w, h;
	glfwGetFramebufferSize(win, &w, &h);
	if (w > h)
		glViewport((w - h) / 2, 0, h, h);
	else
		glViewport(0, (h - w) / 2, w, w);
}

int main() {
	// Initialize
	if (!glfwInit()) {
		std::cerr << "Error initializing GLFW." << std::endl;
		return 0;
	}

	// Make window
	GLFWwindow *wind = glfwCreateWindow(1400, 800, "Game Window", nullptr,
			nullptr);
	if (!wind) {
		std::cerr << "Error initializing GLFW window." << std::endl;
		return 0;
	}
	glfwMakeContextCurrent(wind);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init GLEW." << std::endl;
		return 0;
	}
	glfwSetWindowSizeCallback(wind, glfwWindowResizeCallback);
	gl3d::utils::setupGLDebugging();

	// Initialize viewport to desired square shape:
	glfwWindowResizeCallback(wind, 0, 0);

	while (!glfwWindowShouldClose(wind)) {
		glfwPollEvents();

		// Rendering goes here.

		glfwSwapBuffers(wind);
	}
}

