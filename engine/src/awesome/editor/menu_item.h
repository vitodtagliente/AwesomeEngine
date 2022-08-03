/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

namespace editor
{
	class MenuItem
	{
	public:
		MenuItem() = default;
		virtual ~MenuItem() = default;

		virtual std::string getCategory() const = 0;
		virtual std::string getName() const = 0;

		virtual void execute() = 0;
	};

	typedef std::unique_ptr<MenuItem> MenuItemPtr;
}