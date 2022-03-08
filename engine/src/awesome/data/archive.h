/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <fstream>
#include <string>
#include <variant>

class Archive
{
public:

	enum class Mode
	{
		Read,
		Write
	};

	Archive(const std::string& filename, Mode mode);
	~Archive();

	template <typename T>
	Archive& operator<< (const T value)
	{
		if (m_mode == Mode::Write && m_file.is_open())
		{
			m_file << value;
		}
		return *this;
	}

	template <typename T>
	Archive& operator>> (T& value)
	{
		if (m_mode == Mode::Read && m_file.is_open())
		{
			m_file >> value;
		}
		return *this;
	}

	void close();

private:
	std::string m_filename;
	Mode m_mode;
	std::fstream m_file;
};