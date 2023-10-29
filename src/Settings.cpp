#include "Settings.h"
namespace Settings
{
	double width = 800.f;
	double height = 600.f;

	float aspect_ratio = width / height;

	float FOV = 45.0f;

	float camera_sensitivity = 0.075f;
	int chunk_size = 32;

	int world_width = 10;
	int world_height = 3;
	extern int world_depth;
	int world_depth = 10;

	int chunk_id = 1;

	int no_voxels = 0;
	int no_chunk = world_width * world_height * world_depth;

};