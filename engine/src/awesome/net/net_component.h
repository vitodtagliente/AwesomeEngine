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

		virtual bool hasNetChanges() const = 0;
		virtual json::value netSerialize() const = 0;
		virtual void netDeserialize(const json::value& value) = 0;
	};
}