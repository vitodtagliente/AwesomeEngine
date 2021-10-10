/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>
#include "color.h"
#include <vdtmath/vector3.h>
#include "command.h"
#include "texture.h"
#include <vdtmath/matrix4.h>
#include "texture_rect.h"

#define DEFAULT_SPRITE_BATCH_SIZE 2000

class Context;

class SpriteCommand : public Command
{
public:
	SpriteCommand();

	Texture* texture;
	std::vector<std::pair<math::mat4, TextureRect>> data;

	virtual void execute(Context& context) override;
};

class SpriteBatch
{
public:

	SpriteBatch(int batchSize = DEFAULT_SPRITE_BATCH_SIZE);

	void batch(Texture* const texture, const math::mat4& matrix, const TextureRect& rect);
	void clear();

	std::vector<Command*> commands() const;

private:

	class Batch
	{
	public:
		Batch(int size = DEFAULT_SPRITE_BATCH_SIZE);

		inline size_t size() const { return m_data.size(); }
		inline int capacity() const { return m_size; }
		inline bool empty() const { return m_data.empty(); }
		inline const std::vector<std::pair<math::mat4, TextureRect>>& data() const { return m_data; }
		inline bool full() const { return m_size <= m_data.size(); }

		void batch(const math::mat4& matrix, const TextureRect& rect);
		void clear();

	private:

		int m_size;
		std::vector<std::pair<math::mat4, TextureRect>> m_data;

	};

	Batch& findNextBatch(Texture* const texture);

	int m_batchSize;
	std::map<Texture*, std::vector<Batch>> m_batches;

};