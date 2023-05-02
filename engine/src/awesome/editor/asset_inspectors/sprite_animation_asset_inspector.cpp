#include "sprite_animation_asset_inspector.h"

#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/form_layout.h>

bool SpriteAnimationAssetInspector::canInspect(int type) const
{
	return type == AssetType_SpriteAnimation;
}

char* const SpriteAnimationAssetInspector::getTitle() const
{
	return "Sprite Animation";
}

void SpriteAnimationAssetInspector::inspect(const AssetRecord& record)
{
	if (m_asset.id != record.id)
	{
		m_asset = SpriteAnimationAsset(record.id);
		m_asset.load();
	}

	if (!m_asset.ready()) return;

	if (FormLayout::button(TextIcon::save(" Save").c_str()))
	{
		m_asset.save();
	}
}