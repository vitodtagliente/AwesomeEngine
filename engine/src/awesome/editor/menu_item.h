/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include "menu_item_generated.h"

CLASS()
class MenuItem : public IType
{
public:
	MenuItem() = default;
	virtual ~MenuItem() = default;

	virtual std::string getCategory() const { return ""; };
	virtual std::string getName() const { return getTypeName(); }

	virtual void execute() {};

	GENERATED_BODY()
};

typedef std::unique_ptr<MenuItem> MenuItemPtr;