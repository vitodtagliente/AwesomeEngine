/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/data/asset.h>
#include <awesome/editor/window.h>
#include <awesome/entity/entity.h>
#include <awesome/graphics/texture_rect.h>

namespace editor
{
	class Inspector : public Window
	{
	public:
		Inspector();

		void render() override;

		REFLECT()

	private:
		void inspect(Entity* const entity);
		void inspect(AssetPtr asset);

		std::string m_filename;
		graphics::TextureRect m_rect;
	};
}