#pragma once

#include <dreamkeeper/core/interfaces/base_element.h>
#include <dreamkeeper/shading/shader.h>
#include <initializer_list>

namespace Dreamkeeper
{
	namespace Shading
	{
		class Program : public Core::BaseElement
		{
		private:
			Shader* vs = nullptr;
			Shader* fs = nullptr;
			Shader* gs = nullptr;
			bool compiled = false;

		public:
			Program();
			Program(std::initializer_list<Shader*> args);
			~Program();

			void linkShader(Shader* shader);
			void linkShaders(std::initializer_list<Shader*> shaders);

			bool compile();
			bool isCompiled() const { return compiled; }

			void use();

			void free(bool free_shaders_too = false);

			/* get uniform variable location */
			int getUniformLocation(const char* name);
			/* set uniforms */
			void setBool(const char* name, bool value);
			void setBool(int location, bool value);
			void setInt(const char* name, int value);
			void setInt(int location, int value);
			void setFloat(const char* name, float value);
			void setFloat(int location, float value);

		};
	}
}