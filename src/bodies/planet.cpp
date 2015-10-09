//----LIBRARY----
#include "libvolume/engine/realm.h"
#include "libvolume/common/io.h"
#include "libvolume/generation/perlin.h"

//----LOCAL----
#include "planet.h"

namespace Vast
{
	namespace Bodies
	{
        Planet::Planet()
        {
        	const glm::vec3 parts[20 * 3] =
        	{
        		{0.000000, -1.000000, 0.000000}, {0.723600, -0.447215, 0.525720}, {-0.276385, -0.447215, 0.850640},
				{0.723600, -0.447215, 0.525720}, {0.000000, -1.000000, 0.000000}, {0.723600, -0.447215, -0.525720},
				{0.000000, -1.000000, 0.000000}, {-0.276385, -0.447215, 0.850640}, {-0.894425, -0.447215, 0.000000},
				{0.000000, -1.000000, 0.000000}, {-0.894425, -0.447215, 0.000000}, {-0.276385, -0.447215, -0.850640},
				{0.000000, -1.000000, 0.000000}, {-0.276385, -0.447215, -0.850640}, {0.723600, -0.447215, -0.525720},
				{0.723600, -0.447215, 0.525720}, {0.723600, -0.447215, -0.525720}, {0.894425, 0.447215, 0.000000},
				{-0.276385, -0.447215, 0.850640}, {0.723600, -0.447215, 0.525720}, {0.276385, 0.447215, 0.850640},
				{-0.894425, -0.447215, 0.000000}, {-0.276385, -0.447215, 0.850640}, {-0.723600, 0.447215, 0.525720},
				{-0.276385, -0.447215, -0.850640}, {-0.894425, -0.447215, 0.000000}, {-0.723600, 0.447215, -0.525720},
				{0.723600, -0.447215, -0.525720}, {-0.276385, -0.447215, -0.850640}, {0.276385, 0.447215, -0.850640},
				{0.723600, -0.447215, 0.525720}, {0.894425, 0.447215, 0.000000}, {0.276385, 0.447215, 0.850640},
				{-0.276385, -0.447215, 0.850640}, {0.276385, 0.447215, 0.850640}, {-0.723600, 0.447215, 0.525720},
				{-0.894425, -0.447215, 0.000000}, {-0.723600, 0.447215, 0.525720}, {-0.723600, 0.447215, -0.525720},
				{-0.276385, -0.447215, -0.850640}, {-0.723600, 0.447215, -0.525720}, {0.276385, 0.447215, -0.850640},
				{0.723600, -0.447215, -0.525720}, {0.276385, 0.447215, -0.850640}, {0.894425, 0.447215, 0.000000},
				{0.276385, 0.447215, 0.850640}, {0.894425, 0.447215, 0.000000}, {0.000000, 1.000000, 0.000000},
				{-0.723600, 0.447215, 0.525720}, {0.276385, 0.447215, 0.850640}, {0.000000, 1.000000, 0.000000},
				{-0.723600, 0.447215, -0.525720}, {-0.723600, 0.447215, 0.525720}, {0.000000, 1.000000, 0.000000},
				{0.276385, 0.447215, -0.850640}, {-0.723600, 0.447215, -0.525720}, {0.000000, 1.000000, 0.000000},
				{0.894425, 0.447215, 0.000000}, {0.276385, 0.447215, -0.850640}, {0.000000, 1.000000, 0.000000},
        	};

        	for (int c = 0; c < 20; c ++)
			{
				this->parts[c].poly.a.position = parts[c * 3 + 0] * 10.0f;
				this->parts[c].poly.b.position = parts[c * 3 + 1] * 10.0f;
				this->parts[c].poly.c.position = parts[c * 3 + 2] * 10.0f;
				this->parts[c].owner = this;

				this->parts[c].poly.a.normal = glm::normalize(this->parts[c].poly.a.position);
				this->parts[c].poly.b.normal = glm::normalize(this->parts[c].poly.b.position);
				this->parts[c].poly.c.normal = glm::normalize(this->parts[c].poly.c.position);

				//this->parts[c].poly.correctNormals();
			}
        }

        void Planet::tick()
        {
        	LibVolume::Engine::Actor::tick();

			this->state.update();
        	glm::f64mat4 inv = glm::inverse(this->state.matrix * this->mesh_state.matrix);

        	bool should_remesh = false;

			for (int c = 0; c < 20; c ++)
			{
				should_remesh |= this->parts[c].update((glm::vec3)(inv * glm::f64vec4(this->parent->camera.state.position, 1.0)));
			}

			if (should_remesh)
			{
				this->mesh->clear();

				for (int c = 0; c < 20; c ++)
				{
					this->makeMesh(&this->mesh->polygons, &this->parts[c]);
				}
			}
        }

        void Planet::makeMesh(std::vector<LibVolume::Render::Structures::Polygon>* poly_vector, TerrainPart* part)
        {
        	if (!part->has_split)
				poly_vector->push_back(part->poly);

			if (part->has_split)
			{
				this->makeMesh(poly_vector, part->child[0]);
				this->makeMesh(poly_vector, part->child[1]);
				this->makeMesh(poly_vector, part->child[2]);
				this->makeMesh(poly_vector, part->child[3]);
			}
        }

