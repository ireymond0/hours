#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

string FILE_ERROR = "ERROR: could not open the file\n";

void options();
string getDateTime(int i);
bool checkCurrentPayPeriod();
string writeCppFile(string s);
void clockIn();
void clockOut();
void endPayPeriod();
void startPayPeriod();
int dailyHours();
int getTimecardSize();

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
    strftime(buffer, 80, "%H:%M", timeinfo);
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

  if(lunch != 'y')
  {
    hrFile << "START: " << getDateTime(1) << endl;
    hrFile << "in: " << getDateTime(0) << endl;
  }
  else
  {
    hrFile << "in: " << getDateTime(0) << endl;
  }
  hrFile.close();
  options();
}

/******************************************************************************
* write something...
*******************************************************************************/
void clockOut()
{
  ofstream hrFile;
  string fileName;
  char lunch;
  cout << "Are you leaving to lunch? (y/n)";
  cin >> lunch;

  fileName = writeCppFile(getDateTime(1))+".txt";
  hrFile.open(fileName,ios::app);
  if(!hrFile.is_open())
  {
    cout << "ERROR: could not open the hours file\n";
  }
  else
  {
    if(lunch != 'y')
    {
      hrFile << "out: " << getDateTime(0) << endl;
      hrFile << "END: " << getDateTime(1) << endl;
    }
    else
    {
      hrFile << "out: " << getDateTime(0) << endl;
    }
  }
  hrFile.close();
}

/******************************************************************************
* ends the pay period by clearing out the cpp file
*******************************************************************************/
void endPayPeriod()
{
  ofstream cppFile;
  cppFile.open("cpp");
  if(!cppFile.is_open())
  {
    cout << "ERROR: could not open the cpp file\n";
  }
  else
  {
    cppFile << "";
    cout << "\nFinished pay period on " << getDateTime(1) << endl;
  }
}

/******************************************************************************
* start the pay period, initialises the cpp file with the date the pay period
* starts on
*******************************************************************************/
void startPayPeriod()
{
  ofstream cppFile;
  cppFile.open("cpp");
  if(!cppFile.is_open())
  {
    cout << "ERROR: could not open the cpp file\n";
  }
  else
  {
    cppFile << getDateTime(1);
    cout << "\nNew pay period starting on " << getDateTime(1) << endl;
  }
}

/******************************************************************************
* User options
*******************************************************************************/
void options()
{
  char input;
  cout << "What would you like to do?" << endl;
  cout << "i = clock-in\n" << "o = clock-out\n" << "n = new pay period\n" <<
    "e = end pay period" << "d = daily hours\n" << "p = paycheck hours\n";
  cin >> input;
  if(input == 'i')
    clockIn();
  else if(input == 'o')
    clockOut();
  else if(input == 'e')
    endPayPeriod();
  else if(input == 'n')
    startPayPeriod();
  else
    cout << "ERROR: no correct input detected. Exiting...";
}

/******************************************************************************
* write something...
*******************************************************************************/
int dailyHours()
{
  int hours = 0;
  int numOfLines = getTimecardSize();

  ifstream in;
  string fileName = getDateTime(1) + ".txt";
  in.open(fileName);
  if(in.is_open())
  {
    string *file = new string[numOfLines];

    for(int i = 0; i < numOfLines; ++i)
    {
      getline(in,file[i]);
    }

    istringstream ss(file[1]);
    string h[3];

    for (int i = 0; i < 3; ++i)
    {
      getline(ss, h[i], ':');
    }
    cout << h[1] << endl;
    int hr = atoi(h[1].c_str());
    cout << hr << endl;

    in.close();
    delete [] file;
  }
  else
  {
    options();
  }
  return hours;
}

/******************************************************************************
* write something...
*******************************************************************************/
int getTimecardSize()
{
  int numOfLines = 0;

  ifstream in;
  string fileName = getDateTime(1) + ".txt";
  in.open(fileName);
  if(in.is_open())
  {
    string file;
    while(getline(in,file))
    {
      numOfLines++;
    }
    in.close();
  }
  return numOfLines;
}

/******************************************************************************
* MAIN
*******************************************************************************/
int main(int argc, char** argv)
{
  char input;
  cout << endl << "** Luxion Clock Utility **\n" << endl;
  int i = dailyHours();
  cout << "You have " << i << "h so far today..." << endl;

  options();

  cout << "Would you like to do anything else? (y/n)";
  cin >> input;
  if(input == 'y')
    options();
  else
    return 0;

  return 0;
}
