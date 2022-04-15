#include "select_list.h"

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>

namespace editor
{
	void SelectList::render(const std::vector<std::string>& items, const std::string& selectedItem)
	{
		const bool hasActiveFocus = Layout::isWindowFocused();
		if (hasActiveFocus)
		{
			processInput(selectedItem);
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
			const bool isSelected = item == selectedItem;
			if (isSelected && m_state == State::Renaming)
			{
				Layout::rename(m_tempRename);
			}
			else
			{
				if (!m_filter.empty() && !StringUtil::contains(item, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				if (Layout::selectable(item, isSelected))
				{
					onItemSelection(item);
					m_state = State::Navigating;
				}
			}
		}
	}

	void SelectList::processInput(const std::string& selectedItem)
	{
		const bool hasSelectedItem = !selectedItem.empty();

		Input& input = Input::instance();
		if (m_state == State::Renaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_state = State::Navigating;
				onRenameItem(selectedItem, m_tempRename);
			}
		}
		else if (hasSelectedItem)
		{
			if (input.isKeyPressed(KeyCode::F2))
			{
				m_state = State::Renaming;
				m_tempRename = selectedItem;
			}
			else if (input.isKeyPressed(KeyCode::Delete))
			{
				onRemoveItem(selectedItem);
			}
		}
	}
}