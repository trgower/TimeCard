/*******************************************************************************
 * PayPeriod.cpp
 *
 * Tanner Gower
 * 2/18/2016
 * Project 3: HourTracker
 *
 * This object keeps track of a dynamic array of WorkShift objects.
 *
*******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "PayPeriod.h"
#include "Date.h"

using namespace std;

const string CURRENT_PAYPERIOD_PATH = "currentpayperiod";

// ------------------------------------------------------------------------
// PerPeriod: Initializes the PayPeriod object and loads in the current
//            PayPeriod if it exists.
// ------------------------------------------------------------------------
PayPeriod::PayPeriod()
{
  head = NULL;
  clocked_in = false;
  pay_period_started = false;
  infile.open(CURRENT_PAYPERIOD_PATH.c_str());
  if (infile)
  {
    infile.close();
    loadFromFile(CURRENT_PAYPERIOD_PATH);
  }
}

// ------------------------------------------------------------------------
// ~PerPeriod: Destroys the PayPeriod linked list.
// ------------------------------------------------------------------------
PayPeriod::~PayPeriod()
{
  clearList();
}

// ------------------------------------------------------------------------
// endPayPeriod: Ends the current pay period if one has been started.
//               returns true is successful, false otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::endPayPeriod()
{
  if (pay_period_started && !clocked_in)
  {
    saveToFile("periods\\payperiod" + getDateRange());
    outfile.open(CURRENT_PAYPERIOD_PATH.c_str()); // clear contents
    outfile.close();
    pay_period_started = false;
    clearList(); // DESTRUCTION!!!!
    return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// clockIn: Clocks in but starting the shift. return true if successful,
//          false otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::clockIn()
{
  if (!clocked_in)
  {
    current_shift.startShift();
    clocked_in = true;
    if (!pay_period_started)
      pay_period_started = true;
    return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// clockOut: Clocks out and by ending the current shift and then adding it
//           to the linked list. returns true is successful, false otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::clockOut()
{
  if (clocked_in)
  {
    current_shift.endShift();
    addShift(current_shift);
    clocked_in = false;
    return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// addShift: Adds shift to the end of the linked list.
// shift: WorkShift to add
// ------------------------------------------------------------------------
void PayPeriod::addShift(WorkShift shift)
{
  Node *curr = head;
  while (curr && curr->next)
    curr = curr->next;
  Node *new_shift = new Node;
  new_shift->ws = shift;
  new_shift->next = NULL;
  if (curr)
    curr->next = new_shift;

  if (!head)
    head = new_shift;
}

// ------------------------------------------------------------------------
// saveToFile: calls saveToFile(string) and passes in the default current
//             PayPeriod path.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::saveToFile()
{
  if (pay_period_started) {
    return saveToFile(CURRENT_PAYPERIOD_PATH);
  }
  return false;
}

// ------------------------------------------------------------------------
// saveToFile: Traverses through the linked list and saves work days to
//             path. returns true is successful, false otherwise.
// path: path to save file
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::saveToFile(string path)
{
  if (head)
  {
    outfile.open(path.c_str());
    if (outfile)
    {
      Node *curr = head;
      while (curr)
      {
        outfile << curr->ws.toString() << endl;
        curr = curr->next;
      }
      outfile.close();
      return true;
    }
  }
  else
  {
    return false;
  }
}

// ------------------------------------------------------------------------
// loadFromFile: Loads work days from the file (path) into the linked list.
//               returns true if successful, false otherwise.
// path: path to load file
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::loadFromFile(string path)
{
  infile.open(path.c_str());
  if (infile)
  {
    clearList();
    int dw,
        m_in,
        dm_in,
        y_in,
        m_out,
        dm_out,
        y_out,
        hin,
        min,
        hout,
        mout;
    double hw;
    while (infile >> dw >> m_in >> dm_in >> y_in >> m_out >> dm_out >> y_out
                  >> hin >> min >> hout >> mout >> hw) // heheh
    {
      WorkShift loaded_shift(dw, m_in, dm_in, y_in, m_out, dm_out, y_out, hin,
                             min, hout, mout, hw);
      addShift(loaded_shift);
      pay_period_started = true;
    }
    infile.close();
    return true;
  }
  return false;
}

// ------------------------------------------------------------------------
// printEmailReportToFile: saves an email report to file formatted to BECR's
//                         standards. returns true if successful,
//                         false otherwise.
// path: path to save file
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::printEmailReportToFile(string path) // this is ugly i'm sorry
{
  if (head)
  {
    double dbl_shift_hours = 0,
           total_hours = 0;
    Node *day_start, *curr;
    outfile.open(path.c_str());
    if (outfile)
    {
      day_start = curr = head;
      while (curr || day_start)
      {
        while (curr && day_start && curr->ws == day_start->ws) // on same day?
        {
          dbl_shift_hours += curr->ws.getHoursWorked();
          curr = curr->next;
        }
        // Finished with day
        outfile << Date::DAYS_OF_WEEK[day_start->ws.getDayInWeek()] << ", "
                << Date::MONTHS[day_start->ws.getMonthInYearIn()] << " "
                << day_start->ws.getDayInMonthIn() << ", "
                << fixed << setprecision(2) << dbl_shift_hours << endl;
        day_start = curr;

        total_hours += dbl_shift_hours;

        if (curr)
        {
          dbl_shift_hours = curr->ws.getHoursWorked();
          curr = curr->next;
        }
      }

      outfile << "Total: " << fixed << setprecision(2) << total_hours;

      outfile.close();
      return true;
    }
  }
  else
  {
    return false;
  }
}

// ------------------------------------------------------------------------
// getFormattedPayPeriod: constructs a string that represents the pay period.
// returns a string
// ------------------------------------------------------------------------
string PayPeriod::getFormattedPayPeriod() const
{
  Node *curr = head;
  stringstream ss;
  while (curr)
  {
    ss << curr->ws.getFormattedString() << endl;
    curr = curr->next;
  }
  return ss.str();
}

// ------------------------------------------------------------------------
// isClockedIn: returns true if clocked in, false otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::isClockedIn() const { return clocked_in; }

// ------------------------------------------------------------------------
// getDateRange: contructs a string representing the date range in this
//               format: MMDDYYYY-MMDDYYYY. Returns "ERROR" is unsuccessful
// returns a string
// ------------------------------------------------------------------------
string PayPeriod::getDateRange() const
{
  if (head)
  {
    stringstream ss;
    WorkShift today;
    today.startShift();

    ss << head->ws.getDate() << "-" << today.getDate();
    return ss.str();
  }
  return "ERROR";
}

// ------------------------------------------------------------------------
// getFormattedDateRange: contructs a string representing the date range in
//                        this format: MM/DD/YYYY-MM/DD/YYYY. Returns "EMPTY"
//                        is unsuccessful
// returns a string
// ------------------------------------------------------------------------
string PayPeriod::getFormattedDateRange() const
{
  if (head)
  {
    stringstream ss;
    WorkShift today;
    today.startShift();

    ss << head->ws.getFormattedDate() << "-Today";
    return ss.str();
  }
  return "EMPTY";
}

// ------------------------------------------------------------------------
// getCurrentShift: returns current work shift
// returns a WorkShift
// ------------------------------------------------------------------------
WorkShift PayPeriod::getCurrentShift() const { return current_shift; }

// ------------------------------------------------------------------------
// isPayPeriodStarted: returns true if started, false otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::isPayPeriodStarted() const { return pay_period_started; }

// ------------------------------------------------------------------------
// clearList: deletes the linked list and returns true if successful, false
//            otherwise.
// returns a bool
// ------------------------------------------------------------------------
bool PayPeriod::clearList()
{
  if (head)
  {
    Node *curr = head,
         *temp;
    while (curr)
    {
      temp = curr;
      curr = curr->next;
      delete temp;
    }
    head = NULL;
    return true;
  }
  return false;
}
