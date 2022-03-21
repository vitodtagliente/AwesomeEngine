/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <set>
#include <string>

#include <awesome/data/asset.h>

namespace editor
{
	class AssetImporter
	{
	public:
		AssetImporter();

		void import(const std::string& directory, bool recursive);

	private:
		Asset::Type getTypeByExtension(const std::string& ext) const;

		static std::map<Asset::Type, std::set<std::string>> s_filetypes;
	};
}