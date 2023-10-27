#pragma once
#include "GLFW/glfw3.h"


class Mouse
{
public:
	static double x, y;
	static double last_x, last_y;
	static float dx, dy;
	static bool first_time;

public:
	static void curser_keycallback(GLFWwindow* window, double xpos, double ypos);
	static float Get_dx();
	static float Get_dy();
};