/*******************************************************************************
 * WorkDay.h
 *
 * Tanner Gower
 * 2/18/2016
 * Project 3: HourTracker
 *
 * Header file for the PayPeriod Object.
 *
*******************************************************************************/
#ifndef PAYPERIOD_H
#define PAYPERIOD_H

#include <string>
#include <fstream>
#include "WorkShift.h"

class PayPeriod
{
  private:
    class Node
    {
      public:
        WorkShift ws;
        Node *next;
    };

    Node *head;

    WorkShift current_shift;
    bool clocked_in;

    std::ifstream infile;
    std::ofstream outfile;

    bool pay_period_started;

  public:
    PayPeriod();
    ~PayPeriod();

    bool endPayPeriod();
    bool clockIn();
    bool clockOut();
    void addShift(WorkShift);
    bool saveToFile();
    bool saveToFile(std::string);
    bool loadFromFile(std::string);
    std::string getFormattedPayPeriod() const;
    bool printEmailReportToFile(std::string);
    bool isClockedIn() const;
    std::string getDateRange() const;
    std::string getFormattedDateRange() const;
    WorkShift getCurrentShift() const;
    bool isPayPeriodStarted() const;
    bool clearList();

};

#endif // PAYPERIOD_H
