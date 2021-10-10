#include "sprite_renderer.h"

#include <awesome/scene/entity.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <imgui.h>

SpriteRenderer::SpriteRenderer()
	: Component()
	, texture()
	, rect()
{

}

void SpriteRenderer::render(graphics::Renderer& renderer)
{
	if (texture != nullptr)
	{
		renderer.drawSprite(texture, getOwner()->transform.matrix(), rect);
	}
}

void SpriteRenderer::inspect()
{
	if (ImGui::CollapsingHeader("SpriteRenderer"))
	{
		ImGui::Checkbox("enabled", &enabled);
		ImGui::InputFloat4("rect", rect.data);
	}
}
