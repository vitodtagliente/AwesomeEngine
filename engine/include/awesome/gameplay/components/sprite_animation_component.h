#pragma once

#include "../../scenegraph/component.h"
#include "../../math/rect.h"

namespace Awesome
{
	namespace Gameplay
	{
		struct SpriteAnimationData
		{

		};

		struct SpriteAnimation
		{

		};

		class SpriteAnimationComponent : public Scenegraph::Component
		{
		public:
			void init() override;
			void update(float delta_time) override;
		};
	}
}