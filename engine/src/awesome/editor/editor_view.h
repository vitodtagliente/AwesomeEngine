#pragma once 

namespace awesome
{
	class EditorView
	{
	public:

		virtual void init() {}
		virtual void render() {}
		virtual void uninit() {}

		bool visible{ true };
	};
}