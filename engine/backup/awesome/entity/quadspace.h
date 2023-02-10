/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/entity/entity.h>
#include <awesome/graphics/color.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

class Quadspace
{
public:

	struct Settings
	{
		int bounds{ 100 };
	};

	Quadspace() = default;

	void clear();
	void insert(Entity* const entity, int bounds);
	std::vector<Entity*> retrieve(Entity* const entity) const;
	std::size_t size() const { return m_spaces.size(); }

	void render(class graphics::Renderer* const renderer, const graphics::Color& wireframesColor);

	Settings settings;

private:
	void insertNewSpace(Entity* const entity, int bounds);
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