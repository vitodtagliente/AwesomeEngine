#include <awesome/editor/windows/asset_inspector_window.h>

#include <awesome/editor/editor.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/graphics/color.h>

AssetInspectorWindow::AssetInspectorWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const AssetInspectorWindow::getTitle() const
{
	return "Asset Inspector";
}

void AssetInspectorWindow::init()
{
	for (const auto& [name, options] : TypeFactory::list("Type", "AssetInspector"))
	{
		std::unique_ptr<AssetInspector> inspector = std::unique_ptr<AssetInspector>(TypeFactory::instantiate<AssetInspector>(name));
		if (inspector != nullptr)
		{
			m_inspectors.push_back(std::move(inspector));
		}
	}
}

void AssetInspectorWindow::render()
{
	static const graphics::Color s_filenameColor(0.f, 0.6f, 0.6f);
	static const graphics::Color s_assetTypeColor(1.f, 0.6f, 0.6f);

	if (m_editorState->selection.asset.has_value())
	{
		const AssetRecord& record = m_editorState->selection.asset.value();

		for (const auto& inspector : m_inspectors)
		{
			if (inspector->canInspect(record.type))
			{
				const std::string title = inspector->getTitle();
				FormLayout::button(title.empty() ? "Asset" : title.c_str(), s_assetTypeColor);
				FormLayout::sameLine();
				if (FormLayout::button(record.path.filename().string().c_str(), s_filenameColor))
				{
					m_editorState->select(record.path);
				}
				FormLayout::separator();
				inspector->inspect(record);
				return;
			}
		}

		// no inspector found
		FormLayout::button("Asset", s_assetTypeColor);
		FormLayout::sameLine();
		if (FormLayout::button(record.path.filename().string().c_str(), s_filenameColor))
		{
			m_editorState->select(record.path);
		}
		FormLayout::separator();
		FormLayout::text("Cannot inspect the selected asset");
	}
}