#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glad/glad.h"
#include "Settings.h"
#include "mouse.h"

class Camera
{
public:
	glm::vec3 camera_up;
	glm::vec3 camera_target;
	glm::vec3 default_camera_target;
	glm::vec3 camera_pos;
	glm::vec3 default_camera_pos;
	glm::vec3 camera_dir;
	glm::vec3 camera_x;
	glm::vec3 camera_y;
	float cam_speed;


public:
	Camera()
		:camera_pos({ 0.0,0.0,0.0f }),
		default_camera_pos({0.0,0.0,0.0f}),
		camera_dir({0.0f}),
		camera_x({0.0f}),
		camera_y({0}),
		cam_speed(0)
	{};

	void Init(glm::vec3 pos, float speed)
	{
		cam_speed = speed;
		camera_pos = pos;
		camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
		default_camera_pos = camera_pos;
		default_camera_target = camera_target;
		camera_up = glm::vec3(0.0f,1.0f,0.0f);
		update_pos();
		
	};

	void update_pos()
	{
		camera_dir = glm::normalize(camera_target - camera_pos);
		camera_x = glm::normalize(glm::cross(camera_up, camera_dir));
		camera_y = glm::cross(camera_dir, camera_x);
	}
	void reset_camera()
	{
		camera_pos = default_camera_pos;
		camera_target = default_camera_target;
	}
	glm::mat4 Get_view_mat4()
	{
		return glm::lookAt(camera_pos,camera_pos+camera_target,camera_up);
	};

	glm::mat4 get_projection()
	{
		return glm::perspective(glm::radians(Settings::FOV), Settings::aspect_ratio, 0.1f, 1000.0f);
	}
	void MoveForword(float deltatime)
	{
		camera_pos += camera_target * cam_speed * deltatime;
	}
	void MoveBackword(float deltatime)
	{
		camera_pos -= camera_target * cam_speed * deltatime;
	}
	void MoveRight(float deltatime)
	{
		camera_pos += glm::normalize(glm::cross(camera_target, camera_up)) * cam_speed * deltatime;
	}
	void MoveLeft(float deltatime)
	{
		camera_pos -= glm::normalize(glm::cross(camera_target, camera_up)) * cam_speed * deltatime;
	}
	void MoveUp(float deltatime)
	{
		camera_pos += camera_y * cam_speed * deltatime;
	}
	void MoveDown(float deltatime)
	{
		camera_pos -= camera_y * cam_speed * deltatime;
	};

	void update_camera_dir()
	{
		float dx = Mouse::Get_dx();
		float dy = Mouse::Get_dy();
		camera_target = glm::mat3(glm::rotate(glm::radians(dx) * Settings::camera_sensitivity, camera_up)) * camera_target;
		camera_target = glm::mat3(glm::rotate(glm::radians(-dy) * Settings::camera_sensitivity, glm::cross(camera_up, camera_dir))) * camera_target;
		
	}

};