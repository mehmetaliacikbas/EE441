#include "process.h"

process::process()
{
    //ctor
}

//Constructor of the process
process::process(int id, int priority, int arrivalTime, int runTime, process *next) {

    this->id = id;
    this->priority = priority;
    this->arrivalTime = arrivalTime;
    this->runTime = runTime;
    this->next = next;
    this->proceededTime = 0;
}

process::~process()
{
    //dtor
}

//Getter function of ID
int process::getID() {

    return this->id;
}

//Getter function of priority
int process::getPriority() {

    return this->priority;
}

//Getter function of arrivalTime
int process::getArrivalTime() {

    return this->arrivalTime;
}

//Getter function of runTime
int process::getRunTime(){

    return this->runTime;
}

//Getter function of latency
int process::getLatency() {

    return this->latency;
}

//Getter function of proceededTime
int process::getProceededTime() {

    return this->proceededTime;
}

//Getter function of next of process
process* process::getNext() {

    return this->next;
}

//Setter function of runTime
void process::setRunTime(int remainingRunTime) {

    this->runTime = remainingRunTime;
}

//Setter function of latency
void process::setLatency(int latency) {

    this->latency = latency;
}

//Setter function of next of process
void process::setNext(process *next) {

    this->next = next;
}

//Setter function of proceededTime
void process::setProceededTime(int proceededTime) {

    this->proceededTime = proceededTime;
}
