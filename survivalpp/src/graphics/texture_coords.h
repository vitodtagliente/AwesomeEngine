/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

namespace graphics
{
	class TextureCoords
	{
	public:
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

		TextureCoords();
		TextureCoords(float u, float v);
		TextureCoords(const TextureCoords& coords);
		~TextureCoords() = default;

		TextureCoords(TextureCoords&& coords) = default;
		TextureCoords& operator= (const TextureCoords& coords) = default;
		TextureCoords& operator=(TextureCoords&& coords) = default;

		bool operator== (const TextureCoords& coords) const;
		bool operator!= (const TextureCoords& coords) const;
	};
}