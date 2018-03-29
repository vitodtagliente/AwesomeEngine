#pragma once

namespace Awesome
{
	class EngineModule
	{
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
	};
}