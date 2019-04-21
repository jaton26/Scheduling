#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

void printResults(vector<Job> &list){
  std::sort(list.begin(), list.end(), [](Job&lhs, Job&rhs){return lhs.id<rhs.id;});
  std::cout << "id\tstart\tend\tTotal time\tResponse time\n";
  for(auto i = list.begin(); i != list.end(); i++){
    int total =  i->finish - i->start;
    int response =  i->start - i->arrival;
    printf("%d\t%d\t%d\t%d\t\t%d\n", i->id, i->start, i->finish, total, response);
  }
}

void STCF(int data[][3], int size){
 
  std::priority_queue<Job, std::vector<Job>, decltype(arrivalCmp)> readyQ(arrivalCmp);
  std::vector<Job> finishedList;
  std::vector<Job> activeQ;


  //push all jobs to queue sort by arrival time
  for (int i = 0; i < size; i++){
    Job newJob(data[i][0],data[i][1],data[i][2]);
    readyQ.push(newJob);
  }

  int clock = 0; //initialize clock
  while (!activeQ.empty() || !readyQ.empty()){
      Job *last = &activeQ.front();
      
      if (!activeQ.empty() && last->remain <= 0){  //if procress finished, remove from activeQ and add to finishedList
        last->finish = clock; //record finish time
        finishedList.push_back(*last); //add to finishedList

        //pop from activeQ
        std::pop_heap(activeQ.begin(), activeQ.end(), remainCmp);
        activeQ.pop_back();
      }

    if(readyQ.top().arrival == clock){
      while(!readyQ.empty() && readyQ.top().arrival == clock){ //check if job arrived
        activeQ.push_back(readyQ.top()); //add job to activeQ
        readyQ.pop();
      }
       make_heap(activeQ.begin(), activeQ.end(), remainCmp); //sort 
    }
    
    if (!activeQ.empty()){
      Job *running = &activeQ.front(); //get schduled job
      if(!(running->started)){  //start procress if not running
        running->started = true; 
        running->start = clock; //record start time
      } 
      running->remain--;  //decrement remaining time
    }

    /* //debug output
    std::cout << "clock: " << clock << "\n";
    for (auto i = activeQ.begin(); i != activeQ.end(); ++i){
      printf("%d: %d\n", i->id, i->remain);
    }*/
    
    clock++;
  }

  //print result
  cout << "++++++++++++++++++++ STCF +++++++++++++++++++" << endl;
  printResults(finishedList);
}

void RR(int data[][3], int size){
 
  std::priority_queue<Job, std::vector<Job>, decltype(arrivalCmp)> readyQ(arrivalCmp);
  std::vector<Job> finishedList;
  std::vector<Job> runQ;

  //push all jobs to queue sort by arrival time
  for (int i = 0; i < size; i++){
    Job newJob(data[i][0],data[i][1],data[i][2]);
    readyQ.push(newJob);
  }

  int slice = 10; //time slice
  int clock = 0; //init clock
  int timer = 0; //timer to initialize interupt
  int counter = 0; //tracker on run queue position

  while (!runQ.empty() || !readyQ.empty()){
    
    if(!runQ.empty()){
      Job *last = &runQ[counter];
      if (last->remain <= 0){  //if procress finished, remove from activeQ and add to finishedList
          last->finish = clock; //record finish time
          finishedList.push_back(*last); //add to finishedList

          //pop from run queue
          runQ.erase(runQ.begin()+counter);
      }
    }

    if (timer == slice){ //interupt and move tracker to next job
      counter++;
      timer = 0;
    }

    //add job to run queue
    while(!readyQ.empty() && readyQ.top().arrival == clock){ //check if job arrived
        runQ.push_back(readyQ.top()); //add job to run queue
        readyQ.pop();
    }
    
    if (!runQ.empty()){
      
      if(counter >= runQ.size())
        counter = 0; //reset tracker to start of list when cycled through all jobs in list

      Job *running = &runQ[counter]; //get currently schduled job

      if(!(running->started)){  //start procress if not running
        running->started = true; 
        running->start = clock; //record start time
      } 
      
      running->remain--;  //decrement remaining time
      
    }
    /*  //debug output 
    cout << timer << " " << counter << " ";
    std::cout << "clock: " << clock << "\n";
    for (auto i = runQ.begin(); i != runQ.end(); ++i){
      printf("%d: %d\n", i->id, i->remain);
    }*/
    
    timer++;
    clock++;
  }

  cout << "+++++++++++++++++++++ RR ++++++++++++++++++++" << endl;
  printResults(finishedList);
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
  RR(data, i);
  return 0;
}
