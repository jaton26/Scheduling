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
  cout << "\nAverage: " << avg << endl;
}

void SJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ SJF ++++++++++++++++++++" << endl;
  float turnaround;
  int completion = 0;
  float temp = 0;
  float avg = 0;
  int pos = 0;
  int tempP;
  int tempA;
  int tempD;
  int sData[MAX][3];
  int i;
  int j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      sData[i][j] = data[i][j];
    }  
  }

  for (i = 0; i < size; i++) {
    pos = i;

    for (j = i + 1; j < size; j++) {
      if (sData[j][1] < completion && sData[j][2] < sData[pos][2]) {
        pos = j;
      }
    }
    tempP = sData[i][0];
    tempA = sData[i][1];
    tempD = sData[i][2];
      
    sData[i][0] = sData[pos][0];
    sData[pos][0] = tempP;
    sData[i][1] = sData[pos][1];
    sData[pos][1] = tempA;
    sData[i][2] = sData[pos][2];
    sData[pos][2] = tempD;
    completion += sData[i][2];  
  }

  completion = 0;

  for (i = 0; i < size; i++) {
    for (j = 0; j < 3; j++) {
      cout << sData[i][j] << " ";
    }
    cout << endl;
    completion += sData[i][2];
    cout << "Completion time: " << completion << endl;
    turnaround = completion - sData[i][1];
    cout << "Turnaround time: " << turnaround << endl;
    temp += turnaround;
  }
  avg = temp / (size);
  cout << "\nAverage: " << avg << endl;
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
