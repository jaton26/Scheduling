#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue> 
#include "Job.h"
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

void STCF(int data[][3], int size){
  cout << "++++++++++++++++++++ STCF +++++++++++++++++++" << endl;
  std::priority_queue<Job, std::vector<Job>, cmpArrival> readyQ;
  std::priority_queue<Job, std::vector<Job>, cmpId> finishedList;
  std::vector<Job> activeQ;

  //push all jobs to queue sort by arrival time
  for (int i = 0; i < size; i++){
    Job newJob(data[i][0],data[i][1],data[i][2]);
    readyQ.push(newJob);
  }

  int clock = 0; //initialize clock
  while (!activeQ.empty() || !readyQ.empty()){
    

    if(readyQ.top().arrival == clock){
      while(!readyQ.empty() && readyQ.top().arrival == clock){ //check if job arrived
        activeQ.push_back(readyQ.top()); //add job to activeQ
        readyQ.pop();
      }
       make_heap(activeQ.begin(), activeQ.end(), cmpRemain()); //sort 
    }
    
    if (!activeQ.empty()){
      Job *running = &activeQ.front(); //get schduled job
      if(!(running->started)){  //start procress if not running
        running->started = true; 
        running->start = clock; //record start time
      } else{
        running->remain--;  //decrement remaining time
      }

      if (running->remain <= 0){  //if procress finished, remove from activeQ and add to finishedList
        running->finish = clock; //record finish time
        finishedList.push(*running); //add to finishedList

        //pop from activeQ
        std::pop_heap(activeQ.begin(), activeQ.end(), cmpRemain());
        activeQ.pop_back();
      }
      //std::cout << "clock: " << clock << "\n";
      // for (auto i = activeQ.begin(); i != activeQ.end(); ++i){
      //   printf("%d: %d\n", i->id, i->remain);
      // }
    }
    clock++;
  }

  //print result
  std::cout << "id\tstart\tend\tTotal time\tResponse time\n";
  while(!finishedList.empty()){
    const Job *item = &finishedList.top();
    int total =  item->finish - item->start;
    int response =  item->start - item->arrival;
    printf("%d\t%d\t%d\t%d\t\t%d\n", item->id, item->start, item->finish, total, response);
    finishedList.pop();
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

  STCF(data, i);
  return 0;
}
