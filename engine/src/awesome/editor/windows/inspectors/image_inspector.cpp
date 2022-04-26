#include "image_inspector.h"

#include <awesome/data/image_asset.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool ImageInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Asset
			&& selection.asAsset()->descriptor.type == Asset::Type::Image;
	}

	void ImageInspector::inspect(const State::Selection& selection)
	{
		ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(selection.asAsset());
		if (image == nullptr || !image->data.has_value())
		{
			return;
		}

		Layout::image(image);
	}
}