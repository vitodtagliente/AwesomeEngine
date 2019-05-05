#pragma once

#include "../engine/module.h"

namespace awesome
{
	class Graphics : public Module<Graphics>
	{
	public:

		enum class API
		{
			Null,
			OpenGL
		};

	protected:

		// module update
		virtual void update_implementation() override;
	};
}