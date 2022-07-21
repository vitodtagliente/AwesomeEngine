/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include <awesome/core/serialization.h>

#include "netid.h"

namespace net
{
	struct Message : public ISerializable
	{
		struct Header
		{
			netid id;
			uint8_t version;
			std::string commandId;
			std::map<std::string, std::string> attributes;
		};

		struct Body
		{
			std::string data;
		};

		Header header;
		Body body;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
	};
}