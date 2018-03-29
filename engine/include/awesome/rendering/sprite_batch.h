#pragma once

#include <map>
#include <vector>
#include "../math/math.h"
#include "shading/texture.h"
#include "shading/material.h"

namespace Awesome
{
	/* base sprite batch rendering data */
	struct SpriteBatchRenderingData
	{
		glm::mat4 transform{ 1.0f };
		Math::Rect textureCoords{ 0.0f,0.0f,1.0f,1.0f };
		Material* material{ nullptr };
	};

	class SpriteBatch
	{
	private:
		unsigned int vao{0};
		unsigned int vbo{0};
		unsigned int uv_vbo{0};
		unsigned int eab{0};

		static SpriteBatch* singleton;

		SpriteBatch();
		~SpriteBatch();

		std::map<Texture*, std::vector<SpriteBatchRenderingData>> data;
			
	public:
		static SpriteBatch* instance();

		void init();
		void add(Texture* texture, const SpriteBatchRenderingData& in_data);
		void clear();
		void draw();
	};
}