#include "state.h"

#include <awesome/data/asset_library.h>

namespace editor
{
	State::State()
		: selection()
		, workPath(AssetLibrary::instance()->getDirectory())
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

	void State::select()
	{
		selection = Selection();
	}

	State::Selection::Selection()
		: type(Type::None)
		, data()
	{
	}

	State::Selection::Selection(Entity* const entity)
		: type(Type::Entity)
		, data(entity)
	{
	}

	State::Selection::Selection(const std::shared_ptr<Asset>& asset)
		: type(Type::Asset)
		, data(asset)
	{
	}
}