#pragma once

namespace Awesome
{
	class EngineModule
	{
	public:
		virtual void init() = 0;
		virtual void update(float delta_time) = 0;
		virtual void render() = 0;
		virtual void free() = 0;
	};
}