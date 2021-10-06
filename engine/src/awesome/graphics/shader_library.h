/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

class ShaderLibrary
{
public:
	ShaderLibrary();

	const std::map<std::string, std::string>& getShaders() const { return m_shaders; }

	struct names
	{
		names() = delete;

		static const std::string GizmosShader;
	};

private:
	std::map<std::string, std::string> m_shaders;
};