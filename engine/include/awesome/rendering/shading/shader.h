#pragma once

#include <string>
#include <dreamkeeper/core/interfaces/base_element.h>
#include <glad/glad.h>

namespace Dreamkeeper
{
	namespace Shading
	{
		class Shader : public Core::BaseElement
		{
		private:
			GLenum type = 0;
			bool compiled = false;

			bool load_file(std::string filename, std::string& source);

		public:
			std::string name;

			Shader(GLenum type);
			Shader(GLenum type, std::string name);
			~Shader();

			bool compile(std::string filename);
			bool isCompiled() const { return compiled; }
			GLenum getType() const { return type; }

			bool isVertexShader() const { return type == GL_VERTEX_SHADER; }
			bool isFragmentShader() const { return type == GL_FRAGMENT_SHADER; }
			bool isGeometryShader() const { return type == GL_GEOMETRY_SHADER; }

			void free();
		};

		class VertexShader : public Shader
		{
		public:
			VertexShader() : Shader(GL_VERTEX_SHADER) {}
			VertexShader(std::string name) : Shader(GL_VERTEX_SHADER, name) {}
		};

		class FragmentShader : public Shader
		{
		public:
			FragmentShader() : Shader(GL_FRAGMENT_SHADER) {}
			FragmentShader(std::string name) : Shader(GL_FRAGMENT_SHADER, name) {}
		};

		class GeometryShader : public Shader
		{
		public:
			GeometryShader() : Shader(GL_GEOMETRY_SHADER) {}
			GeometryShader(std::string name) : Shader(GL_GEOMETRY_SHADER, name) {}
		};
	}
}