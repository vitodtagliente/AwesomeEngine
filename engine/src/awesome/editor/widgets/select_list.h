/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>

namespace editor
{
	template <typename T>
	class SelectList
	{
	public:
		SelectList()
			: onAddItem()
			, onItemSelection()
			, onRemoveItem()
			, onRenameItem()
			, onRenderItem()
			, m_filter()
			, m_state(State::Navigating)
			, m_tempRename()
		{
			onRenderItem = [](const T&, const std::string& name, const bool isSelected) -> bool 
			{
				return Layout::selectable(name, isSelected); 
			};
		}

		void render(const std::map<T, std::string>& items, const std::optional<T>& selectedItem)
		{
			const bool hasActiveFocus = Layout::isWindowFocused();
			if (hasActiveFocus && selectedItem.has_value())
			{
				processInput(*selectedItem);
			}

			if (Layout::button(ICON_FA_PLUS))
			{
				onAddItem();
			}

			Layout::sameLine();

			const std::string previousFilter = m_filter;
			Layout::input(ICON_FA_SEARCH, m_filter);
			if (previousFilter != m_filter || !hasActiveFocus)
			{
				m_state = State::Navigating;
			}

			Layout::separator();

			for (const auto& item : items)
			{
				const bool isSelected = selectedItem.has_value() && item.first == *selectedItem;
				if (isSelected && m_state == State::Renaming)
				{
					Layout::rename(m_tempRename);
				}
				else
				{
					if (!m_filter.empty() && !StringUtil::contains(item.second, m_filter, StringUtil::CompareMode::IgnoreCase))
					{
						continue;
					}

					if (onRenderItem(item.first, item.second, isSelected))
					{
						onItemSelection(item.first);
						m_state = State::Navigating;
						m_tempRename = item.second;
					}
				}
			}
		}

		std::function<void()> onAddItem;
		std::function<void(const T&)> onItemSelection;
		std::function<void(const T&)> onRemoveItem;
		std::function<void(const T&, const std::string&)> onRenameItem;
		std::function<bool(const T&, const std::string&, bool)> onRenderItem;

	private:

		void processInput(const T& selectedItem)
		{
			Input& input = Input::instance();
			if (m_state == State::Renaming)
			{
				if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
				{
					m_state = State::Navigating;
					onRenameItem(selectedItem, m_tempRename);
				}
			}
			else
			{
				if (input.isKeyPressed(KeyCode::F2))
				{
					m_state = State::Renaming;
				}
				else if (input.isKeyPressed(KeyCode::Delete))
				{
					onRemoveItem(selectedItem);
				}
			}
		}

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