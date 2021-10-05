#include "renderable.h"

#include <glad/glad.h>

Renderable::Renderable()
	: m_vao()
	, m_vbo()
	, m_ebo()
{
	glGenVertexArrays(1, &m_vao);
}

Renderable::~Renderable()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Renderable::bind()
{
	glBindVertexArray(m_vao);
}

void Renderable::unbind()
{
	glBindVertexArray(0);
}
