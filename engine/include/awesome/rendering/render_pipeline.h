#pragma once 

#include "../scenegraph/scene.h"

using namespace Awesome::Scenegraph;

namespace Awesome
{
	namespace Rendering
	{
		class RenderPipeline
		{
		private:
			Scene* scene{ nullptr };
		
		protected:
			RenderPipeline();
			~RenderPipeline();
		};
	}
}