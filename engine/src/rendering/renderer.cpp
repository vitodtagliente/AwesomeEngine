#include <awesome/rendering/renderer.h>
#include <awesome/scenegraph/scene.h>
#include <awesome/scenegraph/object.h>
#include <awesome/rendering/components/mesh_rendering_component.h>

namespace Awesome
{
	using namespace Scenegraph;

	namespace Rendering
	{
		Renderer* Renderer::singleton = nullptr;

		Renderer* Renderer::instance() {
			if (singleton == nullptr)
				singleton = new Renderer();
			return singleton;
		}

		Renderer::Renderer()
		{

		}
		
		void Renderer::init()
		{
			for (auto object : scene->objects)
			{
				object->init();
			}
		}

		void Renderer::update(float delta_time)
		{
			for (auto object : scene->objects)
			{
				object->update(delta_time);
			}
		}

		void Renderer::render()
		{
			for (auto object : scene->objects)
			{
				auto rendering_component = object->findComponent<MeshRenderingComponent>();
				if (rendering_component != nullptr)
					rendering_component->render();
			}
		}
	}
}