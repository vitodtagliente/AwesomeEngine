/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <fstream>
#include <string>
#include <variant>

enum class ArchiveMode
{
	Read,
	Write
};

class Archive
{
public:
	Archive(const std::string& filename, ArchiveMode mode);
	~Archive();

	template <typename T>
	Archive& operator<< (const T value)
	{
		if (m_mode == ArchiveMode::Write && m_file.is_open())
		{
			m_file << value;
		}
		return *this;
	}

	template <typename T>
	Archive& operator>> (T& value)
	{
		if (m_mode == ArchiveMode::Read && m_file.is_open())
		{
			m_file >> value;
		}
		return *this;
	}

	void close();

private:
	std::string m_filename;
	ArchiveMode m_mode;
	std::fstream m_file;
};