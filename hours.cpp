#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// string openfile()
// {
//   string file;
//   ifstream hrFile;
//   hrFile.open("hours.txt");
//   if(!hrFile.is_open())
//   {
//     cout << "Error: Could not open hours.txt" << endl;
//   }
//   while(!hrFile.eof())
//   {
//
//   }
//   hrFile.close();
//   return file;
// }

// void writeFile()
// {
//   ofstream hrFile;
//   hrFile.open("hours.txt", ios::app);
//   if(!hrFile.is_open())
//   {
//     cout << "error";
//   }
//   for(int i = 0; i < 3; ++i)
//   {
//     hrFile << "Testing \n";
//   }
//   hrFile.close();
// }

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

/**
* write something...
***/
void clockIn()
{
  ofstream hrFile;
  string fileName;
  char lunch;
  cout << "Are you coming back from lunch? (y/n)";
  cin >> lunch;

  fileName = "hours_" + getDateTime(2) + ".txt";
  cout << "test: " << fileName << endl;
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


int main(int argc, char** argv)
{
  char input;
  cout << endl << "** Luxion Clock Utility **\n" << endl;

  cout << "What would you like to do?" << endl;
  cout << "i = clock-in\n" << "o = clock-out\n" << "d = daily hours\n" <<
    "p = paycheck hours\n";
  cin >> input;
  if(input == 'i')
    clockIn();


  return 0;
}
