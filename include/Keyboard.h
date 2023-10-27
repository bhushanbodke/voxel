#pragma once
#include "GLFW/glfw3.h"

static bool keys[GLFW_KEY_LAST] = { 0 };
static bool keys_changed[GLFW_KEY_LAST] = { 0 };
class Keyboard
{
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		if (action == GLFW_RELEASE)
		{
			if (keys[key])
				keys[key] = false;
		}
		if (action == GLFW_REPEAT)
		{
			keys_changed[key] = false;
		}
	}
};