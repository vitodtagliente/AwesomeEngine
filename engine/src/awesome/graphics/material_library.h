#pragma once 

#include <map>
#include <string>
#include <vector>

namespace awesome
{
	class Material;
	class Shader;
	class ShaderProgram;
	class GraphicsModule;

	class MaterialLibrary final
	{
	public:

		MaterialLibrary(GraphicsModule* const t_graphicsModule);
		~MaterialLibrary();

		void clear();

		Material* const getMaterial(const std::string t_name) const;
		Shader* const getShader(const std::string& t_name) const;
		ShaderProgram* const getShaderProgram(const std::string& t_name) const;

		// load materials in folder
		unsigned int loadMaterials(const std::string& t_path);

	private:

		GraphicsModule* m_graphics;
		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;
		std::map<std::string, ShaderProgram*> m_programs;

	};
}