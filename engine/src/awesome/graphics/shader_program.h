/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <initializer_list>
#include <map>
#include <string>

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

	virtual void bind() = 0;
	virtual void unbind() = 0;

	inline unsigned int id() const { return m_id; }
	inline State getState() const { return m_state; }
	inline const std::string& getErrorMessage() const { return m_errorMessage; }
	inline bool isValid() const { return m_id != 0; }

	// uniform setters
	virtual void set(const std::string& name, const bool value) = 0;
	virtual void set(const std::string& name, const int value) = 0;
	virtual void set(const std::string& name, const float value) = 0;
	virtual void set(const std::string& name, const float* const matrix) = 0;
	virtual void set(const std::string& name, const float f1, const float f2, const float f3, const float f4) = 0;

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