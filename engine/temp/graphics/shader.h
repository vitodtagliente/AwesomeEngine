#pragma once 

#include <map>
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
			Error,
			Unloaded
		};

		class Reader final
		{
		public:
			// read the file content
			static bool load(const std::string& t_filename, std::string& t_source);
			// read different shader sources from the same file
			static bool parse(const std::string& t_filename, std::map<Type, std::string>& t_sources);
		};

		Shader(const Type t_type, const std::string& t_source);
		~Shader();

		uint getId() const;
		Type getType() const;
		State getState() const;
		const std::string& getErrorMessage() const;
		bool isValid() const;

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
}