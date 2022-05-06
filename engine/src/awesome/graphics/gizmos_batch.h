/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/vector3.h>

#include "color.h"
#include "command.h"

namespace graphics
{
#define DEFAULT_GIZMOS_BATCH_SIZE 2000

	class Context;

	class GizmosBatch
	{
	public:
		GizmosBatch(int batchSize = DEFAULT_GIZMOS_BATCH_SIZE);

		void batch(const math::vec3& position, const Color& color);
		void flush(Context* const context);

	private:

		class Batch
		{
		public:
			Batch(int size = DEFAULT_GIZMOS_BATCH_SIZE);

			inline size_t size() const { return m_data.size(); }
			inline int capacity() const { return m_size; }
			inline bool empty() const { return m_data.empty(); }
			inline const std::vector<float>& data() const { return m_data; }
			inline bool full() const { return m_size <= m_data.size(); }

			void batch(const math::vec3& position, const Color& color);
			void clear();

		private:
			int m_size;
			std::vector<float> m_data;

		};

		Batch& findNextBatch();

		int m_batchSize;
		int m_batchIndex;
		std::vector<Batch> m_batches;

	};
}