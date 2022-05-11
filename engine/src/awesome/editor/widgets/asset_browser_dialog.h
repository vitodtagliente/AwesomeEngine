/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>

#include <awesome/asset/asset.h>

namespace editor
{
	class AssetBrowserDialog
	{
	public:
		AssetBrowserDialog();

		inline bool isOpen() const { return m_open; }

		void close();
		void open(Asset::Type type, const std::function<void(const AssetPtr&)>& handler);
		void render();

	private:
		std::string m_filter;
		std::function<void(const AssetPtr&)> m_handler;
		bool m_open;
		AssetPtr m_selectedAsset;
		std::string m_title;
		Asset::Type m_type;
	};
}