/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <set>
#include <string>

#include <awesome/data/asset.h>

namespace editor
{
	class AssetImporter
	{
	public:
		AssetImporter();

		void import(const std::filesystem::path& directory, bool recursive);
		bool import(const std::filesystem::path& filename);

	private:
		Asset::Type getTypeByExtension(const std::string& ext) const;

		static std::map<Asset::Type, std::set<std::string>> s_filetypes;
	};
}