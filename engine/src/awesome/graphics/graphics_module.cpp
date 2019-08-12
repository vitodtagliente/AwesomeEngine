#include "graphics_module.h"

#include <vector>
#include "graphics_api.h"
#include "renderer.h"
#include "components/rendering_component.h"
#include "../scene/world.h"
#include "../scene/object.h"
#include "shaders.h"
#include "shader.h"
#include "shader_program.h"
#include "material.h"
#include "material_library.h"

namespace awesome
{
	GraphicsModule::GraphicsModule()
		: m_api()
		, m_renderer()
	{
	}

	GraphicsModule::~GraphicsModule()
	{
	}

	bool GraphicsModule::startup_implementation()
	{
		m_api = createAPI();
		if (m_api->startup())
		{
			m_renderer = createRenderer(m_api);
			if (m_renderer != nullptr)
			{
				initializeDefaultMaterials();
				return true;
			}
		}
		return false;
	}
	
	void GraphicsModule::shutdown_implementation()
	{
		m_api->shutdown();
	}
	
	void GraphicsModule::update_implementation()
	{
	}

	void GraphicsModule::pre_rendering_implementation()
	{
		for (Object* const object : World::instance()->getObjects())
		{
			for (RenderingComponent* rendering_component : object->getComponents<RenderingComponent>())
			{
				rendering_component->push_data(m_renderer);
			}
		}
	}

	void GraphicsModule::render_implementation()
	{
		m_renderer->render();
	}

	void GraphicsModule::post_rendering_implementation()
	{
	}

	void GraphicsModule::initializeDefaultMaterials()
	{
		for (const std::pair<std::string, std::string>& shader : getDefaultShaderSources())
		{
			std::map<Shader::Type, std::string> sources;
			Shader::Reader::parse(shader.second, sources);
			// create shaders
			auto vertex = m_api->createShader(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
			auto fragment = m_api->createShader(Shader::Type::Fragment, sources[Shader::Type::Fragment]);
			auto program = m_api->createShaderProgram({ vertex, fragment });

			// free shaders
			delete vertex;
			delete fragment;

			if (program->getState() == ShaderProgram::State::Linked)
			{
				Material* const material = new Material(program);
				m_renderer->getMaterialLibrary()->add(shader.first, material);
			}
			else
			{
				delete program;
			}
		}
	}
}