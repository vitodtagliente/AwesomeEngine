#pragma once

#include <string>

namespace Awesome
{
	namespace Rendering
	{
		enum ShaderType
		{
			FragmentShader,
			GeometryShader,
			TesselationShader,
			VertexShader
		};

		enum ShaderStatus
		{
			Error,
			Compiled
		};

		class Shader
		{
		private:
			ShaderType type{ ShaderType::VertexShader };
			bool compiled{ false };

			bool load_file(std::string filename, std::string& source);

		public:
			std::string name;

			Shader(ShaderType type);
			Shader(ShaderType type, std::string name);
			~Shader();

			bool compile(std::string filename);
			bool isCompiled() const { return compiled; }

			ShaderType getType() const { return type; }

			static Shader* load(std::string filename, ShaderType type);

			void free();
		};

		class VertexShader : public Shader
		{
		public:
			VertexShader() : Shader(ShaderType::VertexShader) {}
			VertexShader(std::string name) : Shader(ShaderType::VertexShader, name) {}
		};

		class FragmentShader : public Shader
		{
		public:
			FragmentShader() : Shader(ShaderType::FragmentShader) {}
			FragmentShader(std::string name) : Shader(ShaderType::FragmentShader, name) {}
		};

		class GeometryShader : public Shader
		{
		public:
			GeometryShader() : Shader(ShaderType::GeometryShader) {}
			GeometryShader(std::string name) : Shader(ShaderType::GeometryShader, name) {}
		};
	}
}