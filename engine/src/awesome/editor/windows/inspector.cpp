#include "inspector.h"

#include <fstream>
#include <vector>

#include <awesome/data/archive.h>
#include <awesome/editor/context.h>
#include <awesome/editor/selection_system.h>
#include <awesome/encoding/json.h>

namespace editor
{
	Inspector::Inspector()
		: Window()
		, m_prefabFilename()
	{
		m_prefabFilename.reserve(100);
	}

	void Inspector::render(Context& context)
	{
		const auto& selection = SelectionSystem::instance()->getSelection();
		if (selection.has_value())
		{
			if (selection->type == SelectionSystem::Selection::Type::Entity)
			{
				Entity* const entity = std::get<Entity*>(selection->data);
				if (entity != nullptr)
				{
					inspect(context, entity);
				}
			}
			else if (selection->type == SelectionSystem::Selection::Type::File)
			{
				const std::filesystem::path& file = std::get<std::filesystem::path>(selection->data);
				if (std::filesystem::exists(file))
				{
					inspect(context, file);
				}
			}
		}
	}

	void Inspector::inspect(Context& context, Entity* const entity)
	{
		context.input("Name", &entity->name, 100);
		context.input("Tag", &entity->tag, 100);
		context.input("Position", &entity->transform.position);
		context.input("Rotation", &entity->transform.rotation);
		context.input("Scale", &entity->transform.scale);
		context.input("Static", &entity->transform.isStatic);

		const auto& components = entity->getComponents();
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			Component* const component = *it;
			if (context.collapsingHeader(component->getTypeDescriptor().name))
			{
				component->inspect(context);
			}
		}

		if (context.collapsingHeader("Prefab options"))
		{
			context.input("Filename", &m_prefabFilename, 300);
			if (context.button("Save"))
			{
				Archive archive(m_prefabFilename, Archive::Mode::Write);
				archive << json::Serializer::to_string(entity->serialize());
			}
		}
	}

	void Inspector::inspect(Context& context, const std::filesystem::path& file)
	{
		{
			std::vector<std::string> exts = { ".txt", ".json", ".shader", ".prefab", ".md", ".bat", ".ini" };
			for (const std::string& ext : exts)
			{
				if (file.extension().string() == ext)
				{
					static const auto read = [](const std::string& filename) -> std::string
					{
						std::ostringstream buf;
						std::ifstream input(filename.c_str());
						buf << input.rdbuf();
						return buf.str();
					};

					std::string content = read(file.string());
					context.textWrapped(content);
					return;
				}
			}
		}

		{
			std::vector<std::string> exts = { ".png", ".jpg", ".jpeg", ".bmp" };
			for (const std::string& ext : exts)
			{
				if (file.extension().string() == ext)
				{
					static const auto read = [](const std::string& filename) -> std::string
					{
						std::ostringstream buf;
						std::ifstream input(filename.c_str());
						buf << input.rdbuf();
						return buf.str();
					};

					std::string content = read(file.string());
					context.textWrapped(content);
					return;
				}
			}
		}
	}

	REFLECT_IMP(Inspector)
}