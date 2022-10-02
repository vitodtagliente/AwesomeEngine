/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>
#include <vector>

class ContextMenu
{
public:
	ContextMenu() = default;

	inline bool isOpen() const { return m_open; }

	void close();
	void open(const std::string& title, const std::vector<std::string>& items, const std::function<void(const std::string&)>& handler);
	void render();

	static constexpr char* const Separator{ "separator" };

private:
	std::function<void(const std::string&)> m_handler;
	std::vector<std::string> m_items;
	bool m_open{ false };
	std::string m_title;
};