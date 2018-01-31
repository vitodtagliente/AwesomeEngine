#pragma once

#include <awesome/rendering/shading/shader.h>
#include <initializer_list>

namespace Awesome
{
	namespace Rendering
	{
		class Program
		{
		private:
			Shader* vs = nullptr;
			Shader* fs = nullptr;
			Shader* gs = nullptr;
			ShaderStatus status{ ShaderStatus::Error };

		public:
			unsigned int id{ 0 };

			Program();
			Program(std::initializer_list<Shader*> args);
			~Program();

			void linkShader(Shader* shader);
			void linkShaders(std::initializer_list<Shader*> shaders);

			bool compile();
			ShaderStatus getStatus() const { return status; }

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