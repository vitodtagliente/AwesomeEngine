/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

class Health : public Component
{
public:
	Health() = default;
	virtual ~Health() = default;

	virtual void init() override;

	void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	void set(int v);
	inline bool isAlive() const { return value > 0; }

	REFLECT()

	int min{ 0 };
	int max{ 100 };
	int value{ 100 };
};