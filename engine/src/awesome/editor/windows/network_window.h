/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/editor/window.h>

namespace editor
{
	class NetworkWindow : public Window, public IProtoClass
	{
	public:
		NetworkWindow() = default;
		virtual ~NetworkWindow() = default;

		std::string getTitle() const override { return "Network"; }
		void render() override;

		PROTO()
	};
}