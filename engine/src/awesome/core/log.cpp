#include <awesome/core/log.h>

#include <iostream>
#include <fstream>
#include <ctime>

#include <awesome/data/date_time.h>

namespace awesome
{
	Log* Log::m_Instance = nullptr;

	Log* Log::instance() {
		if (m_Instance == nullptr)
			m_Instance = new Log();
		return m_Instance;
	}

	Log& Log::get() {
		return *instance();
	}

	Log::Log() {
		m_Filter.flip();
	}

	void Log::setSeverityFilename(const LogSeverity severity, const std::string& filename) {
		auto it = m_SeverityFilenames.find(severity);
		if (it != m_SeverityFilenames.end()) {
			it->second = filename;
		}
		else m_SeverityFilenames.insert(std::pair<LogSeverity, std::string>{severity, filename});
	}

	void Log::resetFilter() {
		m_Filter.reset();
		m_Filter.flip();
	}

	bool Log::isValidLog(const LogSeverity severity) const { 
		return m_Filter.test(static_cast<uint8>(severity)); 
	}
	
	Log& Log::operator+= (const LogSeverity severity) {
		m_Filter.set(static_cast<uint8>(severity));
		return *this;
	}

	Log& Log::operator-= (const LogSeverity severity) {
		m_Filter.reset(static_cast<uint8>(severity));
		return *this;
	}

	void Log::log(const LogSeverity severity, const std::string& message) {
		if (!isValidLog(severity))
			return;

		std::string currentLog{ "[" + data::DateTime::now().toString() + "] " + message };
		switch (severity) {
		case LogSeverity::Warning:
		case LogSeverity::Error:
		case LogSeverity::Fatal:
			currentLog = currentLog + " (File: " + std::string{ __FILE__ } + ", Line: " + std::to_string(__LINE__) + ")";
			break;
		default:break;
		}
		
		if (m_WriteMode == LogWriteMode::FlushTime)
		{
			m_Messages.emplace_back(severity, currentLog);
		}
		else
		{
			auto filename = m_Filename;
			const auto it = m_SeverityFilenames.find(severity);
			if (it != m_SeverityFilenames.end())
				filename = it->second;

			std::ofstream file{ filename, std::ios_base::app };
			if (file.is_open()) {
				file << currentLog << std::endl;
			}
			file.close();
		}
		std::clog << currentLog << std::endl;
	}

	bool Log::flush() {
		std::ofstream file{ m_Filename, std::ios_base::app };
		auto opened = false;
		if (file.is_open()) { 
			opened = true;
			for (auto& m_Message : m_Messages)
			{
				auto severity = m_Message.first;
				auto& current_log = m_Message.second;

				if (isValidLog(severity))
				{
					auto severity_it = m_SeverityFilenames.find(severity);
					if (severity_it != m_SeverityFilenames.end()) {
						std::ofstream severity_file{ severity_it->second, std::ios_base::app };
						if (severity_file.is_open()) {
							severity_file << current_log << std::endl;
						}
						severity_file.close();
					}
					else file << current_log << std::endl;					
				}				
			}
		}
		file.close();

		m_Messages.clear();

		return opened;
	}

	void log(const LogSeverity severity, const std::string& message) {
		Log::instance()->log(severity, message);
	}
}

	