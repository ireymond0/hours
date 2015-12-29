#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string openfile()
{
  ofstream hrFile;
  if(!hrFile.open("hours.txt"))
  {
    cout << "Error: Could not open hours.txt" << endl;
  }
  hrFile << "Test.\n";
  hrFile.close();
}

int main(int argc, char** argv)
{
  cout << "** Luxion Clock Utility **" << endl;


  return 0;
}
