/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

class Patrol : public Component
{
public:
	Patrol() = default;
	virtual ~Patrol() = default;

	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	REFLECT()

private:

};