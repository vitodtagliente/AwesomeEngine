/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <awesome/data/asset.h>
#include <awesome/data/asset_library.h>
#include <awesome/data/base_asset.h>
#include <awesome/data/image_asset.h>
#include <awesome/data/sprite_animation_asset.h>
#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

namespace editor
{
	class Layout
	{
	private:
		Layout() = default;

	public:

		static void begin(const std::string& name);
		static bool beginCombo(const std::string& name, const std::string& value);
		static void beginContext(const std::string context);
		static bool button(const std::string& name);
		static bool button(const std::string& name, int width, int height);
		static bool collapsingHeader(const std::string& name);
		static void end();
		static void endCombo();
		static void endContext();
		static void image(const ImageAssetPtr& image);
		static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect);
		static void input(const std::string& name, int& value);
		static void input(const std::string& name, bool& value);
		static void input(const std::string& name, float& value);
		static void input(const std::string& name, double& value);
		static void input(const std::string& name, std::string& value, size_t size);
		static void input(const std::string& name, vec2& value);
		static void input(const std::string& name, vec3& value);
		static void input(const std::string& name, graphics::Color& value);
		static void input(const std::string& name, graphics::TextureCoords& value);
		static void input(const std::string& name, graphics::TextureRect& value);
		static void input(const std::string& name, SpriteAnimation::Frame& value);
		template <Asset::Type T, typename D>
		static void input(const std::string& name, std::shared_ptr<BaseAsset<T, D>>& value)
		{
			if (Layout::beginCombo(name.c_str(), value ? value->filename.stem().string() : ""))
			{
				const auto assets = AssetLibrary::instance()->list(T);
				for (const Asset& asset : assets)
				{
					if (Layout::selectable(asset.filename.stem().string(), value ? value->id == asset.id : false))
					{
						value = AssetLibrary::instance()->find<BaseAsset<T, D>>(asset.id);
						Layout::endCombo();
						return;
					}

				}
				Layout::endCombo();
			}
		}
		template <typename T>
		static void input(const std::string& name, std::vector<T>& list, const std::function<void(T&)>& handler)
		{
			for (size_t i = 0; i < list.size(); ++i)
			{
				const std::string context = name + "[" + std::to_string(i) + "]";
				beginContext(context);
				if (collapsingHeader(context))
				{
					handler(list.at(i));
					if (button("-"))
					{
						list.erase(list.begin() + i);
						return;
					}
				}
				endContext();
			}
			separator();
			{
				if (button("+"))
				{
					list.push_back(T());
				}
				sameLine();
				if (button("X"))
				{
					list.clear();
				}
			}
		}
		template <typename T>
		static void input(const std::string& name, std::vector<T>& list)
		{
			input<T>(name, list, [](T& element) -> void {
				input("Value", element);
				});
		}
		static void newLine();
		static void sameLine();
		static bool selectable(const std::string& name, bool selected);
		static void separator();
		static void scroll(float position);
		static void scrollToBottom();
		static void text(const std::string& str);
		static void textWrapped(const std::string& str);
		static void title(const std::string& title);

	private:

		static std::string id(const std::string& label);

		static std::string s_context;
	};
}