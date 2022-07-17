/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/encoding/json.h>

namespace net
{
	class INetworkComponent
	{
	public:
		INetworkComponent() = default;
		virtual ~INetworkComponent() = default;

		virtual json::value serialize() const = 0;
		virtual void deserialize(const json::value& value) = 0;
	};
}