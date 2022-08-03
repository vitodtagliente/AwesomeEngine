/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>

namespace editor
{
	class MenuItem : public IProtoClass
	{
	public:
		MenuItem() = default;
		virtual ~MenuItem() = default;

		virtual std::string getCategory() const = 0;
		virtual std::string getName() const { return get_descriptor().name; }

		virtual void execute() = 0;
	};

	typedef std::unique_ptr<MenuItem> MenuItemPtr;
}