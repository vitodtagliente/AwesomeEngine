#include "state.h"

#include <awesome/asset/asset_library.h>

#include "layout.h"

namespace editor
{
	State::State()
		: isContentChanged(false)
		, path(AssetLibrary::instance().getDirectory())
		, selection()
	{
	}

	void State::select(Entity* const entity)
	{
		selection = Selection(entity);
	}

	void State::select(const AssetPtr& asset)
	{
		static const size_t s_maxHistory{ 10 };

		selection = Selection(asset);

		if (history.size() == s_maxHistory)
		{
			history.pop_back();
		}
		history.push_back(asset);
	}

	bool State::hasPendingContentRefresh()
	{
		const bool result = isContentChanged;
		return isContentChanged = false, result;
	}

	void State::select()
	{
		selection = Selection();
	}

	State::Selection::Selection()
		: type(Type::None)
		, data()
	{
		Layout::clear();
	}

	State::Selection::Selection(Entity* const entity)
		: type(Type::Entity)
		, data(entity)
	{
		Layout::clear();
	}

	State::Selection::Selection(const AssetPtr& asset)
		: type(Type::Asset)
		, data(asset)
	{
		Layout::clear();
	}
}