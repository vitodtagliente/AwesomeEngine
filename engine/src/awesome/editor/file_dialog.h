/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <string>

namespace editor
{
	class FileDialog
	{
	public:
		FileDialog() = default;

		inline bool isOpen() const { return m_open; }

		void open(const std::function<void(const std::filesystem::path&)>& handler);
		void render();

	private:
		bool m_open;
		std::function<void(const std::filesystem::path&)> m_handler;
		std::string m_filename;
	};
}