        bool TerrainPart::split()
        {
        	if (!this->has_split && this->owner->max_depth > this->depth)
			{
				this->has_split = true;

				for (int c = 0; c < 4; c ++)
				{
					this->child[c] = new TerrainPart();
					this->child[c]->poly = this->poly;
					this->child[c]->depth = this->depth + 1;
					this->child[c]->parent = this;
					this->child[c]->owner = this->owner;
				}


				this->child[0]->poly.a.position = (this->poly.a.position + this->poly.a.position) / 2.0f;
				this->child[0]->poly.b.position = (this->poly.a.position + this->poly.b.position) / 2.0f;
				this->child[0]->poly.c.position = (this->poly.a.position + this->poly.c.position) / 2.0f;

				this->child[1]->poly.a.position = (this->poly.a.position + this->poly.b.position) / 2.0f;
				this->child[1]->poly.b.position = (this->poly.b.position + this->poly.b.position) / 2.0f;
				this->child[1]->poly.c.position = (this->poly.b.position + this->poly.c.position) / 2.0f;

				this->child[2]->poly.a.position = (this->poly.a.position + this->poly.c.position) / 2.0f;
				this->child[2]->poly.b.position = (this->poly.b.position + this->poly.c.position) / 2.0f;
				this->child[2]->poly.c.position = (this->poly.c.position + this->poly.c.position) / 2.0f;

				this->child[3]->poly.a.position = (this->poly.a.position + this->poly.b.position) / 2.0f;
				this->child[3]->poly.b.position = (this->poly.b.position + this->poly.c.position) / 2.0f;
				this->child[3]->poly.c.position = (this->poly.a.position + this->poly.c.position) / 2.0f;

				for (int c = 0; c < 4; c ++)
				{
					this->child[c]->poly.a.position = glm::normalize(this->child[c]->poly.a.position);
					this->child[c]->poly.b.position = glm::normalize(this->child[c]->poly.b.position);
					this->child[c]->poly.c.position = glm::normalize(this->child[c]->poly.c.position);

					LibVolume::Generation::PerlinNoise noise;
					this->child[c]->poly.a.position *= 10.0 + 0.1 * noise.getPerlin(glm::vec4(this->child[c]->poly.a.position, 7.0) * 16.0f, 0.5, 6.0, 3.0);
					this->child[c]->poly.b.position *= 10.0 + 0.1 * noise.getPerlin(glm::vec4(this->child[c]->poly.b.position, 7.0) * 16.0f, 0.5, 6.0, 3.0);
					this->child[c]->poly.c.position *= 10.0 + 0.1 * noise.getPerlin(glm::vec4(this->child[c]->poly.c.position, 7.0) * 16.0f, 0.5, 6.0, 3.0);

					this->child[c]->poly.correctNormals();

					glm::vec3 v = this->child[c]->poly.a.normal;

					this->child[c]->poly.a.normal = glm::normalize(this->child[c]->poly.a.position);
					this->child[c]->poly.b.normal = glm::normalize(this->child[c]->poly.b.position);
					this->child[c]->poly.c.normal = glm::normalize(this->child[c]->poly.c.position);

					glm::vec3 avg = (this->child[c]->poly.a.normal + this->child[c]->poly.b.normal + this->child[c]->poly.c.normal) / 3.0f;

					/*if (glm::dot(avg, va) < 0.8)
						this->child[c]->poly.a.normal = va;

					if (glm::dot(avg, vb) < 0.8)
						this->child[c]->poly.b.normal = vb;

					if (glm::dot(avg, vc) < 0.8)
						this->child[c]->poly.c.normal = vc;*/

					this->child[c]->poly.a.normal = glm::mix(v, this->child[c]->poly.a.normal, glm::pow(glm::dot(avg, v) - 0.8f, 1.0));
					this->child[c]->poly.b.normal = glm::mix(v, this->child[c]->poly.b.normal, glm::pow(glm::dot(avg, v) - 0.8f, 1.0));
					this->child[c]->poly.c.normal = glm::mix(v, this->child[c]->poly.c.normal, glm::pow(glm::dot(avg, v) - 0.8f, 1.0));
				}

				return true;
			}

			return false;
        }

        bool TerrainPart::join()
        {
        	if (this->has_split)
			{
				this->has_split = false;

				for (int c = 0; c < 4; c ++)
				{
					delete this->child[c];
					this->child[c] = nullptr;
				}

				return true;
			}

			return false;
        }

        bool TerrainPart::update(glm::vec3 camera_pos)
        {
        	bool result = false;

        	glm::vec3 average = (this->poly.a.position + this->poly.b.position + this->poly.c.position) / 3.0f;

        	if ((glm::length(average - camera_pos) - 0.1f) * glm::pow(2.0, (float)this->depth) < 10.0f * 10.0f)
				result |= this->split();
			else
				result |= this->join();

        	if (this->has_split)
			{
				for (int c = 0; c < 4; c ++)
				{
					result |= this->child[c]->update(camera_pos);
				}
			}

			return result;
        }
	}
}
