#include "selection_system.h"

namespace editor 
{
	SelectionSystem::SelectionSystem()
		: m_selection()
	{
	}

	void SelectionSystem::select(Entity* entity)
	{
		m_selection = Selection(entity);
	}

	void SelectionSystem::select(std::shared_ptr<Asset> asset)
	{
		m_selection = Selection(asset);
	}

	void SelectionSystem::unselect()
	{
		m_selection = Selection();
	}

	SelectionSystem::Selection::Selection()
		: type(Type::None)
		, data()
	{
	}

	SelectionSystem::Selection::Selection(Entity* entity)
		: type(Type::Entity)
		, data(entity)
	{

	}

	SelectionSystem::Selection::Selection(std::shared_ptr<Asset> asset)
		: type(Type::Asset)
		, data(asset)
	{
	}

}
