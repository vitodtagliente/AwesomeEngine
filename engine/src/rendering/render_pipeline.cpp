#include <awesome/rendering/render_pipeline.h>
#include <awesome/rendering/components/rendering_component.h>
#include <awesome/rendering/sprite_batch.h>
#include <awesome/object_iterator.h>

namespace Awesome
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
		for (ObjectIterator it{ scene }; it.has_next(); ++it)
		{
			(*it).init();
		}
	}

	void RenderPipeline::update(float delta_time)
	{
		// clear the render queue
		render_queue.clear();

		for (ObjectIterator it{ scene }; it.has_next(); ++it)
		{
			// check if the object is active
			if ((*it).isActive() == false)
				continue;

			// update
			(*it).update(delta_time);
			// check for rendering components and push them into the render queue
			auto rendering_component = (*it).findComponent<RenderingComponent>();
			if (rendering_component != nullptr)
				render_queue.push_back(rendering_component);
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

		auto sprite_batch = SpriteBatch::instance();
		if (sprite_batch != nullptr)
			sprite_batch->draw();
	}

	/* change the scene that should be rendered */
	void RenderPipeline::renderScene(Scene* new_scene)
	{
		scene = new_scene;
	}
}