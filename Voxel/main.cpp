#include<vector>
#include "glm/glm.hpp"
#include "Window.h"
#include "Cube.h"
#include "Settings.h"
#include "Keyboard.h"
#include "mouse.h"
#include "textures.h"
#include "player.h"
#include "Scene.h"

class VoxelEngine
{
public:
	Window window;
	Scene scene;
	float delta_time;
	float last_frame;
public:
	VoxelEngine()
	{
		window.CreateWindow(Settings::width, Settings::height, "Voxel");
		glfwSetKeyCallback(window.window, Keyboard::key_callback);
		glfwSetCursorPosCallback(window.window, Mouse::curser_keycallback);
		scene.Init();
	}

	void set_deltatime()
	{
		float current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
	}

	bool Run()
	{
		last_frame = glfwGetTime();
		while (!window.ShouldClose())
		{
			set_deltatime();
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClearColor(1.0, 1.0, 1.0, 1.0);
			scene.render(delta_time);
			window.PollEvents();
			window.Swapbuffer();
		}
		return true;
	}
};



int main()
{
	VoxelEngine engine;
	engine.Run();
}