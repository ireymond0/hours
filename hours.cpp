#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/******************************************************************************
* function inputs an int and returns a string
* if i = 0 return time string
* if i = 1 return date string
* if i = 2 return year string
*******************************************************************************/
string getDateTime(int i)
{
  time_t t;
  struct tm * timeinfo;
  char buffer[80];

  time(&t);
  timeinfo = localtime(&t);

  if(i == 0)
  {
    strftime(buffer, 80, "%I:%M", timeinfo);
    string clckTime(buffer);
    return clckTime;
  }
  else if(i == 1)
  {
    strftime(buffer, 80, "%d-%m-%Y", timeinfo);
    string date(buffer);
    return date;
  }
  else if(i == 2)
  {
    strftime(buffer, 80, "%Y", timeinfo);
    string yr(buffer);
    return yr;
  }
  else
  {
    return "ERROR";
  }
}

bool checkCurrentPayPeriod()
{
  ifstream cppFile;
  cppFile.open("cpp");
  if(!cppFile.is_open())
  {
    cout << "ERROR: could not open the cpp file\n";
  }
  string d;
  cppFile >> d;
  cppFile.close();
  if (d == "" || d == " ")
  {
    return false;
  }
  else
    return true;
}

string writeCppFile(string s)
{
  if(!checkCurrentPayPeriod())
  {
    cout << "\nNew pay period starting today " + s << endl << endl;

    ofstream out;
    out.open("cpp");
    if(!out.is_open())
    {
      cout << "Error: could not open the cpp file\n";
    }
    out << s;
    out.close();

    return s;
  }
  else
  {
    ifstream cppFile;
    cppFile.open("cpp");
    if(!cppFile.is_open())
    {
      cout << "Error: could not open the cpp file\n";
    }
    string d;
    cppFile >> d;
    cppFile.close();
    cout << "\nPay period starting on " + d << endl <<endl;

    ofstream out;
    out.open("cpp");
    if(!out.is_open())
    {
      cout << "Error: could not open the cpp file\n";
    }
    out << d;
    out.close();

    return d;
  }
}

/******************************************************************************
* write something...
*******************************************************************************/
void clockIn()
{
  ofstream hrFile;
  string fileName;
  char lunch;
  cout << "Are you coming back from lunch? (y/n)";
  cin >> lunch;

  fileName = writeCppFile(getDateTime(1))+".txt";
  hrFile.open(fileName, ios::app);
  if(!hrFile.is_open())
  {
    cout << "ERROR: could not open the hours file\n";
  }

  if(lunch == 'n')
  {
    hrFile << "START: " << getDateTime(1) << endl;
    hrFile << "in: " << getDateTime(0) << endl;
  }
  else
  {
    hrFile << "Clocked in at " << getDateTime(0) << endl;
  }
  hrFile.close();
}

void clockOut()
{

}


int main(int argc, char** argv)
{
  char input;
  cout << endl << "** Luxion Clock Utility **\n" << endl;

  cout << "What would you like to do?" << endl;
  cout << "n = new pay period\n" << "i = clock-in\n" << "o = clock-out\n" <<
    "e = end pay period" << "d = daily hours\n" << "p = paycheck hours\n";
  cin >> input;
  if(input == 'i')
    clockIn();



  return 0;
}
