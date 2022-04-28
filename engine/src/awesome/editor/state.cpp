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

	void State::select(const std::shared_ptr<Asset>& asset)
	{
		selection = Selection(asset);
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

	State::Selection::Selection(const std::shared_ptr<Asset>& asset)
		: type(Type::Asset)
		, data(asset)
	{
		Layout::clear();
	}
}