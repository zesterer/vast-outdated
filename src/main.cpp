//----STANDARD----
#include "stdio.h"

//----LIBRARY----
#include "libvolume/window/window.h"
#include "libvolume/engine/realm.h"
#include "libvolume/engine/voxelactor.h"

int main(int argc, char* argv[])
{
	printf("Hello, World!\n");

	LibVolume::Window::Window window;

	LibVolume::Engine::Realm realm;
	realm.setEventManager(&window.event_manager);

	LibVolume::Engine::VoxelActor asteroid(glm::ivec3(16, 16, 16));
	asteroid.state.scale = glm::vec3(200.0, 200.0, 200.0);
	asteroid.state.position = glm::vec3(3000.0, 0.0, 0.0);
	asteroid.mesh_state.position = glm::vec3(-8.0, -8.0, -8.0);
	asteroid.mesh->colour = glm::vec3(0.5, 0.4, 0.2);

	for (int x = -8; x < 8; x ++)
	{
		for (int y = -8; y < 8; y ++)
		{
			for (int z = -8; z < 8; z ++)
			{
				float d = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				asteroid.getAt(glm::ivec3(x + 8, y + 8, z + 8))->density = (0.1 + d) * (8.0 - std::sqrt(x * x + y * y + z * z));
			}
		}
	}

	float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float c = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	asteroid.state.spin = glm::quat(glm::vec3(2.0 * a - 1.0, 2.0 * b - 1.0, 2.0 * c - 1.0) * 0.01f);

	asteroid.extractMarchingCubes();
	realm.objects.push_back(dynamic_cast<LibVolume::Engine::Object*>(&asteroid));

	while (window.tick() == false)
	{
		realm.tick();
		realm.render();
	}

	return 0;
}
