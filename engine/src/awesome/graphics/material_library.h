#pragma once 

#include <map>
#include <string>
#include <vector>

namespace awesome
{
	class Material;
	class Shader;
	class ShaderProgram;

	class MaterialLibrary final
	{
	public:

		MaterialLibrary();
		~MaterialLibrary();

		void clear();

		Material* const getMaterial(const std::string t_name) const;
		Shader* const getShader(const std::string& t_name) const;
		ShaderProgram* const getShaderProgram(const std::string& t_name) const;

		// some default material names
		static const std::string DefaultSpriteMaterialName;

	private:

		void generateDefaultMaterials();

		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;
		std::map<std::string, ShaderProgram*> m_programs;

	};
}