/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>
#include <vector>

namespace editor
{
	class SelectList
	{
	public:
		SelectList();

		void render(const std::vector<std::string>& items, const std::string& selectedItem);

		std::function<void()> onAddItem;
		std::function<void(const std::string&)> onItemSelection;
		std::function<void(const std::string&)> onRemoveItem;
		std::function<void(const std::string&, const std::string&)> onRenameItem;

	private:

		void processInput(const std::string& selectedItem);

		enum class State
		{
			Navigating,
			Renaming
		};

		std::string m_filter;
		State m_state;
		std::string m_tempRename;
	};
}