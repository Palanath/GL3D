/*
 * Main.cpp
 *
 *  Created on: Jul 8, 2023
 *      Author: Palanath
 */

#include <iostream>
#include "Utils.h"

void glfwKeyCallback(GLFWwindow *wind, int key, int scancode, int action,
		int mods) {
	std::cout << "KEY: " << glfwGetKeyName(key, scancode) << " was pressed"
			<< std::endl << "\tMods: " << std::hex << mods << std::endl
			<< "\tAction: " << action << std::dec << std::endl;
}

void glfwCursorPositionCallback(GLFWwindow *wind, double x, double y) {
	std::cout << "MOUSE POS: (" << x << ", " << y << ")" << std::endl;
}

void glfwMouseButtonCallback(GLFWwindow *wind, int button, int action,
		int mods) {
	std::cout << "MOUSE PRESS: button=" << button << ", action=" << action
			<< ", mods=" << mods << std::endl;
}

void glfwScrollCallback(GLFWwindow *wind, double x, double y) {
	std::cout << "SCROLL: x=" << x << ", y=" << y << std::endl;
}

void glfwJoystickConfigurationCallback(int joystickID, int event) {
	if (event == GLFW_CONNECTED)
		std::cout << "JOYSTICK " << joystickID << " CONNECTED";
	else if (event == GLFW_DISCONNECTED)
		std::cout << "JOYSTICK " << joystickID << " DISCONNECTED";
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

	// Input Callbacks
	glfwSetKeyCallback(wind, glfwKeyCallback);
	glfwSetCursorPosCallback(wind, glfwCursorPositionCallback);
	glfwSetMouseButtonCallback(wind, glfwMouseButtonCallback);
	glfwSetScrollCallback(wind, glfwScrollCallback);
	glfwSetJoystickCallback(glfwJoystickConfigurationCallback);

	while (!glfwWindowShouldClose(wind)) {
		glfwPollEvents();

		// Rendering goes here.

		glfwSwapBuffers(wind);
	}
}

