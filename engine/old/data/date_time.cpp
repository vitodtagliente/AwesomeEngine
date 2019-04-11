#include <awesome/data/date_time.h>
#include <awesome/data/string.h>
#include <awesome/platform.h>
#include <ctime>

namespace awesome
{
	namespace data
	{
		Date::Date() {
			year = static_cast<uint32>(1900);
			month = static_cast<uint8>(1);
			day = static_cast<uint8>(1);
		}

		Date::Date(const std::string& str) {
			if(String::contains(str, "/"))
			{
				
			}
			else
			{
				
			}
		}

		Date::Date(const Date& date)
		{
			year = date.year;
			month = date.month;
			day = date.day;
		}
		
		bool Date::operator== (const Date& date) const {
			return year == date.year && month == date.month && day == date.day;
		}

		bool Date::operator!= (const Date& date) const {
			return year != date.year || month != date.month || day != date.day;
		}

		void Date::validate() {
			if (month == 0) month = 1;
			else if (month > 12) month = 12;

			if (day == 0) day = 1;
			uint8 month_days = 31;
			switch (static_cast<Month>(month)) {
			case April:
			case June:
			case September:
			case November:
				month_days = 30;
				break;
			case February:
				month_days = 28;
				// is it a leap year?
				if (year % 4 == 0 || (year % 400 != 0 && year % 100 == 0))
					month_days = 29;
				break;
			default: break;
			}
			if (day > month_days) day = month_days;
		}

		std::string Date::toString() const {
			return std::to_string(day) + " " + monthToString(month) + " " + std::to_string(year);
		}

		std::string Date::toShortString() const {
			return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
		}

		Date Date::today() {
			auto now = time(nullptr);
			struct tm time_data{};
#ifdef PLATFORM_WINDOWS
			// localtime may be deprecated on windows
			localtime_s(&time_data, &now);
#else
			time_data = *localtime(&now);
#endif

			Date date;
			date.year = static_cast<uint32>(1900) + static_cast<uint32>(time_data.tm_year);
			date.month = 1 + static_cast<uint8>(time_data.tm_mon);
			date.day = static_cast<uint8>(time_data.tm_mday);
			return date;
		}

		std::string Date::monthToString(const Month month) {
			switch (month) {
			case Jenuary:return std::string{ "Jenuary" }; break;
			case February:return std::string{ "February" }; break;
			case March:return std::string{ "March" }; break;
			case April:return std::string{ "April" }; break;
			case May:return std::string{ "May" }; break;
			case June:return std::string{ "June" }; break;
			case July:return std::string{ "July" }; break;
			case August:return std::string{ "August" }; break;
			case September:return std::string{ "September" }; break;
			case October:return std::string{ "October" }; break;
			case November:return std::string{ "November" }; break;
			case December:return std::string{ "December" }; break;
			default:return std::string{}; break;
			}
		}

		std::string Date::monthToString(const uint8 month) {
			return monthToString(static_cast<Month>(month));
		}


		Month Date::stringToMonth(const std::string& str) {
			const std::string month_str = String::lower(String::trim(str));
			if (month_str == "jenuary")return Month::Jenuary;
			else if (month_str == "february")return Month::February;
			else if (month_str == "march")return Month::March;
			else if (month_str == "april")return Month::April;
			else if (month_str == "may")return Month::May;
			else if (month_str == "june")return Month::June;
			else if (month_str == "july")return Month::July;
			else if (month_str == "august")return Month::August;
			else if (month_str == "september")return Month::September;
			else if (month_str == "october")return Month::October;
			else if (month_str == "november")return Month::November;
			else if (month_str == "december")return Month::December;
			else return Month::Jenuary;
		}

		// Time

		Time::Time() {
			hour = static_cast<uint8>(0);
			min = static_cast<uint8>(0);
			sec = static_cast<uint8>(0);
		}

		Time::Time(const std::string& str) {
			// TODO: parse from string
		}

		Time::Time(const Time& time)
		{
			hour = time.hour;
			min = time.min;
			sec = time.sec;
		}

		bool Time::operator== (const Time& time) const {
			return hour == time.hour && min == time.min && sec == time.sec;
		}

		bool Time::operator!= (const Time& time) const {
			return hour != time.hour || min != time.min || sec != time.sec;
		}

		void Time::validate() {
			if (hour > 59)hour = 0;
			if (min > 59)min = 0;
			if (sec > 59)sec = 0;
		}

		std::string Time::toString() const {
			const auto str_hour = (hour == 0) ? "00" : std::to_string(hour);
			const auto str_min = (min == 0) ? "00" : std::to_string(min);
			const auto str_sec = (sec == 0) ? "00" : std::to_string(sec);
			return str_hour + ":" + str_min + ":" + str_sec;
		}

		std::string Time::toShortString() const {
			const auto str_hour = (hour == 0) ? "00" : std::to_string(hour);
			const auto str_min = (min == 0) ? "00" : std::to_string(min);
			return str_hour + ":" + str_min;
		}

		Time Time::now() {
			auto now = time(nullptr);
			struct tm time_data {};
#ifdef PLATFORM_WINDOWS
			// localtime may be deprecated on windows
			localtime_s(&time_data, &now);
#else
			time_data = *localtime(&now);
#endif

			Time time;
			time.hour = static_cast<uint8>(time_data.tm_hour);
			time.min = static_cast<uint8>(time_data.tm_min);
			time.sec = static_cast<uint8>(time_data.tm_sec);
			return time;
		}

		// Date Time

		DateTime::DateTime() = default;

		DateTime::DateTime(const std::string& str) {
			// TODO: parse from string
		}

		DateTime::DateTime(const DateTime& date_time)
		{
			date = date_time.date;
			time = date_time.time;
		}

		DateTime& DateTime::operator= (const DateTime& date_time) = default;

		bool DateTime::operator== (const DateTime& date_time) const {
			return date == date_time.date && time == date_time.time;
		}

		bool DateTime::operator!= (const DateTime& date_time) const {
			return date != date_time.date || time != date_time.time;
		}

		void DateTime::validate() {
			date.validate();
			time.validate();
		}

		std::string DateTime::toString() const {
			return date.toString() + " " + time.toString();
		}

		std::string DateTime::toShortString() const {
			return date.toShortString() + " " + time.toShortString();
		}

		DateTime DateTime::now() {
			DateTime date_time;
			date_time.date = Date::today();
			date_time.time = Time::now();
			return date_time;
		}
	}
}