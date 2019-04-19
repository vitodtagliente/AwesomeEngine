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
		void draw(const unsigned int t_vertices = 3);
		void drawElements(const unsigned int t_vertices);

	private:
		
		Renderer();
		~Renderer();

		void init();
		void uninit();
		
	};
}