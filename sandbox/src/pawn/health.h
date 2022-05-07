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

	inline int get() const { return m_value; }
	void set(int v);
	inline bool isAlive() const { return m_value > 0; }

	int getPercentage() const;

	Health& operator+= (int value);
	Health& operator-= (int value);

	REFLECT()

	int min{ 0 };
	int max{ 100 };

private:
	int m_value{ 100 };
	bool m_destroyOnDeath{ false };
};