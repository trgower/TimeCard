/*******************************************************************************
 * WorkShift.cpp
 *
 * Tanner Gower
 * 2/18/2016
 * Project 3: HourTracker
 *
 * An object that represents a regular work day.
 *
*******************************************************************************/

#include <sstream>
#include <iomanip>
#include "WorkShift.h"
#include "Date.h"

using namespace std;

// ------------------------------------------------------------------------
// WorkShift: Initializes the WorkShift object by setting hours worked to 0
// ------------------------------------------------------------------------
WorkShift::WorkShift()
{
  hours_worked = 0;
}

// ------------------------------------------------------------------------
// WorkShift: Initializes the WorkShift object with specified parameters
// dw: day in week (0-6)
// m: month in year (0-11)
// dm: day in month (1-31)
// hin: hour clocked in (0-23)
// min: minute clocked in (0-59)
// hout: hour clocked out (0-23)
// mout: minute clocked out (0-59)
// hw: hours worked in shift
// ------------------------------------------------------------------------
WorkShift::WorkShift(int dw, int m_in, int dm_in, int y_in, int m_out,
                     int dm_out, int y_out, int hin, int min,
                     int hout, int mout, double hw)
{
  day_in_week = dw;

  month_in_year_in = m_in;
  day_in_month_in = dm_in;
  year_in = y_in;

  month_in_year_out = m_out;
  day_in_month_out = dm_out;
  year_out = y_out;

  hour_in = hin;
  min_in = min;
  hour_out = hout;
  min_out = mout;
  hours_worked = hw;
}

// ------------------------------------------------------------------------
// startShift: Gets the local time and then assigns hour in and minute in
//             times. Initializes the date.
// ------------------------------------------------------------------------
void WorkShift::startShift()
{
  local_time = time(0);
  tm_struct = localtime(&local_time);
  hour_in = tm_struct->tm_hour;
  min_in = tm_struct->tm_min;

  day_in_week = tm_struct->tm_wday;

  month_in_year_in = tm_struct->tm_mon;
  day_in_month_in = tm_struct->tm_mday;
  year_in = tm_struct->tm_year + 1900;
}

// ------------------------------------------------------------------------
// endShift: Gets the local time and then assigns hour out and minute out
//             times. Calculates total hours worked
// ------------------------------------------------------------------------
void WorkShift::endShift()
{
  int hour_diff = 0;
  int min_diff = 0;

  local_time = time(0);
  tm_struct = localtime(&local_time);
  hour_out = tm_struct->tm_hour;
  min_out = tm_struct->tm_min;

  month_in_year_out = tm_struct->tm_mon;
  day_in_month_out = tm_struct->tm_mday;
  year_out = tm_struct->tm_year + 1900;

  hour_diff = hour_out - hour_in;
  min_diff = min_out - min_in;
  hours_worked = hour_diff + (min_diff / 60.0) + (daysBetween() * 24);
}

// ------------------------------------------------------------------------
// Accessors: returns member variables
// ------------------------------------------------------------------------
double WorkShift::getHoursWorked() const { return hours_worked; }
int WorkShift::getDayInWeek() const { return day_in_week; }
int WorkShift::getDayInMonthIn() const { return day_in_month_in; }
int WorkShift::getMonthInYearIn() const { return month_in_year_in; }
int WorkShift::getYearIn() const { return year_in; }
int WorkShift::getDayInMonthOut() const { return day_in_month_out; }
int WorkShift::getMonthInYearOut() const { return month_in_year_out; }
int WorkShift::getYearOut() const { return year_out; }

// ------------------------------------------------------------------------
// toString: constructs a string that stores data in the WorkShift object
// returns a string
// ------------------------------------------------------------------------
string WorkShift::toString() const
{
  stringstream ss;
  ss << fixed << setprecision(2) << day_in_week << " "
     << month_in_year_in << " " << day_in_month_in << " " << year_in << " "
     << month_in_year_out << " " << day_in_month_out << " " << year_out << " "
     << hour_in       << " " << min_in       << " "
     << hour_out      << " " << min_out      << " "
     << hours_worked;
  return ss.str();
}

// ------------------------------------------------------------------------
// getFormattedString: constructs a formatted string that represents the
//                     WorkShift.
// returns a string
// ------------------------------------------------------------------------
string WorkShift::getFormattedString() const
{
  stringstream ss;
  ss << fixed << setprecision(2) << Date::DAYS_OF_WEEK[day_in_week] << " "
     << setfill('0') << setw(2) << month_in_year_in + 1 << "/"
     << setfill('0') << setw(2) << day_in_month_in << "/"
     << setfill('0') << setw(2) << year_in << " "
     << setfill('0') << setw(2) << hour_in      << ":"
     << setfill('0') << setw(2) << min_in       << " "
     << setfill('0') << setw(2) << hour_out     << ":"
     << setfill('0') << setw(2) << min_out      << " "
     << setfill('0') << setw(5) << hours_worked;
  return ss.str();
}

// ------------------------------------------------------------------------
// getDate: constructs a string that represents the date
//                   of the WorkShift. MMDDYYYY
// returns a string
// ------------------------------------------------------------------------
string WorkShift::getDate() const
{
  stringstream ss;
  ss << setfill('0') << setw(2) << month_in_year_in + 1
     << setfill('0') << setw(2) << day_in_month_in
     << setfill('0') << setw(2) << year_in;
  return ss.str();
}

// ------------------------------------------------------------------------
// getFormattedDate: constructs a formatted string that represents the date
//                   of the WorkShift. MMDDYYYY
// returns a string
// ------------------------------------------------------------------------
string WorkShift::getFormattedDate() const
{
  stringstream ss;
  ss << setfill('0') << setw(2) << month_in_year_in + 1 << "/"
     << setfill('0') << setw(2) << day_in_month_in << "/"
     << setfill('0') << setw(2) << year_in;
  return ss.str();
}

// ------------------------------------------------------------------------
// getFormattedTimeIn: constructs a formatted string that represents the time
//                     in of the WorkShift.
// returns a string
// ------------------------------------------------------------------------
string WorkShift::getFormattedTimeIn() const
{
  stringstream ss;
  ss << setfill('0') << setw(2) << hour_in      << ":"
     << setfill('0') << setw(2) << min_in;
  return ss.str();
}

// ------------------------------------------------------------------------
// getFormattedTimeOut: constructs a formatted string that represents the time
//                      in of the WorkShift.
// returns a string
// ------------------------------------------------------------------------
string WorkShift::getFormattedTimeOut() const
{
  stringstream ss;
  ss << setfill('0') << setw(2) << hour_out      << ":"
     << setfill('0') << setw(2) << min_out;
  return ss.str();
}

// ------------------------------------------------------------------------
// operator==: returns true if the WorkShift objects are on the same date,
//             false otherwise. Uses the in time as date.
// returns a bool
// ------------------------------------------------------------------------
bool WorkShift::operator==(const WorkShift &rhs) const
{
  return (day_in_month_in == rhs.day_in_month_in
          && month_in_year_in == rhs.month_in_year_in
          && year_in == rhs.year_in);
}

// ------------------------------------------------------------------------
// daysBetween: returns the amount of days in between the in time and out
//              time. Uses an old date class i created, don't look at it...
// returns a bool
// ------------------------------------------------------------------------
int WorkShift::daysBetween() const
{
  Date date_in(month_in_year_in, day_in_month_in, year_in);
  Date date_out(month_in_year_out, day_in_month_out, year_out);
  return date_in - date_out;
}
