/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>

namespace editor
{
	class MenuItem
	{
	public:
		MenuItem() = default;
		virtual ~MenuItem() = default;

		virtual std::string getCategory() const = 0;
		virtual std::string getName() const = 0;

		virtual void render() {}
		virtual void execute() = 0;
	};
}

#define REFLECT_MENU_ITEM(T) REFLECT_IMP_CATEGORY(T, MenuItem)