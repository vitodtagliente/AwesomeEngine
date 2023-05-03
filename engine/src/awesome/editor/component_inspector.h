/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "component_inspector_generated.h"

CLASS()
class ComponentInspector : public IType
{
public:
	ComponentInspector() = default;
	virtual ~ComponentInspector() = default;

	virtual char* const getIcon() const { return ""; }
	virtual char* const getTitle() const { return ""; }

	inline bool hasFocus() const { return m_hasFocus; }
	inline bool isHovered() const { return m_isHovered; }

	void setFocus(bool focus);
	void setIsHovered(bool isHovered);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double /*deltaTime*/) {}

	virtual void onFocusChange(bool /*focus*/) {}

	bool visible{ true };

	GENERATED_BODY()

private:
	bool m_hasFocus{ false };
	bool m_isHovered{ false };
};