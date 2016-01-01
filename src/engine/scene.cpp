//----LOCAL----
#include "scene.h"

//#include "bullet/btBulletDynamicsCommon.h"

namespace Vast
{
	namespace Engine
	{
		Scene::Scene()
		{
			//Constructor
		}
		
		void Scene::initiate()
		{
			this->render_context.initiate();
		}
		
		bool Scene::tick(double fps, glm::ivec2 dimensions)
		{
			bool closed = false;
			
			closed |= this->render_context.render(fps, dimensions);
			
			return closed;
		}
		
		void Scene::close()
		{
			this->render_context.close();
		}
	}
}
