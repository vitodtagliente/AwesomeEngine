#include "sprite_editor_window.h"

#include <awesome/asset/image_asset.h>
#include <awesome/editor/editor_ui.h>

char* const SpriteEditorWindow::getTitle() const
{
	return "Sprite Editor";
}

void SpriteEditorWindow::render()
{
	static ImageAsset s_image;

	EditorUI::input("Image", s_image);
	if (!s_image.ready()) return;


}