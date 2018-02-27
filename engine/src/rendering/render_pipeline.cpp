#include <awesome/rendering/render_pipeline.h>
#include <awesome/rendering/components/rendering_component.h>
#include <awesome/scenegraph/scene_reader.h>

namespace Awesome
{
	namespace Rendering
	{
		/*
			TOOD:
			- add occlusion culling 
		*/		

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
			auto it = new SceneReader(scene);
			auto object = it->next();
			while (object != nullptr)
			{
				object->init();
				object = it->next();
			}
		}

		void RenderPipeline::update(float delta_time)
		{
			render_queue.clear();
			auto it = new SceneReader(scene);
			auto object = it->next();
			while (it->end() == false)
			{
				/* check if the object is active */
				if (object->isActive() == false)
					continue;

				/* update */
				object->update(delta_time);
				/* check for rendering components and push them into the render queue */
				auto rendering_component = object->findComponent<RenderingComponent>();
				if (rendering_component != nullptr)
					render_queue.push_back(rendering_component);

				object = it->next();
			}
		}

		void RenderPipeline::render()
		{
			for (auto render_item : render_queue)
			{
				/* TODO: error */
				if (render_item == nullptr)
					continue;

				auto owner = render_item->owner();
				/* check if the object is still active */
				if (owner->isActive() == false)
					continue;

				render_item->render();
			}
		}

		/* change the scene that should be rendered */
		void RenderPipeline::renderScene(Scene* new_scene)
		{
			scene = new_scene;
		}
	}
}