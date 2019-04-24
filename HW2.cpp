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
  float start = 0;
  float response = 0;
  float temp = 0;
  float avg = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 3; j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
    //completion += data[i][2];
    cout << "Job: " << data[i][0] << endl;
    start = data[i][1];
    if(start > completion){
      cout << "Start Time: " << start << endl;
      completion = start;
    }
    else{
      cout << "Start Time: " << completion << endl;
      start = completion;
    }
    completion += data[i][2];
    //cout << "Completion time: " << completion << endl;
    cout << "Finish Time: " << completion << endl;
    turnaround = completion - data[i][1];
    cout << "Total Time Elapsed: " << turnaround << endl;
    response = start - data[i][1];
    cout << "Response Time: " << response << endl << endl;
    //cout << "Turnaround time: " << turnaround << endl;
    temp += turnaround;
  }
  avg = temp / (size);
  //cout << "\nAverage: " << avg << endl;
}

void SJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ SJF ++++++++++++++++++++" << endl;
  float turnaround;
  int completion = 0;
  float response = 0;
  float temp = 0;
  float avg = 0;
  int start = 0;
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

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 3; j++) {
      cout << sData[i][j] << " ";
    }
    cout << endl;
    //completion += data[i][2];
    cout << "Job: " << sData[i][0] << endl;
    start = sData[i][1];
    if(start > completion){
      cout << "Start Time: " << start << endl;
      completion = start;
    }
    else{
      cout << "Start Time: " << completion << endl;
      start = completion;
    }
    completion += sData[i][2];
    //cout << "Completion time: " << completion << endl;
    cout << "Finish Time: " << completion << endl;
    turnaround = completion - sData[i][1];
    cout << "Total Time Elapsed: " << turnaround << endl;
    response = start - sData[i][1];
    cout << "Response Time: " << response << endl << endl;
    //cout << "Turnaround time: " << turnaround << endl;
    temp += turnaround;
  }
}

void BJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ BJF ++++++++++++++++++++" << endl;
  float turnaround;
  int completion = 0;
  float response = 0;
  float temp = 0;
  float avg = 0;
  int start = 0;
  int pos = 0;
  int tempP;
  int tempA;
  int tempD;
  int bData[MAX][3];
  int i;
  int j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      bData[i][j] = data[i][j];
    }  
  }

  for (i = 0; i < size; i++) {
    pos = i;

    for (j = i + 1; j < size; j++) {
      if (bData[j][1] < completion && bData[j][2] > bData[pos][2]) {
        pos = j;
      }
    }
    tempP = bData[i][0];
    tempA = bData[i][1];
    tempD = bData[i][2];
      
    bData[i][0] = bData[pos][0];
    bData[pos][0] = tempP;
    bData[i][1] = bData[pos][1];
    bData[pos][1] = tempA;
    bData[i][2] = bData[pos][2];
    bData[pos][2] = tempD;
    completion += bData[i][2];  
  }

  completion = 0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 3; j++) {
      cout << bData[i][j] << " ";
    }
    cout << endl;
    //completion += data[i][2];
    start = bData[i][1];
    cout << "Job: " << bData[i][0] << endl;
    if(start > completion){
      cout << "Start Time: " << start << endl;
      completion = start;
    }
    else{
      cout << "Start Time: " << completion << endl;
      start = completion;
    }
    completion += bData[i][2];
    //cout << "Completion time: " << completion << endl;
    cout << "Finish Time: " << completion << endl;
    turnaround = completion - bData[i][1];
    cout << "Total Time Elapsed: " << turnaround << endl;
    response = start - bData[i][1];
    cout << "Response Time: " << response << endl << endl;
    //cout << "Turnaround time: " << turnaround << endl;
    temp += turnaround;
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

void STCF(std::vector<Job> readyQ){
  std::vector<Job> finishedList;
  std::vector<Job> runQ;


  int clock = 0; //initialize clock
  while (!runQ.empty() || !readyQ.empty()){
      Job *last = &runQ.front();
      
      if (!runQ.empty() && last->remain <= 0){  //if procress finished, remove from run queue and add to finishedList
        last->finish = clock; //record finish time
        finishedList.push_back(*last); //add to finishedList

        //pop from runQ
        std::pop_heap(runQ.begin(), runQ.end(), remainCmp);
        runQ.pop_back();
      }

    if(readyQ.front().arrival == clock){
      while(!readyQ.empty() && readyQ.front().arrival == clock){ //check if job arrived
        runQ.push_back(readyQ.front()); //add job to runQ
        readyQ.erase(readyQ.begin());
      }
       make_heap(runQ.begin(), runQ.end(), remainCmp); //sort 
    }
    
    if (!runQ.empty()){
      Job *running = &runQ.front(); //get schduled job
      if(!(running->started)){  //start procress if not running
        running->started = true; 
        running->start = clock; //record start time
      } 
      running->remain--;  //decrement remaining time
    }

    /* //debug output
    std::cout << "clock: " << clock << "\n";
    for (auto i = runQ.begin(); i != runQ.end(); ++i){
      printf("%d: %d\n", i->id, i->remain);
    }*/
    
    clock++;
  }

  //print result
  cout << "++++++++++++++++++++ STCF +++++++++++++++++++" << endl;
  printResults(finishedList);
}

void RR(std::vector<Job> readyQ){
 
  std::vector<Job> finishedList;
  std::vector<Job> runQ;

  int slice = 1; //time slice
  int clock = 0; //init clock
  int timer = 0; //timer to initialize interupt
  int counter = 0; //tracker on run queue position

  while (!runQ.empty() || !readyQ.empty()){
    
    if(!runQ.empty()){
      Job *last = &runQ[counter];
      if (last->remain <= 0){  //if procress finished, remove from runQ and add to finishedList
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
    while(!readyQ.empty() && readyQ.front().arrival == clock){ //check if job arrived
        runQ.push_back(readyQ.front()); //add job to run queue
        readyQ.erase(readyQ.begin());
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
  ifstream in("jobs.dat");
  std::string line;
  std::string temp;
  std::vector<Job> jobList;

  while(std::getline(in, line))
  {
      std::istringstream iss(line);

      // Parse each line using the input string stream
      // j = 0;
      // while(std::getline(iss,temp,' '))
      // {
      //    data[i][j] = std::stoi(temp);
      //    j++;
      // }
      
      std::getline(iss,temp,' ');
      int id = std::stoi(temp);
      std::getline(iss,temp,' ');
      int arrival = std::stoi(temp);
      std::getline(iss,temp,' ');
      int duration = std::stoi(temp);
      
      Job newJob(id, arrival, duration);
      jobList.push_back(newJob);
      i++;
  }


  std::sort(jobList.begin(), jobList.end(),arrivalCmp);

  FIFO(data, i);
  SJF(data, i);
  BJF(data, i);

  STCF(jobList);
  RR(jobList);

  return 0;
}
