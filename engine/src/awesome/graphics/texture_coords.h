/// Copyright (c) Vito Domenico Tagliente
#pragma once

class TextureCoords
{
	static const TextureCoords zero;
	static const TextureCoords ones;

	union
	{
		struct
		{
			float u, v;
		};

		float data[2];
	};

	TextureCoords()
		: u(0.0f)
		, v(0.0f)
	{

	}

	TextureCoords(const float u, const float v)
		: u(u)
		, v(v)
	{

	}

	TextureCoords(const TextureCoords& coords)
		: u(coords.u)
		, v(coords.v)
	{
	}
};