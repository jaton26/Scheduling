#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#define MAX 100

using namespace std;

void FIFO(int data[][3], int size) {
  cout << "++++++++++++++++++++ FIFO ++++++++++++++++++++" << endl;
  float turnaround;
  float completion = 0;
  float temp = 0;
  float avg = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 3; j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
    completion += data[i][2];
    cout << "Completion time: " << completion << endl;
    turnaround = completion - data[i][1];
    cout << "Turnaround time: " << turnaround << endl;
    temp += turnaround;
  }
  avg = temp / (size);
  cout << "Average: " << avg << endl;
}

void SJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ SJF ++++++++++++++++++++" << endl;
  int duration = 0;
  int arrival = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 3; j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
  }
}

int main()
{
  int data[MAX][3];
  int i = 0;
  int j = 0;
  int size;
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
  FIFO(data, i);
  SJF(data, i);
  //BJF();
  return 0;
}
