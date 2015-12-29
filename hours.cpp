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

void clockIn()
{
  ofstream hrFile;
  string fileName;
  char lunch;
  cout << "Are you coming back from lunch? (y/n)";
  cin >> lunch;

  time_t t = time(0);
  struct tm *now = localtime(&t);

  fileName = "Pay starting " + (now->tm_mon+1) + '-' + (now->tm_mday);
  hrFile.open(fileName, ios::app);
  if(!hrFile.is_open())
  {
    cout << "ERROR: could not open the hours file";
  }

  if(lunch == 'n')
  {
    hrFile << "START: " << (now->tm_mon+1) << "-" << (now->tm_mday) << endl;
    hrFile << "in: " << (now->tm_hour) << ":" << (now->tm_min) << endl;
  }
  else
  {
    hrFile << "Clocked in at " << (now->tm_hour) << ":" << (now->tm_min) << endl;
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
