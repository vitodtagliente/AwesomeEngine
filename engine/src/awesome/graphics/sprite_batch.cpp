#include "sprite_batch.h"

#include "context.h"

namespace graphics
{
	SpriteBatch::Batch::Batch(const int size)
		: m_size(size)
		, m_data()
	{
		m_data.reserve(size);
	}

	void SpriteBatch::Batch::batch(const math::mat4& matrix, const TextureRect& rect)
	{
		m_data.push_back(std::make_pair(matrix, rect));
	}

	void SpriteBatch::Batch::clear()
	{
		m_data.clear();
	}

	SpriteBatch::SpriteBatch(const int batchSize)
		: m_batchSize(batchSize)
		, m_batches()
	{
		m_batches.reserve(20); // 20 textures?
	}

	void SpriteBatch::batch(Texture* const texture, const math::mat4& matrix, const TextureRect& rect)
	{
		findNextBatch(texture).batch(matrix, rect);
	}

	void SpriteBatch::clear()
	{

	}

	std::vector<Command*> SpriteBatch::commands()
	{
		std::vector<Command*> commands;
		for (auto& pair : m_batches)
		{
			Texture* const texture = pair.first;
			for (Batch& batch : pair.second)
			{
				SpriteCommand* command = new SpriteCommand();
				command->texture = texture;
				command->data = std::move(batch.data());
				batch.clear();
				commands.push_back(command);
			}
		}
		return commands;
	}

	SpriteBatch::Batch& SpriteBatch::findNextBatch(Texture* const texture)
	{
		const auto& it = m_batches.find(texture);
		if (it == m_batches.end())
		{
			const auto& insertedPair = m_batches.insert(std::make_pair(texture, std::vector<Batch>{}));
			std::vector<Batch>& batches = insertedPair.first->second;
			return batches.emplace_back(Batch(m_batchSize));
		}

		std::vector<Batch>& batches = it->second;
		if (batches.front().full() == false)
		{
			return batches.front();
		}

		return batches.emplace_back(Batch(m_batchSize));
	}

	SpriteCommand::SpriteCommand()
		: Command()
		, texture()
		, data()
	{
	}

	void SpriteCommand::execute(Context& context)
	{
		context.drawSprites(texture, data);
	}
}