/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/asset/image_asset.h>
#include <awesome/engine/keycode.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

class Layout
{
public:
	Layout() = delete;

	static void begin(const std::string& name);
	static void beginChild(const std::string& name);
	static void beginChild(const std::string& name, float width, float height);
	static void beginContext(const std::string context);
	static bool beginTreeNode(const std::string& name, bool selected);
	static bool button(const std::string& name);
	static bool button(const std::string& name, int width, int height);
	static bool collapsingHeader(const std::string& name);
	static void end();
	static void endChild();
	static void endCombo();
	static void endContext();
	static void endTreeNode();
	static void hint(const std::string& text);
	static void image(const ImageAssetPtr& image);
	static void image(const ImageAssetPtr& image, float width, float height);
	static bool imageButton(const ImageAssetPtr& image);
	static bool imageButton(const ImageAssetPtr& image, float width, float height);
	static void input(const std::string& name, int& value);
	static void input(const std::string& name, bool& value);
	static void input(const std::string& name, float& value);
	static void input(const std::string& name, double& value);
	static void input(const std::string& name, std::string& value);
	static void inputMultiline(const std::string& name, std::string& value);
	static void input(const std::string& name, std::filesystem::path& value);
	static void input(const std::string& name, ImageAssetPtr& value);
	static void input(const std::string& name, math::transform& value);
	static void input(const std::string& name, math::vec2& value);
	static void input(const std::string& name, math::vec3& value);
	static void input(const std::string& name, math::vec4& value);
	static bool isKeyDown(keycode_t keycode);
	static bool isKeyPressed(keycode_t keycode);
	static bool isKeyReleased(keycode_t keycode);
	static bool isItemHovered();
	static bool isMouseClicked();
	static bool isPopupOpen(const std::string& name);
	static bool isTreeNodeClicked();
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
	static void text(const std::string& str);
	static void textWrapped(const std::string& str);
	static void title(const std::string& title);

	static void clear();

private:

	static std::string id(const std::string& label);

	static std::vector<std::string> s_context;
	static std::map<std::string, void*> s_keyCache;
};