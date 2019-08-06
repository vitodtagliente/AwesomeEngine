#pragma once 

#include <map>
#include <string>
#include <vector>

namespace awesome
{
	class Material;
	class Shader;
	class ShaderProgram;
	class GraphicsAPI;

	class MaterialLibrary final
	{
	public:

		MaterialLibrary(GraphicsAPI* const t_api);
		~MaterialLibrary();

		void clear();

		Material* const getMaterial(const std::string t_name) const;
		Shader* const getShader(const std::string& t_name) const;
		ShaderProgram* const getShaderProgram(const std::string& t_name) const;

		// load materials in folder
		unsigned int loadMaterials(const std::string& t_path);
		unsigned int loadShaders(const std::string& t_path);

		bool add(const std::string& t_name, Material* const t_material);
		bool add(const std::string& t_name, Shader* const t_shader);
		bool add(const std::string& t_name, ShaderProgram* const t_program);

		// retrieve a material
		Material* const get(const std::string& t_name) const;

		const std::map<std::string, Material*>& getMaterials() const { return m_materials; }
		const std::map<std::string, Shader*>& getShaders() const { return m_shaders; }
		const std::map<std::string, ShaderProgram*>& getPrograms() const { return m_programs; }

	private:

		GraphicsAPI* m_api;
		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;
		std::map<std::string, ShaderProgram*> m_programs;

	};
}