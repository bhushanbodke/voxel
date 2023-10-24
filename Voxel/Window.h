#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include "Keyboard.h"


class Window
{

public:
	GLFWwindow* window;

public:
	Window()
		:window(nullptr)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	};

	~Window() { glfwTerminate(); }

	bool CreateWindow(short width, short height, std::string title)
	{
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			std::cout << "failed to create window terminating ........." << std::endl;
			return false;
		}
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return true;
	};
	bool PollEvents()
	{
		glfwPollEvents();
		return true;
	};
	bool ShouldClose()
	{
		if (keys[GLFW_KEY_ESCAPE])
			return true;
		return glfwWindowShouldClose(window);
	};
	bool Swapbuffer()
	{
		glfwSwapBuffers(window);
		return true;
	}
};



