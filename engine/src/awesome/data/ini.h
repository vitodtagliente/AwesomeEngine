#pragma once

#include <map>
#include <string>

namespace awesome
{
	class FileINI final
	{
	public:

		class Section final
		{
		public:

			Section()
				: m_name()
				, m_data()
			{}

			Section(const std::string& t_name)
				: m_name(t_name)
				, m_data()
			{

			}

			// retrieve section name
			inline const std::string& getName() const { return m_name; }
			// retrieve section data
			inline const std::map<std::string, std::string>& getData() const { return m_data; }

			bool contains(const std::string& t_key) const;
			std::string get(const std::string& t_key) const;
			void set(const std::string& t_key, const std::string& t_value);
			void remove(const std::string& t_key);

			std::string to_string() const;

		private:

			// section name
			std::string m_name;
			// section data
			std::map<std::string, std::string> m_data;
		};

		class Reader
		{
			Reader() = delete;

			static FileINI parse(const std::string& t_filename);
		};

		FileINI();

		bool hasSection(const std::string& t_name) const;
		Section& getSection(const std::string& t_name);

	private:

		std::map<std::string, Section> m_sections;
	};
}