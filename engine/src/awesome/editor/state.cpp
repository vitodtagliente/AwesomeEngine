#include "state.h"

#include <awesome/asset/asset_library.h>
#include <awesome/entity/entity.h>

#include "layout.h"

State::State()
	: isContentChanged(false)
	, path(AssetLibrary::instance().getDirectory())
	, selection()
{
}

void State::select(Entity* const entity)
{
	selection.entity = entity;
	Layout::clear();
}

void State::select(const AssetPtr& asset)
{
	static const size_t s_maxHistory{ 10 };

	selection.asset = asset;

	if (history.size() == s_maxHistory)
	{
		history.pop();
	}
	history.push(asset);
	Layout::clear();
}

bool State::hasPendingContentRefresh()
{
	const bool result = isContentChanged;
	return isContentChanged = false, result;
}

void State::select()
{
	selection.clear();
}

void State::Selection::clear()
{
	asset = nullptr;
	entity = nullptr;
	path = AssetLibrary::instance().getDirectory();
}