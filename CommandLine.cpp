/*******************************************************************************
 * CommandLine.cpp
 *
 * Tanner Gower
 * 2/18/2016
 * Project 3: HourTracker
 *
 * A simple utilty used to track hours worked. It saves the date, time in, time
 * out and the day of the week. It also prints to a approval file formatted
 * so you can copy and paste your hours worked into an email.
 * 
 * This was mainly used by me to track hours worked as a Grader at
 * Texas State University
 *
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "PayPeriod.h"

using namespace std;

int main ()
{
  bool running = true;
  string command = "";

  PayPeriod pp;

  cout << "----------Tanner Gower's Hour Tracker" << "----------" << endl;
  if (pp.isPayPeriodStarted())
    cout << "[PAY PERIOD IN PROGRESS]" << endl;
  else
    cout << "No pay period started. use \"in\" to clock in and start one."
         << endl;

  if (cin.rdbuf()->in_avail() == 0)
    cout << "> ";

  while (running)
  {
    if (cin.peek() == '\n')
      cout << "> ";
    cin >> command;

    if (command == "end")
    {
      cout << "[ENDING PERIOD...";
      if (pp.endPayPeriod())
        cout << "Success!]" << endl;
      else
        cout << "Failed! Make sure a directory named \"periods\" exists!]"
             << endl;
    }
    else if (command == "in")
    {
      if (pp.clockIn())
        cout << "[CLOCKED IN AT " << pp.getCurrentShift().getFormattedTimeIn()
             << "]" << endl;
      else
        cout << "[You are already clocked in!]" << endl;
    }
    else if (command == "out")
    {
      if (pp.clockOut())
      cout << "[CLOCKED OUT AT " << pp.getCurrentShift().getFormattedTimeOut()
           << "]" << endl;
      else
        cout << "[You are not clocked in!]" << endl;
    }
    else if (command == "print")
    {
      cout << "[" << pp.getFormattedDateRange() << " PAY PERIOD]" << endl
           << pp.getFormattedPayPeriod();
    }
    else if (command == "report")
    {
      cout << "[CREATING REPORT FILE...";
      if (pp.printEmailReportToFile("report.txt"))
        cout << "Success!]" << endl;
      else
        cout << "Failed!]" << endl;
    }
    else if (command == "load")
    {
      if (cin.peek() == '\n')
        cout << "Enter filepath: ";
      cin >> command;
      char verify;
      cout << "[This will overwrite your current pay period! "
           << "Are you sure? Y/N]" << endl;
      cin >> verify;
      if (verify == 'Y' || verify == 'y')
      {
        cout << "[LOADING...";
        if (pp.loadFromFile(command))
          cout << "Success!]" << endl;
        else
          cout << "Failed!]" << endl;
      }
      else
        cout << "[CANCELLED LOAD]" << endl;
    }
    else if (command == "save")
    {
      cout << "[SAVING...";
      if (pp.saveToFile())
        cout << "Success!]" << endl;
      else
        cout << "Failed!]" << endl;
    }
    else if (command == "exit")
    {
      running = false;
      if (pp.isClockedIn())
        pp.clockOut();
        cout << "[SAVING...";
        if (pp.saveToFile())
          cout << "Success!]" << endl;
        else
          cout << "Failed!]" << endl;
    }
    else if (command == "cmd")
    {
      cout << "in - clock in/start pay period" << endl
           << "out - clock out" << endl
           << "end - end pay period and save to file" << endl
           << "print - print current pay period to screen" << endl
           << "report - prints email report to txt file" << endl
           << "exit - saves current pay period and exits" << endl;
    }
    else
    {
      cout << "Command \'" << command << "\' not found! Use \'cmd\' for "
           << "a list of commands." << endl;
    }
  }

  return 0;

}
