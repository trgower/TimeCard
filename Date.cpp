/*******************************************************************************
 * Date.cpp
 *
 * Tanner Gower
 * 1/12/2016
 * Project 2: IncomeXpense
 *
 * A Date object that stores a date and does certain calculations.
 *
*******************************************************************************/

#include "Date.h"
#include <ctime>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

const int DATE_STRING_LENGTH = 10,
          DAYS_IN_WEEK = 7,
          DAYS_IN_YEAR = 365;
const int DAYS_IN_MONTHS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
                                 31 };
const string Date::DAYS_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri",
                                     "Sat"};
const string Date::MONTHS[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                               "Aug", "Sep", "Oct", "Nov", "Dec"};

// ------------------------------------------------------------------------
// Date: Creates a Date object that stores the current date
// ------------------------------------------------------------------------
Date::Date()
{
  time_t now = time(0);
  tm *local_time = localtime(&now);
  day_in_month = local_time->tm_mday;
  day_in_year = local_time->tm_yday + 1;
  month_in_year = local_time->tm_mon + 1; // tm_mon is from 0-11
  year = local_time->tm_year + 1900;
}

// ------------------------------------------------------------------------
// Date: Creates a Date object with the date dd-mm-yyyy
// ------------------------------------------------------------------------
Date::Date(int m, int d, int y)
{
  day_in_month = d;
  month_in_year = m;
  year = y;
  day_in_year = calcDayInYear();
}

// ------------------------------------------------------------------------
// Date: Destroys the object
// ------------------------------------------------------------------------
Date::~Date() {

}

// ------------------------------------------------------------------------
// getFormattedDate: Returns the date formatted as the string in parameter.
//                   The string must include two -, d and m's, and 4 y's.
//                   Pass in any format, ex: yyyy-dd-mm or mm-dd-yyyy
//                   Does not change formatted_date member variable
//                   You should rewrite this because it sucks
// format: The desired format, ex: yyyy-dd-mm or mm-dd-yyyy
// ------------------------------------------------------------------------
string Date::getFormattedDate(string format) const
{
  string f_date = "ERROR";

  if (format.length() == DATE_STRING_LENGTH)
  {
    stringstream ss;
    int num_skip = 0;
    int before_add = 0;
    char curr;

    int i = 0;
    while (i < format.length())
    {
      curr = format.at(i);

      switch (curr)
      {
        case '-':
          ss << "-";
          i++;
          break;

        case 'd':
          before_add = ss.str().length();
          if (day_in_month < 10)
            ss << "0";

          ss << day_in_month;
          num_skip = ss.str().length() - before_add;
          i += num_skip;
          break;

        case 'm':
          before_add = ss.str().length();
          if (month_in_year < 10)
            ss << "0";

          ss << month_in_year;
          num_skip = ss.str().length() - before_add;
          i += num_skip;
          break;

        case 'y':
          before_add = ss.str().length();
          if (year < 1000)
            ss << "0";
          if (year < 100)
            ss << "0";
          if (year < 10)
            ss << "0";

          ss << year;
          num_skip = ss.str().length() - before_add;
          i += num_skip;
          break;
      }
    }
    f_date = ss.str();
  }
  return f_date;
}

// ------------------------------------------------------------------------
// Accessors: returns member variables AND MORE
// ------------------------------------------------------------------------
int Date::getDayInMonth() const { return day_in_month; }
int Date::getDayInYear() const { return day_in_year; }
int Date::getWeekInYear() const { return day_in_year / DAYS_IN_WEEK; }
int Date::getMonthInYear() const { return month_in_year; }
int Date::getYear() const { return year; }
string Date::getFormattedDate() {
  if (formatted_date == "")
    formatted_date = getFormattedDate("mm-dd-yyyy");
  return formatted_date;
}

// ------------------------------------------------------------------------
// isLeapYear: checks if stored year is a leap year
// returns a bool
// ------------------------------------------------------------------------
bool Date::isLeapYear() const { return isLeapYear(year); }

// ------------------------------------------------------------------------
// isLeapYear: checks if stored year is a leap year
// check_year: year in question
// returns a bool
// ------------------------------------------------------------------------
bool Date::isLeapYear(int check_year) const
{
  if (check_year % 4 == 0)
    if (check_year % 100 == 0)
      if (check_year % 400 == 0)
        return true;
      else
        return false;
    else
      return true;
  else
    return false;
}

// ------------------------------------------------------------------------
// calcDayInYear: calculates the day in year based on the date
// returns an int
// ------------------------------------------------------------------------
int Date::calcDayInYear() const
{
  int day = 0;
  for (int i = 0; i < (month_in_year-1); i++)
    day += DAYS_IN_MONTHS[i];
  day += day_in_month;
  if (month_in_year == 3 && isLeapYear())
    day++;
  return day;
}

// ------------------------------------------------------------------------
// > Operator: returns false if rhs is further in the future
// returns a bool
// ------------------------------------------------------------------------
bool Date::operator>(const Date &rhs) const
{
  if (year == rhs.getYear())
    return day_in_year > rhs.getDayInYear();
  else
    return year > rhs.getYear();
}

// ------------------------------------------------------------------------
// < Operator: returns true if rhs is further in the future
// returns a bool
// ------------------------------------------------------------------------
bool Date::operator<(const Date &rhs) const
{
  if (year == rhs.getYear())
    return day_in_year < rhs.getDayInYear();
  else
    return year < rhs.getYear();
}

// ------------------------------------------------------------------------
// - Operator: returns the amount of days between the two dates
// returns an int
// ------------------------------------------------------------------------
int Date::operator-(const Date &rhs) const
{
  int days_between_years = 0,
      upper_day = 0;
  if (year != rhs.getYear())
  {
    int lower_year,
        upper_year;
    // Find the upper (latest) year and the lower (earliest) year and day
    if (year > rhs.getYear())
    {
      upper_year = year;
      lower_year = rhs.getYear();
      upper_day = day_in_year;
    }
    else
    {
      upper_year = rhs.getYear();
      lower_year = year;
      upper_day = rhs.getDayInYear();
    }
    // Counts days in each year and then adds the day_in_year to the final result
    // once the iterator (i) gets to upper_year
    for (int i = lower_year; i < upper_year; i++)
    {
      days_between_years += DAYS_IN_YEAR;
      if (isLeapYear(i))
        days_between_years++;
    }
    days_between_years += upper_day;
  }
  else
  {
    days_between_years = abs(day_in_year - rhs.getDayInYear());
  }
  return days_between_years;
}
