#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int main()
{
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%y %I:%M:%S", timeinfo);
  string str(buffer);

  cout << str << endl;

  return 0;
}
