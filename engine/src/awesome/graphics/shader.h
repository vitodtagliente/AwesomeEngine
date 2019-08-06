#pragma once

#include <map>
#include <string>

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
			static bool parse(const std::string& t_content, std::map<Type, std::string>& t_sources);
		};

		Shader(const Type t_type, const std::string& t_source);

		inline unsigned int id() const { return m_id; }
		inline Type getType() const { return m_type; }
		inline State getState() const { return m_state; }
		inline const std::string& getErrorMessage() const { return m_errorMessage; }
		inline bool isValid() const { return m_id != 0; }

	protected:

		// shader id
		unsigned int m_id;
		// shader type
		Type m_type;
		// shader state
		State m_state;
		// store compile errors
		std::string m_errorMessage;
	};
}