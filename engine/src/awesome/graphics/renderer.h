/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include "color.h"
#include <awesome/core/singleton.h>
#include "gizmos.h"
#include "texture.h"
#include <vdtmath/matrix4.h>
#include "texture_rect.h"
#include "sprite_batch.h"

class Command;
class Context;

class Renderer : public Singleton<Renderer>
{
public:

	struct Stats
	{
		Stats();

		int drawCalls;
	};

	Renderer(Context& context);

	void begin();
	void flush();
	void clear();

	void pushCamera(const math::mat4& camera);
	void drawSprite(Texture* const texture, const math::mat4& matrix, const TextureRect& rect = {});

	Color backgroundColor;

	inline Gizmos& getGizmos() { return m_gizmos; }
	inline const Stats& getStats() const { return m_stats; }

private:

	Context& m_context;
	Gizmos m_gizmos;
	SpriteBatch m_spriteBatch;
	std::vector<Command*> m_commands;
	Stats m_stats;

};