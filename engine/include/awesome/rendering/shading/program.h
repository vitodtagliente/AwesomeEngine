#pragma once

#include <awesome/rendering/shading/shader.h>
#include <initializer_list>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

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
			void setBool(const char* name, const bool value);
			void setBool(const int location, const bool value);
			void setInt(const char* name, const int value);
			void setInt(const int location, const int value);
			void setFloat(const char* name, const float value);
			void setFloat(const int location, const float value);

			void setVec3(const char* name, const glm::vec3& value);
			void setVec3(const int location, const glm::vec3& value);
			void setVec4(const char* name, const glm::vec4& value);
			void setVec4(const int location, const glm::vec4& value);
			void setMat4(const char* name, const glm::mat4& value);
			void setMat4(const int location, const glm::mat4& value);

		};
	}
}