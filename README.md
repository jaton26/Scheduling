# CMPE 142 Assingment 2 - Scheduling

Takes in a job list with arrival time and duration and calculate start time, finish time, turnaround time, and response time for the following scheduling policies:

_non-preemptive:_
* First in first out (FIFO) 
* Shortest job first (SJF)
* Biggest job first (BJF)

_preemptive:_
* Shortest time-to-completion first (STCF)
* Round robin (RR)

__About `jobs.dat`:__ Each line in jobs.dat represents a signle job, with id, arrival time, and duration of the job seperated by whitespace.

### To build and run
1. Clone repo and `cd` into folder:

    ```
    git clone https://github.com/jaton26/Scheduling.git
    cd Scheduling
    ```
2. Comple executable:

    ```
    g++ HW2.cpp -o HW2
    ```
3. Run:
    
    ```
    ./HW2
    ```
