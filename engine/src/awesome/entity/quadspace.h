/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/entity/entity.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

namespace graphics
{
	class Renderer2D;
}

class Quadspace
{
public:

	struct Settings
	{
		int bounds{ 100 };
	};

	Quadspace() = default;

	void clear();
	void insert(Entity* const entity);
	std::vector<Entity*> retrieve(Entity* const entity) const;
	std::size_t size() const { return m_spaces.size(); }

	void render(graphics::Renderer2D* const renderer);

	Settings settings;

private:
	void insertNewSpace(Entity* const entity);
	int getIndex(const math::vec3& position) const;

	struct Space
	{
		Space() = default;

		std::vector<Entity*> entities;
		math::vec3 position;
		int bounds{ 0 };

		void clear();
	};

	std::vector<Space> m_spaces;
};