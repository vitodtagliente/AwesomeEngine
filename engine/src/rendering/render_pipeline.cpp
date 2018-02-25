#include <awesome/rendering/render_pipeline.h>
#include <awesome/rendering/components/rendering_component.h>

namespace Awesome
{
	namespace Rendering
	{
		RenderPipeline::RenderPipeline()
		{

		}

		RenderPipeline::RenderPipeline(Scene* new_scene)
		{
			renderScene(new_scene);
		}

		RenderPipeline::~RenderPipeline()
		{

		}

		void RenderPipeline::init()
		{
			for (auto object : scene->objects)
			{
				object->init();
			}
		}

		void RenderPipeline::update(float delta_time)
		{
			for (auto object : scene->objects)
			{
				object->update(delta_time);
			}
		}

		void RenderPipeline::render()
		{
			for (auto object : scene->objects)
			{
				auto rendering_component = object->findComponent<RenderingComponent>();
				if (rendering_component != nullptr)
					rendering_component->render();
			}
		}

		void RenderPipeline::renderScene(Scene* new_scene)
		{
			scene = new_scene;
		}
	}
}