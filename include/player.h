#pragma once 
#include "camera.h"
#include "mouse.h"
#include "Keyboard.h"
#include "Window.h"

class Player : public Camera
{
public:
	Player():Camera()
	{};
	void movement(float delta_time)
	{
		update_camera_dir();
		if (keys[GLFW_KEY_LEFT_SHIFT])
			cam_speed = 50;
		else
			cam_speed = 5;

		if (keys[GLFW_KEY_S])
			MoveBackword(delta_time);
		if (keys[GLFW_KEY_W])
			MoveForword(delta_time);
		if (keys[GLFW_KEY_A])
			MoveLeft(delta_time);
		if (keys[GLFW_KEY_D])
			MoveRight(delta_time);
		if (keys[GLFW_KEY_LEFT_CONTROL])
			MoveDown(delta_time);
		if (keys[GLFW_KEY_SPACE])
			MoveUp(delta_time);
		if (keys[GLFW_KEY_C])
			reset_camera();
		
	}

	void update(float delta_time)
	{
		movement(delta_time);
	}
};