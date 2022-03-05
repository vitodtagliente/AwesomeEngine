/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

namespace graphics
{
	class Shader
	{
	public:

		enum class Type
		{
			Vertex,
			Geometry,
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
			static bool load(const std::string& filename, std::string& source);
			// read different shader sources from the same file
			static bool parse(const std::string& content, std::map<Type, std::string>& sources);
		};

		Shader(Type type, const std::string& source);
		~Shader();

		void free();

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