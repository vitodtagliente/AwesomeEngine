/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/entity/component.h>

class SpriteFsm : public Component
{
public:
	SpriteFsm() = default;
	virtual ~SpriteFsm() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

private:
	class SpriteAnimator* m_animator{ nullptr };
};