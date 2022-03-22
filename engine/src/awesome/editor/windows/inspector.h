/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/editor/window.h>
#include <awesome/entity/entity.h>

namespace editor
{
	class Context;

	class Inspector : public Window
	{
	public:
		Inspector();

		void render(Context& context) override;

		REFLECT()

	private:
		void inspect(Context& context, Entity* const entity);
		void inspect(Context& context, const std::filesystem::path& file);

		std::string m_prefabFilename;
	};
}