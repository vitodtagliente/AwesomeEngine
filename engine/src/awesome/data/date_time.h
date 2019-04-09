#pragma once

#include <string>
#include "../types.h"

/*
Date Time implementation
*/

namespace awesome
{
	namespace data
	{
		enum Month : uint8
		{
			Jenuary = 1,
			February,
			March,
			April,
			May,
			June,
			July,
			August,
			September,
			October,
			November,
			December
		};

		struct Date
		{
			Date();
			Date(const std::string& str);
			~Date() = default;
						
			uint32 year{};
			uint8 month{}, day{};

			Date& operator=(Date&& date) = default;
			Date(const Date& date);
			Date(Date&& date) = default;

			Date& operator= (const Date& date) = default;

			inline Month getMonth() const { return static_cast<Month>(month); }

			bool operator== (const Date& date) const;
			bool operator!= (const Date& date) const;

			void validate();

			std::string toString() const;
			std::string toShortString() const;

			static Date today();

			static std::string monthToString(const Month month);
			static std::string monthToString(const uint8 month);
			static Month stringToMonth(const std::string& str);
		};

		struct Time
		{
			Time();
			Time(const std::string& str);
			~Time() = default;

			uint8 hour{}, min{}, sec{};

			Time& operator=(Time&& time) = default;
			Time(const Time& time);
			Time(Time&& time) = default;

			Time& operator= (const Time& date) = default;

			bool operator== (const Time& time) const;
			bool operator!= (const Time& time) const;

			void validate();

			std::string toString() const;
			std::string toShortString() const;

			static Time now();
		};

		struct DateTime
		{
			DateTime();
			DateTime(const std::string& str);
			~DateTime() = default;

			Date date{};
			Time time{};

			DateTime& operator=(DateTime&& date_time) = default;
			DateTime(const DateTime& date_time);
			DateTime(DateTime&& date_time) = default;

			DateTime& operator= (const DateTime& date_time);

			bool operator== (const DateTime& date_time) const;
			bool operator!= (const DateTime& date_time) const;

			void validate();

			std::string toString() const;
			std::string toShortString() const;

			static DateTime now();
		};
	}
}