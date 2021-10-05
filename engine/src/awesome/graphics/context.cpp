#include "context.h"

#include <glad/glad.h>

void Context::clear(const Color& color)
{
	glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Context::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Context::drawLines(const std::vector<std::pair<math::vec3, Color>>& lines)
{
	if (lines.empty()) return;

	// fill geometry data
	std::vector<float> vertices;
	for (auto it = lines.begin(); it != lines.end(); ++it)
	{
		vertices.push_back(it->first.x);
		vertices.push_back(it->first.y);
		vertices.push_back(it->first.z);
		vertices.push_back(it->second.getRed());
		vertices.push_back(it->second.getGreen());
		vertices.push_back(it->second.getBlue());
		vertices.push_back(it->second.getAlpha());
	}

	/*
	this._gizmosBatchRenderData.bind();
	this._gizmosBatchRenderData.vertexBuffer.bind();
    this._gizmosBatchRenderData.vertexBuffer.fillData(vertices);

    this._gizmosBatchProgram.use();
    this._gizmosBatchProgram.setMat4("u_matrix", this.camera);
	*/

	const int primitiveType = GL_LINES;
	const int offset = 0;
	const int count = lines.size();
	glDrawArrays(primitiveType, offset, count);
}
