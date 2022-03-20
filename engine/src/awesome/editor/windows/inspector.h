/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/entity/entity.h>

#include "../file.h"
#include "../window.h"

namespace editor
{
	class Context;

	class Inspector : public Window
	{
	public:
		Inspector();

		void render(Context& context) override;

		REFLECT()

	private:
		void inspect(Context& context, Entity* const entity);
		void inspect(Context& context, const File& file);

		std::string m_prefabFilename;
	};
}