#ifndef JOB_H
#define JOB_H

struct Job{
  int id, arrival, duration, remain, start, finish;
  bool started; 
  Job(int id, int arrival, int duration): id(id), arrival (arrival), duration (duration), remain (duration), started(false) {};
  
};

static auto arrivalCmp = [](Job&lhs, Job&rhs){return lhs.arrival>rhs.arrival;};
static auto remainCmp = [](Job&lhs, Job&rhs){return lhs.remain>rhs.remain;};

#endif