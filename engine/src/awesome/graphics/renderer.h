#pragma once

#include "../core/singleton.h"

namespace awesome
{
	struct Color;

	class Renderer : public Singleton<Renderer>
	{
	public:

		friend class Engine;

		void clear(const Color& t_color);

	private:
		
		Renderer();
		~Renderer();

		void init();
		void uninit();
		
	};
}