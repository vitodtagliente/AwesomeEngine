/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Window
{
public:
	Window() = default;
	virtual ~Window() = default;

	virtual char* const getTitle() const = 0;

	inline bool hasFocus() const { return m_hasFocus; }
	inline bool isHovered() const { return m_isHovered; }

	void setFocus(bool focus);
	void setIsHovered(bool isHovered);

	virtual void init() {}
	virtual void render() {}
	virtual void update(double /*deltaTime*/) {}

	virtual void onFocusChange(bool /*focus*/) {}

	bool visible{ true };

private:
	bool m_hasFocus{ false };
	bool m_isHovered{ false };
};