/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

namespace net
{
	enum class NetMode;
}

REFLECT_ENUM(net::NetMode,
	Client,
	Shared,
	Server
)