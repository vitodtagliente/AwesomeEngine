#pragma once

#include <map>
#include <string>

namespace awesome
{
	class IniData final
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
			{}

			// retrieve section name
			inline const std::string& getName() const { return m_name; }
			// retrieve section data
			inline const std::map<std::string, std::string>& getData() const { return m_data; }

			bool contains(const std::string& t_key) const;
			std::string get(const std::string& t_key) const;
			const std::string& get(const std::string& t_key, const std::string& t_default) const;
			void set(const std::string& t_key, const std::string& t_value);
			void remove(const std::string& t_key);

			std::string toString() const;

		private:

			// section name
			std::string m_name;
			// section data
			std::map<std::string, std::string> m_data;
		};

		IniData()
			: m_sections()
		{}

		bool hasSection(const std::string& t_name) const;
		Section& getSection(const std::string& t_name);
		void addSection(const Section& t_section);

		inline const std::map<std::string, Section>& getSections() const { return m_sections; }

		std::string toString() const;

		static IniData parse(const std::string& t_content);

	private:

		// sections collection
		std::map<std::string, Section> m_sections;
	};
}