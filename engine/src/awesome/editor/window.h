/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "window_generated.h"

CLASS()
class Window : public Type
{
public:
	Window() = default;
	virtual ~Window() = default;

	virtual std::string getTitle() const;
	inline bool hasFocus() const { return m_hasFocus; }
	inline bool isHovered() const { return m_isHovered; }

	void setFocus(bool focus);
	void setIsHovered(bool isHovered);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double /*deltaTime*/) {}

	virtual void onFocusChange(bool /*focus*/) {}

	PROPERTY() bool visible{ true };

	GENERATED_BODY()

private:
	bool m_hasFocus{ false };
	bool m_isHovered{ false };
};

typedef std::unique_ptr<Window> WindowPtr;