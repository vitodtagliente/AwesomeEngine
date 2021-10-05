/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Renderable
{
public:

	Renderable();
	~Renderable();

	void bind();
	void unbind();

private:

	// vertex array object
	unsigned int m_vao;
	// vertex buffer object
	unsigned int m_vbo;
	// elements buffer object
	unsigned int m_ebo;
};