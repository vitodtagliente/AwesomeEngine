/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>

#include <awesome/core/reflection.h>

#include <awesome/asset/image_asset.h>
#include <awesome/engine/keycode.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>
#include <awesome/scene/entity.h>

#include "editor_style.h"

struct EditorUI final
{
	EditorUI() = delete;

	struct Child final
	{
		Child() = delete;

		static void begin(const char* const name);
		static void begin(const char* const name, float width, float height);
		static void end();
	};

	struct Combo final
	{
		Combo() = delete;

		static bool begin(const char* const name, const char* const value);
		static void end();
	};

	struct Dialog final
	{
		Dialog() = delete;

		static void save(const char* const name, const char* const extension, const std::function<void(const std::filesystem::path&)>& handler);
	};

	struct DragDrop final
	{
		DragDrop() = delete;

		static void begin(const char* const name, const char* const item, void* const data, size_t size);
		static void end(const char* const name, const std::function<void(void*, size_t)>& handler);
	};

	struct Icon final
	{
		Icon() = delete;

		static const std::string copy;
		static const std::string cube;
		static const std::string eraser;
		static const std::string eye;
		static const std::string file;
		static const std::string folder;
		static const std::string horse;
		static const std::string image;
		static const std::string minus;
		static const std::string music;
		static const std::string paste;
		static const std::string pause;
		static const std::string play;
		static const std::string plus;
		static const std::string save;
		static const std::string search;
		static const std::string stop;
		static const std::string tree;
		static const std::string upload;
		static const std::string video;
	};

	struct Input final
	{
		Input() = delete;

		static bool isKeyDown(keycode_t keycode);
		static bool isKeyPressed(keycode_t keycode);
		static bool isKeyReleased(keycode_t keycode);
		static bool isItemHovered();
		static bool isMouseClicked();
		static void scroll(float position);
		static void scrollToBottom();
	};

	struct Menu final
	{
		Menu() = delete;

		static bool beginBar();
		static void endBar();

		static bool begin(const char* const name);
		static void end();
		static bool item(const char* const name);
		static bool item(const char* const name, bool& checked);
	};

	struct Popup final
	{
		Popup() = delete;

		static bool begin(const char* const name);
		static void end();
		static void open(const char* const name);
	};

	struct Runtime final
	{
		Runtime() = delete;

		static void startup(void* const windowHandler);
		static void preRendering();
		static void postRendering();
		static void update();
		static void shutdown();
	};

	struct Style final
	{
		Style() = delete;

		static void apply(const EditorStyle& style);
	};

	struct Tree final
	{
		Tree() = delete;

		static bool begin(const char* const name, bool selected);
		static void end();
		static bool isClicked();
		static void openNextItem();
	};

	struct Window final
	{
		Window() = delete;

		static void begin(const char* const name);
		static void end();
		static bool isFocused();
		static bool isHovered();
	};

	enum class HorizontalAlignment
	{
		Left,
		Middle,
		Right
	};

	static void align(HorizontalAlignment alignment, float widthNextElement = 0.f);
	static void begin(const char* const name);
	static bool button(const char* const name);
	static bool button(const char* const name, float width, float height = 0.f);
	static bool button(const char* const name, const graphics::Color& color);
	static bool button(const char* const name, const graphics::Color& color, float width, float height = 0.f);
	static bool collapsingHeader(const char* const name);
	static void end();
	static void hint(const std::string& text);
	static void image(const ImageAsset& image);
	static void image(const ImageAsset& image, float width, float height);
	static void image(const ImageAsset& image, const graphics::TextureRect& rect);
	static void image(const ImageAsset& image, const graphics::TextureRect& rect, float width, float height);
	static bool imageButton(const ImageAsset& image);
	static bool imageButton(const ImageAsset& image, float width, float height);
	static bool imageButton(const ImageAsset& image, const graphics::TextureRect& rect);
	static bool imageButton(const ImageAsset& image, const graphics::TextureRect& rect, float width, float height);
	static void newLine();
	static void rename(std::string& value);
	static void sameLine();
	static bool search(std::string& value);
	static bool selectable(const char* const name, bool selected);
	static bool selectable(const char* const name, bool selected, const std::function<void()>& handler);
	static bool selectableDoubleClick(const char* const name, bool selected);
	static void separator();
	static void separatorText(const char* const name);
	static void slider(const char* const name, int min, int max, int& value);
	static void slider(const char* const name, float min, float max, float& value);
	static void text(const char* const str);
	static void textWrapped(const char* const str);
	static void title(const char* const title);

	static void input(const char* const name, Asset& asset);
	static void input(const char* const name, int& value);
	static void input(const char* const name, bool& value);
	static void input(const char* const name, float& value);
	static void input(const char* const name, double& value);
	static void input(const char* const name, std::string& value);
	static void input(const char* const name, std::filesystem::path& value);
	static void input(const char* const name, math::transform& value);
	static void input(const char* const name, math::vec2& value);
	static void input(const char* const name, math::vec3& value);
	static void input(const char* const name, math::vec4& value);
	static void input(const char* const name, graphics::Color& value);
	static void input(const char* const name, graphics::TextureCoords& value);
	static void input(const char* const name, graphics::TextureRect& value);
	static void inputMultilineText(const char* const name, std::string& value);

	static void input(Entity& entity);
	static void input(IType& type);

	// Enum input
	template <typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
	static void input(const char* const name, T& value)
	{
		const std::string strValue = enumToString(value);
		if (Combo::begin(name, strValue.c_str()))
		{
			for (const auto& [option_name, option_value] : reflect::Enum<T>::values())
			{
				if (selectable(option_name.c_str(), strValue == option_name))
				{
					value = static_cast<T>(option_value);
					break;
				}
			}
			Combo::end();
		}
	}

	// vectors
	// std::vector<T> input
	template <typename T>
	static void input(const char* const name, std::vector<T>& list, const std::function<void(T&)>& handler, const std::function<T()>& createHandler)
	{
		begin(name);

		text(name);
		for (size_t i = 0; i < list.size(); ++i)
		{
			std::string context(name);
			context += "[" + std::to_string(i) + "]";
			begin(context.c_str());
			if (collapsingHeader(context.c_str()))
			{
				handler(list.at(i));
				if (button(Icon::minus.c_str()))
				{
					list.erase(list.begin() + i);

					end();
					break;
				}
			}
			end();
		}
		if (button(Icon::plus.c_str()))
		{
			list.push_back(std::move(createHandler()));
		}
		if (!list.empty())
		{
			sameLine();
			if (button(Icon::eraser.c_str()))
			{
				list.clear();
			}
		}

		end();
	}
	template<typename T>
	static void input(const char* const name, std::vector<T>& list)
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
};