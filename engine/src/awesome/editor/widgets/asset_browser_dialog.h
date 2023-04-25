/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>

#include <awesome/asset/asset.h>
#include <awesome/asset/asset_database.h>

class AssetBrowserDialog
{
public:
	AssetBrowserDialog() = default;
	virtual ~AssetBrowserDialog() = default;

	inline bool isOpen() const { return m_open; }

	void close();
	void open(const std::string& id, int type, const std::function<void(const AssetRecord&)>& handler);
	void render(const std::string& id);

private:
	std::string m_filter;
	std::function<void(const AssetRecord&)> m_handler;
	std::string m_id;
	bool m_open{ false };
	const AssetRecord* m_selectedAsset{ nullptr };
	int m_type{ AssetType_Invalid };
};