/*******************************************************************************
 * WorkShift.h
 *
 * Tanner Gower
 * 2/18/2016
 * Project 3: HourTracker
 *
 * Header file for the WorkShift Object.
 *
*******************************************************************************/
#ifndef WORKSHIFT_H
#define WORKSHIFT_H

#include <string>
#include <ctime>

class WorkShift
{
  private:
    time_t local_time;
    tm* tm_struct;
    double hours_worked;
    int day_in_week,
        month_in_year_in,
        day_in_month_in,
        year_in,
        month_in_year_out,
        day_in_month_out,
        year_out,
        hour_in,
        hour_out,
        min_in,
        min_out;

  public:
    WorkShift();
    WorkShift(int, int, int, int, int, int, int, int, int, int, int, double);

    void startShift();
    void endShift();

    double getHoursWorked() const;

    int getDayInWeek() const;
    int getDayInMonthIn() const;
    int getMonthInYearIn() const;
    int getYearIn() const;
    int getDayInMonthOut() const;
    int getMonthInYearOut() const;
    int getYearOut() const;
    int daysBetween() const;

    std::string toString() const;
    std::string getFormattedString() const;
    std::string getDate() const;
    std::string getFormattedDate() const;
    std::string getFormattedTimeIn() const;
    std::string getFormattedTimeOut() const;

    bool operator==(const WorkShift &rhs) const;
};

#endif // WORKSHIFT_H
