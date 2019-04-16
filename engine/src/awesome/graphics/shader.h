#pragma once 

#include <fstream>
#include <string>
#include "../types.h"

namespace awesome
{
	class Shader
	{
	public:

		enum class Type
		{
			Vertex,
			Fragment
		};

		enum class State
		{
			Unknown,
			Compiled,
			Error
		};

		Shader(const Type t_type, const std::string& t_source);
		~Shader();

		uint getId() const;
		Type getType() const;
		State getState() const;
		const std::string& getErrorMessage() const;


	private:

		// shader id
		uint m_id;
		// shader type
		Type m_type;
		// shader state
		State m_state;
		// store compile errors
		std::string m_errorMessage;
	};
	/*
	class VertexShader final
	{
	public:
		VertexShader(const std::string& t_source);
	};

	class FragmentShader final
	{
	public:
		FragmentShader(const std::string& t_source);
	};
	*/
}