/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

namespace editor
{
	struct TextIcon final
	{
		TextIcon() = delete;
		
		static std::string copy(const std::string& name = "");
		static std::string cube(const std::string& name = "");
		static std::string eraser(const std::string& name = "");
		static std::string file(const std::string& name = "");
		static std::string folder(const std::string& name = "");
		static std::string horse(const std::string& name = "");
		static std::string image(const std::string& name = "");
		static std::string minus(const std::string& name = "");
		static std::string music(const std::string& name = "");
		static std::string paste(const std::string& name = "");
		static std::string pause(const std::string& name = "");
		static std::string play(const std::string& name = "");
		static std::string plus(const std::string& name = "");
		static std::string save(const std::string& name = "");
		static std::string search(const std::string& name = "");
		static std::string stop(const std::string& name = "");
		static std::string tree(const std::string& name = "");
		static std::string upload(const std::string& name = "");
		static std::string video(const std::string& name = "");
	};
}