/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "window_generated.h"

CLASS()
class Window : public IType
{
public:
	Window() = default;
	virtual ~Window() = default;

	virtual std::string getTitle() const;
	inline bool hasFocus() const { return m_hasFocus; }

	void setFocus(bool focus);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double /*deltaTime*/) {}

	virtual void onFocusChange(bool /*focus*/) {}

	GENERATED_BODY()

private:
	bool m_hasFocus{ false };
};

typedef std::unique_ptr<Window> WindowPtr;