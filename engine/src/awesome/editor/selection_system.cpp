#include "selection_system.h"

namespace editor 
{
	SelectionSystem::SelectionSystem()
		: m_path()
		, m_selection()
	{
	}

	void SelectionSystem::select(Entity* entity)
	{
		m_selection = Selection(entity);
	}

	void SelectionSystem::select(const std::shared_ptr<Asset>& asset)
	{
		m_selection = Selection(asset);
	}

	void SelectionSystem::select(const std::filesystem::path& path)
	{
		m_path = path;
		unselect();
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

	SelectionSystem::Selection::Selection(const std::shared_ptr<Asset>& asset)
		: type(Type::Asset)
		, data(asset)
	{
	}

}
