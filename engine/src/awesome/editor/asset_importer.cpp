#include "asset_importer.h"

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>

namespace editor
{
	std::map<Asset::Type, std::set<std::string>> AssetImporter::s_filetypes{
		{ Asset::Type::Image, {".png", ".jpg", ".jpeg", ".bmp"}},
		{ Asset::Type::Text, {".txt", ".md", ".shader", ".ini", ".cfg"}}
	};

	AssetImporter::AssetImporter()
	{

	}

	void AssetImporter::import(const std::string& directory, const bool recursive)
	{
		import(std::filesystem::path(directory), recursive);
	}

	void AssetImporter::import(const std::filesystem::path& directory, bool recursive)
	{
		for (const auto& entry : std::filesystem::directory_iterator(directory))
		{
			if (entry.is_directory() && recursive)
			{
				import(entry.path(), recursive);
				continue;
			}

			const std::filesystem::path& file = entry.path();
			import(file);
		}
	}

	bool AssetImporter::import(const std::string& filename)
	{
		return import(std::filesystem::path(filename));
	}

	bool AssetImporter::import(const std::filesystem::path& filename)
	{
		if (!std::filesystem::exists(filename) || std::filesystem::is_directory(filename))
		{
			return false;
		}

		if (Asset::isAsset(filename))
		{
			Asset descriptor = Asset::load(filename.string());
			if (descriptor)
			{
				AssetLibrary::instance()->redirectors.insert(std::make_pair(descriptor.id, filename.string()));
				return true;
			}
			return false;
		}

		const std::string assetFilename = filename.string() + Asset::Extension;
		if (std::filesystem::exists(assetFilename))
		{
			return true;
		}

		const Asset::Type type = getTypeByExtension(filename.extension().string());
		if (type != Asset::Type::None)
		{
			Archive archive(assetFilename, Archive::Mode::Write);
			Asset asset(type);
			archive << json::Serializer::to_string(asset.serialize());

			AssetLibrary::instance()->redirectors.insert(std::make_pair(asset.id, assetFilename));
		}

		return true;
	}

	Asset::Type AssetImporter::getTypeByExtension(const std::string& ext) const
	{
		for (const auto& pair : s_filetypes)
		{
			if (pair.second.find(ext) != pair.second.end())
			{
				return pair.first;
			}
		}
		return Asset::Type::None;
	}
}