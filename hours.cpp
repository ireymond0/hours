#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string openfile()
{
  string file;
  ifstream hrFile;
  hrFile.open("hours.txt");
  if(!hrFile.is_open())
  {
    cout << "Error: Could not open hours.txt" << endl;
  }
  while(!hrFile.eof())
  {
    
  }
  hrFile.close();
  return file;
}

int main(int argc, char** argv)
{
  cout << "** Luxion Clock Utility **" << endl;


  return 0;
}
