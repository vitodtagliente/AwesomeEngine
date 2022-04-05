/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
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
		static void image(const ImageAssetPtr& image, float width, float height);
		static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect);
		static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect, float width, float height);
		static void input(const std::string& name, int& value);
		static void input(const std::string& name, bool& value);
		static void input(const std::string& name, float& value);
		static void input(const std::string& name, double& value);
		static void input(const std::string& name, std::string& value);
		static void input(const std::string& name, vec2& value);
		static void input(const std::string& name, vec3& value);
		static void input(const std::string& name, graphics::Color& value);
		static void input(const std::string& name, graphics::TextureCoords& value);
		static void input(const std::string& name, graphics::TextureRect& value);
		static void input(const std::string& name, SpriteAnimation::Frame& value);
		// usable for displaying enums
		template <typename T>
		static void input(const std::string& name, T& value, const std::map<std::string, T>& values)
		{
			const auto& it = std::find_if(values.begin(), values.end(), [&value](const auto& pair) {
				return pair.second == value;
				});

			if (Layout::beginCombo(name.c_str(), it != values.end() ? it->first.c_str() : ""))
			{
				for (const auto& pair : values)
				{
					if (Layout::selectable(pair.first.c_str(), value == pair.second))
					{
						value = pair.second;
						Layout::endCombo();
						return;
					}

				}
				Layout::endCombo();
			}
		}
		// assets support
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
		// std::vector<T> support
		template <typename T>
		static void input(const std::string& name, std::vector<T>& list, const std::function<void(T&)>& handler)
		{
			text(name);
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
			if (button("+"))
			{
				list.push_back(T());
			}
			if (!list.empty())
			{
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
		// std::map<K,T> support
		template <typename K, typename T>
		static void input(const std::string& name, std::map<K, T>& map, const std::function<std::string(const K&)>& toKey, const std::function<void(T&)>& handler)
		{
			text(name);
			for (auto& pair : map)
			{
				const std::string context = name + "[" + toKey(pair.first) + "]";
				beginContext(context);
				if (collapsingHeader(context))
				{
					handler(pair.second);
					if (button("-"))
					{
						map.erase(pair.first);
						return;
					}
				}
				endContext();
			}
			
			K* newKey = nullptr;
			{
				const auto& it = s_keyCache.find(name);
				if (it == s_keyCache.end())
				{
					newKey = new K();
					s_keyCache.insert(std::make_pair(name, newKey));
				}
				else
				{
					newKey = reinterpret_cast<K*>(it->second);
				}
			}

			input("Key", *newKey);
			sameLine();
			if (button("+"))
			{
				map.insert(std::make_pair(*newKey, T()));
				if (typeid(K) == typeid(std::string))
				{
					reinterpret_cast<std::string*>(newKey)->clear();
				}
			}
			if (!map.empty())
			{
				sameLine();
				if (button("X"))
				{
					map.clear();
				}
			}
		}
		template <typename T>
		static void input(const std::string& name, std::map<std::string, T>& map, const std::function<void(T&)>& handler)
		{
			input<std::string, T>(name, map, [](const std::string& key) -> std::string { return key; }, handler);
		}
		template <typename K, typename T>
		static void input(const std::string& name, std::map<std::string, T>& map, const std::function<std::string(const K&)>& toKey)
		{
			input<T>(name, map, toKey, [](T& value) -> void {
				input("Value", value);
				});
		}
		template <typename T>
		static void input(const std::string& name, std::map<std::string, T>& map)
		{
			input<T>(name, map, [](T& value) -> void {
				input("Value", value);
				});
		}
		static void newLine();
		static void sameLine();
		static bool selectable(const std::string& name, bool selected);
		static void separator();
		static void scroll(float position);
		static void scrollToBottom();
		static void slider(const std::string& name, int min, int max, int& value);
		static void slider(const std::string& name, float min, float max, float& value);
		static void text(const std::string& str);
		static void textWrapped(const std::string& str);
		static void title(const std::string& title);

		static void clear();

	private:

		static std::string id(const std::string& label);

		static std::string s_context;
		static std::map<std::string, void*> s_keyCache;
	};
}