#pragma once

#include <string>

namespace Awesome
{
	enum class ShaderType
	{
		FragmentShader,
		GeometryShader,
		TesselationShader,
		VertexShader
	};

	enum class ShaderStatus
	{
		Compiled,
		Error
	};

	class Shader
	{
	private:
		ShaderType type{ ShaderType::VertexShader };
		ShaderStatus status{ ShaderStatus::Error };

		bool load_file(std::string filename, std::string& source);

	public:
		unsigned int id{ 0 };

		Shader(ShaderType type);
		~Shader();

		bool compile(std::string filename);

		ShaderType getType() const { return type; }
		ShaderStatus getStatus() const { return status; }

		static Shader* load(std::string filename, ShaderType type);

		void free();
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader() : Shader(ShaderType::VertexShader) {}
	};

	class FragmentShader : public Shader
	{
	public:
		FragmentShader() : Shader(ShaderType::FragmentShader) {}
	};

	class GeometryShader : public Shader
	{
	public:
		GeometryShader() : Shader(ShaderType::GeometryShader) {}
	};
}