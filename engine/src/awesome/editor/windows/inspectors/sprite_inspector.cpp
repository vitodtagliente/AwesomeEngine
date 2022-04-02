#include "sprite_inspector.h"

#include <awesome/data/sprite_animation.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>

namespace editor
{
	SpriteInspector::SpriteInspector()
		: m_previousSelectedAsset()
		, m_filename()
	{
		m_filename.reserve(300);
	}

	bool SpriteInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->type == Asset::Type::Sprite;
	}

	void SpriteInspector::inspect(const State::Selection& selection, const std::filesystem::path& path)
	{
		SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(selection.asAsset());

		const bool hasChanged = m_previousSelectedAsset != sprite.get();
		m_previousSelectedAsset = sprite.get();

		if (sprite == nullptr)
		{
			return;
		}

		Layout::image(sprite->data.image, sprite->data.rect);
		Layout::input("Rect", sprite->data.rect);

		if (hasChanged)
		{
			m_filename.clear();
		}

		if (Layout::collapsingHeader("Sprite Animation"))
		{
			Layout::input("Filename", &m_filename, 300);
			if (Layout::button("Save Animation"))
			{
				const std::string name = m_filename.c_str();
				if (!name.empty())
				{
					const std::string filename = (path / name).string() + ".spriteanim";
					SpriteAnimation animation;
					animation.save(filename);

					AssetImporter importer;
					importer.import(filename);
				}
				m_filename.clear();
			}
		}
	}
}