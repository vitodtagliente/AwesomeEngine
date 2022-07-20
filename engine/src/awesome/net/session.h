/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "netid.h"

namespace net
{
	class Session
	{
	public:
		Session() = default;

		const netid& netId() const { return m_id; }

	private:
		netid m_id;
	};
}