#include <awesome/rendering/renderer.h>
#include <awesome/scenegraph/scene.h>

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

		}

		void Renderer::update(float delta_time)
		{

		}

		void Renderer::render()
		{

		}
	}
}