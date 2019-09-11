#pragma once

#include <memory>
#include <vector>
#include "actor.h"

namespace awesome
{
	class w1
	{
	public:

		w1() = default;


		// destory all the actors
		void clear();

	private:

		// world's actors
		std::vector<std::unique_ptr<Actor>> m_actors;
	};
}