/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

class Lifetime : public Component
{
public:
	Lifetime() = default;
	virtual ~Lifetime() = default;

	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	REFLECT()

private:
	double m_lifetime{ 1.0 };
	double m_timer{ 0.0 };
};