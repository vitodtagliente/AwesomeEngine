#include "texture_coords.h"

namespace graphics
{
	const TextureCoords TextureCoords::zero = TextureCoords();
	const TextureCoords TextureCoords::ones = TextureCoords(1.0f, 1.0f);

	TextureCoords::TextureCoords()
		: u(0.0f)
		, v(0.0f)
	{

	}

	TextureCoords::TextureCoords(const float u, const float v)
		: u(u)
		, v(v)
	{

	}

	bool TextureCoords::operator==(const TextureCoords& coords) const
	{
		return u == coords.u && v == coords.v;
	}

	bool TextureCoords::operator!=(const TextureCoords& coords) const
	{
		return u != coords.u || v != coords.v;
	}

	TextureCoords::TextureCoords(const TextureCoords& coords)
		: u(coords.u)
		, v(coords.v)
	{
	}
}