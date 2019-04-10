#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define MAX 100

using namespace std;

void FIFO(int data[][3]) {
  int i;
  int j;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
  }
}

int main()
{
  int data[3][3];
  int i = 0;
  int j = 0;
  ifstream in("jobs.txt");
  std::string line;
  std::string temp;
  while(std::getline(in, line))
  {
      std::istringstream iss(line);

      // Parse each line using the input string stream
      j = 0;
      while(std::getline(iss,temp,' '))
      {
         data[i][j] = std::stoi(temp);
         j++;
      }
      i++;
  }

  FIFO(data);
  //SJF();
  //BJF();
  return 0;
}
