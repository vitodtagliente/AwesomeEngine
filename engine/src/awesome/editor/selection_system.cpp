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

	void SelectionSystem::select(const std::filesystem::path& file)
	{
		m_selection = Selection(file);
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

	SelectionSystem::Selection::Selection(const std::filesystem::path& file)
		: type(Type::File)
		, data(file)
	{
	}

}
