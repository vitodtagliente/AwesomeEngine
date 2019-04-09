#pragma once

#include <bitset>
#include <map>
#include <string>
#include <vector>
#include "../types.h"

namespace awesome
{
	// log severities
	enum class LogSeverity : uint8
	{
		Log = 1,
		Warning,
		Error,
		Fatal,
		Engine,
		Game
	};

	// when log data should be written on file?
	enum LogWriteMode
	{
		// each time there is a log
		LogTime,
		// only when the flush function is called
		FlushTime
	};

	class Log
	{
	private:

		static Log* m_Instance;

		// messages
		std::vector<std::pair<LogSeverity, std::string>> m_Messages{};

		// default file
		std::string m_Filename{ "log.txt" };
		// file per log severity
		std::map<LogSeverity, std::string> m_SeverityFilenames{};

		// write mode
		LogWriteMode m_WriteMode{ LogWriteMode::FlushTime };

		// filter, used to specify which log display and which ones no
		std::bitset<256> m_Filter{};

		Log();
		~Log() = default;

	public:

		// get the instance
		static Log* instance();
		static Log& get();
		// delete the instance
		static inline void free() { delete m_Instance; }

		Log& operator=(Log&& log) = default;
		Log(const Log& log) = default;
		Log(Log&& log) = default;
		Log& operator= (const Log& log) = default;

		// set the default filename
		inline void setFilename(const std::string& filename) { m_Filename = filename; }
		// set the filename per log severity
		void setSeverityFilename(const LogSeverity severity, const std::string& filename);

		// filter management
		void resetFilter();
		bool isValidLog(const LogSeverity severity) const;
		Log& operator+= (const LogSeverity severity); 
		Log& operator-= (const LogSeverity severity);

		// set write mode
		inline void setWriteMode(const LogWriteMode mode) { m_WriteMode = mode; }

		// log a message
		void log(const LogSeverity severity, const std::string& message);
		// save to file and clear
		bool flush();

	};

	void log(const LogSeverity severity, const std::string& message);
}