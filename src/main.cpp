//----STANDARD----
#include "stdio.h"

//----LIBRARY----
#include "libvolume/window/window.h"
#include "libvolume/engine/realm.h"
#include "libvolume/engine/voxelactor.h"

//----LOCAL----
#include "bodies/planet.h"

int main(int argc, char* argv[])
{
	LibVolume::Window::Window window;
	window.setTitle("Vast");

	LibVolume::Engine::Realm realm;
	realm.linkTo(window);

	LibVolume::Render::Structures::Light sun(LibVolume::Render::Structures::LightType::Directional, glm::vec3(0.5, 0.5, -1.0), glm::vec3(3.0, 3.0, 2.9), 0.03);
	realm.addLight(sun);

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

				asteroid.getAt(glm::ivec3(x + 8, y + 8, z + 8))->density = (1.0) * (8.0 - std::sqrt(x * x + y * y + z * z));
			}
		}
	}

	float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float c = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	asteroid.state.spin = glm::quat(glm::vec3(2.0 * a - 1.0, 2.0 * b - 1.0, 2.0 * c - 1.0) * 0.01f);

	asteroid.extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
	//realm.addObject(asteroid);

	Vast::Bodies::Planet planet;
	planet.state.scale = glm::vec3(80.0, 80.0, 80.0);
	planet.state.position = glm::vec3(8000.0, 0.0, -810.0);
	planet.mesh->colour = glm::vec3(0.5, 0.4, 0.2);
	planet.state.orientation = glm::quat(glm::vec3(2.0 * a - 1.0, 2.0 * b - 1.0, 2.0 * c - 1.0) * 1.0f);
	realm.addObject(planet);



	while (window.tick() == false)
	{
		float dist = (glm::length(planet.state.position - realm.camera.state.position) - 800.0f) * 0.005;
		if (window.event_manager.keyboard_state.key_down)
			realm.camera.state.position += glm::vec3(-3.0, 0.0, 0.0) * dist;
		if (window.event_manager.keyboard_state.key_right)
			realm.camera.state.position += glm::vec3(0.0, -3.0, 0.0) * dist;
		if (window.event_manager.keyboard_state.key_left)
			realm.camera.state.position += glm::vec3(0.0, 3.0, 0.0) * dist;
		if (window.event_manager.keyboard_state.key_up)
			realm.camera.state.position += glm::vec3(3.0, 0.0, 0.0) * dist;
		if (window.event_manager.keyboard_state.key_space)
			realm.camera.state.position += glm::vec3(0.0, 0.0, 3.0) * dist;
		if (window.event_manager.keyboard_state.key_shift)
			realm.camera.state.position += glm::vec3(0.0, 0.0, -3.0) * dist;

		realm.tick();
		realm.render();
	}

	return 0;
}
