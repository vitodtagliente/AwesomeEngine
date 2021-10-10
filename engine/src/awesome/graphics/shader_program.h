/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <map>
#include <string>

#include <vdtmath/matrix4.h>

namespace graphics
{
	class Shader;

	class ShaderProgram
	{
	public:

		enum class State
		{
			Unknown,
			Error,
			Linked
		};

		ShaderProgram(const std::initializer_list<Shader*>& shaders);
		~ShaderProgram();

		void bind();
		void unbind();
		void free();

		inline unsigned int id() const { return m_id; }
		inline State getState() const { return m_state; }
		inline const std::string& getErrorMessage() const { return m_errorMessage; }
		inline bool isValid() const { return m_id != 0; }

		// uniform setters
		void set(const std::string& name, bool value);
		void set(const std::string& name, int value);
		void set(const std::string& name, float value);
		void set(const std::string& name, const math::mat4& matrix);
		void set(const std::string& name, float f1, float f2, float f3, float f4);

	protected:

		// find the uniform layout location
		int getUniformLocation(const std::string& t_name) const;

		// program id
		unsigned int m_id;
		// state
		State m_state;
		// error message
		std::string m_errorMessage;

		// uniform locations
		mutable std::map<std::string, unsigned int> m_uniformLocations;
	};
}