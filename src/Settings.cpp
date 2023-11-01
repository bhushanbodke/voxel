#include "Settings.h"
namespace Settings
{
	double width = 1280.f;
	double height = 800.f;

	float aspect_ratio = width / height;

	float FOV = 45.0f;

	float camera_sensitivity = 0.075f;
	int chunk_size = 2;

	int chunk_vol = chunk_size * chunk_size * chunk_size;

	int world_width = 1;
	int world_height = 1;
	int world_depth = 1;

	int chunk_id = 1;

	int no_voxels = 0;
	int no_chunk = world_width * world_height * world_depth;

};