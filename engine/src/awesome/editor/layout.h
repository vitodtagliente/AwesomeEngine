/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#include <awesome/asset/asset.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/base_asset.h>
#include <awesome/asset/image_asset.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/type_name.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/asset_browser_dialog.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

class Layout
{
public:
	Layout() = delete;

	static void begin(const std::string& name);
	static bool beginCombo(const std::string& name, const std::string& value);
	static void beginContext(const std::string context);
	static void beginDrag(const std::string& name, const std::string& item, void* const data, size_t size);
	static bool button(const std::string& name);
	static bool button(const std::string& name, int width, int height);
	static bool collapsingHeader(const std::string& name);
	static void end();
	static void endCombo();
	static void endContext();
	static void endDrag(const std::string& name, const std::function<void(void*, size_t)>& handler);
	static void image(const ImageAssetPtr& image);
	static void image(const ImageAssetPtr& image, float width, float height);
	static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect);
	static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect, float width, float height);
	static void input(const std::string& name, int& value);
	static void input(const std::string& name, bool& value);
	static void input(const std::string& name, float& value);
	static void input(const std::string& name, double& value);
	static void input(const std::string& name, std::string& value);
	static void input(const std::string& name, math::transform& value);
	static void input(const std::string& name, math::vec2& value);
	static void input(const std::string& name, math::vec3& value);
	static void input(const std::string& name, math::vec4& value);
	static void input(const std::string& name, graphics::Color& value);
	static void input(const std::string& name, graphics::TextureCoords& value);
	static void input(const std::string& name, graphics::TextureRect& value);
	static void input(const std::string& name, SpriteAnimation::Frame& value);
	static void input(const std::string& name, const std::string& category, TypeName<Type>& type);
	static void input(Type& value);
	static void input(std::unique_ptr<Type>& type);
	static void input(std::shared_ptr<Type>& type);
	static void input(const std::string& name, std::unique_ptr<Type>& type, const std::string& typeName);
	static void input(const std::string& name, std::shared_ptr<Type>& type, const std::string& typeName);
	// Ranges
	template <typename T>
	static void input(const std::string& name, std::pair<T, T>& value)
	{
		input(name + "-0", value.first);
		input(name + "-1", value.second);
	}
	// Enum input
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
	// Enum input
	template <typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
	static void input(const std::string& name, T& value)
	{
		const std::string strValue = enumToString(value);
		if (Layout::beginCombo(name.c_str(), strValue))
		{
			for (const auto& pair : EnumType<T>::values())
			{
				if (Layout::selectable(pair.first, strValue == pair.first))
				{
					value = static_cast<T>(pair.second);
					endCombo();
					return;
				}
			}
			endCombo();
		}
	}
	// Asset input
	template <Asset::Type T, typename D>
	static void input(const std::string& name, std::shared_ptr<BaseAsset<T, D>>& value)
	{
		static AssetBrowserDialog s_assetBrowserDialog;

		if (Layout::selectable(name + ": " + (value ? value->descriptor.path.stem().string() : ""), false))
		{
			s_assetBrowserDialog.open(name, T, [&value](const AssetPtr& asset) -> void
				{
					value = std::static_pointer_cast<BaseAsset<T, D>>(asset);
				}
			);
		}
		s_assetBrowserDialog.render(name);
	}
	// std::vector<T> input
	template <typename T>
	static void input(const std::string& name, std::vector<T>& list, const std::function<void(T&)>& handler, const std::function<T()>& createHandler)
	{
		beginContext(name);

		text(name);
		for (size_t i = 0; i < list.size(); ++i)
		{
			const std::string context = name + "[" + std::to_string(i) + "]";
			beginContext(context);
			if (collapsingHeader(context))
			{
				handler(list.at(i));
				if (button(TextIcon::minus()))
				{
					list.erase(list.begin() + i);

					endContext();
					break;
				}
			}
			endContext();
		}
		if (button(TextIcon::plus()))
		{
			list.push_back(std::move(createHandler()));
		}
		if (!list.empty())
		{
			sameLine();
			if (button(TextIcon::eraser()))
			{
				list.clear();
			}
		}

		endContext();
	}
	template<typename T> 
	static void input(const std::string& name, std::vector<T>& list)
	{
		input<T>(
			name, 
			list, 
			[](T& element) -> void 
			{
				input("Value", element);
			},
			[]() -> T
			{
				return T();
			}
		);
	}
	static void input(const std::string& name, std::vector<std::shared_ptr<Type>>& list, const std::string& typeName);
	static void input(const std::string& name, std::vector<std::unique_ptr<Type>>& list, const std::string& typeName);
	// std::map<K,T> support
	template <typename K, typename T>
	static void input(const std::string& name, std::map<K, T>& map, const std::function<void(T&)>& handler, const std::function<T()>& createHandler)
	{
		beginContext(name);

		text(name);
		for (auto& pair : map)
		{
			const std::string context = name + "[" + pair.first + "]";
			beginContext(context);
			if (collapsingHeader(context))
			{
				handler(pair.second);
				if (button(TextIcon::minus()))
				{
					map.erase(pair.first);
					
					endContext();
					break;
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
		if (button(TextIcon::plus()))
		{
			map.insert(std::make_pair(*newKey, std::move(createHandler())));
			if (typeid(K) == typeid(std::string))
			{
				reinterpret_cast<std::string*>(newKey)->clear();
			}
		}
		if (!map.empty())
		{
			sameLine();
			if (button(TextIcon::eraser()))
			{
				map.clear();
			}
		}

		endContext();
	}
	template<typename K, typename T>
	static void input(const std::string& name, std::map<K, T>& map)
	{
		input<K, T>(
			name,
			map,
			[](T& element) -> void
			{
				input("Value", element);
			},
			[]() -> T
			{
				return T();
			}
		);
	}
	static void input(const std::string& name, std::map<std::string, std::shared_ptr<Type>>& map, const std::string& typeName);
	static void input(const std::string& name, std::map<std::string, std::unique_ptr<Type>>& map, const std::string& typeName);
	static bool isWindowFocused();
	static bool isWindowHovered();
	static void newLine();
	static void rename(std::string& value);
	static void sameLine();
	static bool selectable(const std::string& name, bool selected);
	static bool selectable(const std::string& name, bool selected, const std::function<void()>& handler);
	static void separator();
	static void scroll(float position);
	static void scrollToBottom();
	static void slider(const std::string& name, int min, int max, int& value);
	static void slider(const std::string& name, float min, float max, float& value);
	static void setKeyboardFocusHere();
	static void sprite(const SpriteAssetPtr& sprite);
	static void sprite(const SpriteAssetPtr& sprite, float width, float height);
	static void text(const std::string& str);
	static void textWrapped(const std::string& str);
	static void title(const std::string& title);

	static void clear();

private:

	static std::string id(const std::string& label);

	static std::vector<std::string> s_context;
	static std::map<std::string, void*> s_keyCache;
};