/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include "color.h"
#include <awesome/core/singleton.h>
#include "gizmos.h"
#include "texture.h"
#include <vdtmath/transform.h>
#include "texture_rect.h"
#include "sprite_batch.h"

class Command;
class Context;

class Renderer : public Singleton<Renderer>
{
public:

	Renderer(Context& context);

	void begin();
	void flush();
	void clear();

	void drawSprite(Texture* const texture, const math::transform& transform, const TextureRect& rect = {});

	Color backgroundColor;

	inline Gizmos& getGizmos() { return m_gizmos; }

private:

	Context& m_context;
	Gizmos m_gizmos;
	SpriteBatch m_spriteBatch;
	std::vector<Command*> m_commands;

};