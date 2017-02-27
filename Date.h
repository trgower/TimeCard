/*******************************************************************************
 * Date.h
 *
 * Tanner Gower
 * 1/12/2016
 * Project 2: IncomeXpense
 *
 * A header file for a Date object.
 *
*******************************************************************************/
#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
  private:
    int day_in_month,
        day_in_year,
        month_in_year,
        year;
    std::string formatted_date;

  public:
    Date(); // sets to current Date
    Date(int, int, int);
    ~Date();

    std::string getFormattedDate(std::string) const;
    std::string getFormattedDate();

    bool isLeapYear() const;
    bool isLeapYear(int) const;

    int getDayInMonth() const;
    int getDayInYear() const;
    int calcDayInYear() const;
    int getWeekInYear() const;
    int getMonthInYear() const;
    int getYear() const;

    bool operator>(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    int operator-(const Date &rhs) const;

    static const std::string DAYS_OF_WEEK[7];
    static const std::string MONTHS[12];
};

#endif // DATE_H
