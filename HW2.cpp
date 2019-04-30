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

void printResults(vector<Job> &list){
  std::sort(list.begin(), list.end(), [](Job&lhs, Job&rhs){return lhs.id<rhs.id;});
  std::cout << "id\tstart\tend\tTotal time\tResponse time\n";
  for(auto i = list.begin(); i != list.end(); i++){
    int total =  i->finish - i->start;
    int response =  i->start - i->arrival;
    printf("%d\t%d\t%d\t%d\t\t%d\n", i->id, i->start, i->finish, total, response);
  }
}

void FIFO(std::vector<Job> readyQ, int size) {
  cout << "++++++++++++++++++++ FIFO ++++++++++++++++++++" << endl;
  std::vector<Job> finishedList;
  Job *in = &readyQ[0];
  in->start = 1000;
  int i = 0;
  int current= 0;

  for(i = 0; i < size; i++){
    Job *in = &readyQ[i];
    Job *temp = &finishedList[0];
    if(in->arrival > current){
      in->start = in->arrival;
      in->finish = in->start + in->duration;
      current = in->finish;
    }
    else if(in->arrival <= current){
      in->start = current;
      in->finish = in->start + in->duration;
      current = in->finish;
    }
    finishedList.push_back(*in);
    //cout << "ID: " << in->id << endl;
    //cout << "Start: " << in->start << endl;
    //cout << "Finish: " << in->finish << endl;
    
  }
  printResults(finishedList);
}

void SJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ SJF ++++++++++++++++++++" << endl;
  float turnaround;
  int completion = 0;
  float response = 0;
  float temp = 0;
  float avg = 0;
  int start = 0;
  int min;
  int tempP;
  int tempA;
  int tempD;
  int sData[MAX][3];
  int i;
  int j;
  

  for (i = 0; i < size; i++) {
    for (j = 0; j < 3; j++) {
      sData[i][j] = data[i][j];
    }  
  }

  for (i = 0; i < size; i++) {
    min = sData[i][1];

    for (j = i + 1; j < size; j++) {
      if (sData[j][1] < min) {
        min = sData[j][1];

	tempA = sData[i][1];
	tempD = sData[i][2];
	      
	sData[i][1] = sData[j][1];
	sData[j][1] = tempA;
	sData[i][2] = sData[j][2];
	sData[j][2] = tempD;
	completion += sData[i][2]; 
      }
    }
     
  }

  /*for (i = 0; i < size; i++) {
    cout << sData[i][1];
  }*/
  
  std::vector<Job> finishedSJFList;
  std::vector<Job> SJList;
  Job *sIn;
  int id       = 0;
  int arrival  = 0;
  int duration = 0;

  for (i = 0; i < size; i++) {
    id       = sData[i][0];
    //cout << id << "\n";
    arrival  = sData[i][1];
    duration = sData[i][2];
    Job sIn(id, arrival, duration);
    SJList.push_back(sIn);
  }

  int current = 0;

  for(i = 0; i < size; i++) {
    Job *sIn = &SJList[i];
    if (sIn->arrival > current) {
      sIn->start = sIn->arrival;
      sIn->finish = sIn->start + sIn->duration;
      current = sIn->finish;
    }
    else if (sIn->arrival <= current) {
      sIn->start = current;
      sIn->finish = sIn->start + sIn->duration;
      current = sIn->finish;
    }
    finishedSJFList.push_back(*sIn);
    //cout << "ID: " << sIn->id << endl;
    //cout << "Start: " << sIn->start << endl;
    //cout << "Finish: " << sIn->finish << endl;
    
  }

  printResults(finishedSJFList);  
}

void BJF(int data[][3], int size) {
  cout << "++++++++++++++++++++ BJF ++++++++++++++++++++" << endl;
  float turnaround;
  int completion = 0;
  float response = 0;
  float temp = 0;
  float avg = 0;
  int start = 0;
  int max;
  int tempP;
  int tempA;
  int tempD;
  int bData[MAX][3];
  int i;
  int j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < 3; j++) {
      bData[i][j] = data[i][j];
    }  
  }

  for (i = 0; i < size; i++) {
    max = bData[i][1];

    for (j = i + 1; j < size; j++) {
      if (bData[j][1] > max) {
        max = bData[j][1];

	tempA = bData[i][1];
	tempD = bData[i][2];
	      
	bData[i][1] = bData[j][1];
	bData[j][1] = tempA;
	bData[i][2] = bData[j][2];
	bData[j][2] = tempD;
	completion += bData[i][2]; 
      }
    }
     
  }

  std::vector<Job> finishedBJFList;
  std::vector<Job> BJList;
  Job *bIn;
  int id       = 0;
  int arrival  = 0;
  int duration = 0;

  for (i = 0; i < size; i++) {
    id       = bData[i][0];
    //cout << id << "\n";
    arrival  = bData[i][1];
    duration = bData[i][2];
    Job bIn(id, arrival, duration);
    BJList.push_back(bIn);
  }

  int current = 0;

  for(i = 0; i < size; i++) {
    Job *bIn = &BJList[i];
    if (bIn->arrival > current) {
      bIn->start = bIn->arrival;
      bIn->finish = bIn->start + bIn->duration;
      current = bIn->finish;
    }
    else if (bIn->arrival <= current) {
      bIn->start = current;
      bIn->finish = bIn->start + bIn->duration;
      current = bIn->finish;
    }
    finishedBJFList.push_back(*bIn);
    //cout << "ID: " << sIn->id << endl;
    //cout << "Start: " << sIn->start << endl;
    //cout << "Finish: " << sIn->finish << endl;
    
  }

  printResults(finishedBJFList);
}

/*
Note: STCF schedules every clock cycle, not when a job arrives.
*/

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

    
    while(!readyQ.empty() && readyQ.front().arrival == clock){ //check if job arrived
      runQ.push_back(readyQ.front()); //add job to runQ
      readyQ.erase(readyQ.begin());
    }
   
    make_heap(runQ.begin(), runQ.end(), remainCmp); //sort by shortest remaining time
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
    }
    */
    
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
       j = 0;
       while(std::getline(iss,temp,' '))
       {
          data[i][j] = std::stoi(temp);
          j++;
       }
      
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

  FIFO(jobList, i);
  SJF(data, i);
  BJF(data, i);

  STCF(jobList);
  RR(jobList);

  return 0;
}
