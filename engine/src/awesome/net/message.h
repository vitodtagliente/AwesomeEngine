/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/serialization.h>

#include "netid.h"

namespace net
{
	struct Message : public ISerializable
	{
		netid id;
		bool reliable{ false };
		std::string type;
		std::string data;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
	};
}