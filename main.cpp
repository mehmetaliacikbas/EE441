#include <iostream>
#include <fstream> // file streams
#include "process.h"
#include "queue.h"
#include "stack.h"

using namespace std;

/*
    Example program for file input/output, accompanying EE441 HW1.
    This program opens an input and an output text file. As long as
    the input file has contents, the program reads 4 integers from
    it and writes them to the output file. In the output, integers
    are separated by commas, and after the four integers are written,
    a newline is printed.
*/

int main()
{
    int pID, priority, arrTime, runTime;

    ifstream infile; // input file stream
    ofstream outfile; // output file stream
    ofstream latfile; // latency file stream

    infile.open("input.txt"); // input file is input.txt
    outfile.open("output.txt"); // output file is output.txt
    latfile.open("latency.txt"); //latency file is latency.txt

    queue generalQueue = queue(); //General queue for all processes
    queue queue1 = queue(); //Queue for waiting processes that priorities equals 1
    queue queue2 = queue(); //Queue for waiting processes that priorities equals 2
    queue queue3 = queue(); //Queue for waiting processes that priorities equals 3

    int currentTime = 0;

    stack waitingStack = stack();

    process *currentProcess = nullptr;

    while(!infile.eof()){ // continue while input file has unread text
        infile >> pID >> priority >> arrTime >> runTime; // read input like cin

        process *newProcess = new process(pID, priority, arrTime, runTime, nullptr);
        generalQueue.addProcess(newProcess);
    }

    infile.close(); // close the files


    while(true) {

        if(generalQueue.getHead() != nullptr && generalQueue.getHead()->getArrivalTime() == currentTime) {

            outfile<<"t="<<currentTime<<" P"<<generalQueue.getHead()->getID()<<" arrives"<<endl;

            if(currentProcess == nullptr) { //If there is no process in CPU and some process comes at this time, get this process and remove from general queue

                currentProcess = generalQueue.getHead(); //Set current process
                generalQueue.deleteHead(); //Remove from general queue
            }
            else if(currentProcess->getPriority() <= generalQueue.getHead()->getPriority()){ // If priority of coming process greater than priority of process that in CPU

                if(generalQueue.getHead()->getPriority() == 1) {

                    queue1.addProcess(generalQueue.getHead()); //Push coming process to Q1 if it has priority 1
                    outfile<<"P"<<generalQueue.getHead()->getID()<<" pushed on Q1"<<endl;
                }
                else if(generalQueue.getHead()->getPriority() == 2) {

                    queue2.addProcess(generalQueue.getHead()); ////Push coming process to Q2 if it has priority 2
                    outfile<<"P"<<generalQueue.getHead()->getID()<<" pushed on Q2"<<endl;
                }
                else if(generalQueue.getHead()->getPriority() == 3) {

                    queue3.addProcess(generalQueue.getHead()); //Push coming process to Q3 if it has priority 3
                    outfile<<"P"<<generalQueue.getHead()->getID()<<" pushed on Q3"<<endl;
                }

                generalQueue.deleteHead(); //Remove coming process from general queue
            }
            else if(currentProcess->getPriority() > generalQueue.getHead()->getPriority()) {

                waitingStack.push(currentProcess);
                outfile<<"P"<<currentProcess->getID()<<" pushed on S with runTime "<<currentProcess->getRunTime() - currentProcess->getProceededTime()<<endl;
                currentProcess = generalQueue.getHead();
                generalQueue.deleteHead();
                outfile<<"P"<<currentProcess->getID()<<" preempted the CPU"<<endl;
            }
            outfile<<endl;
        }

        if(currentProcess->getProceededTime() == currentProcess->getRunTime()) {

            outfile<<"t="<<currentTime<<" P"<<currentProcess->getID()<<" finished"<<endl;
            latfile<<"latency for P"<<currentProcess->getID()<<" is "<<currentTime - currentProcess->getArrivalTime()<<endl;
            currentProcess = nullptr;

            if(waitingStack.getTop() != nullptr) {

                if(waitingStack.getTop()->getPriority() == 1) {

                    currentProcess = waitingStack.getTop();
                    waitingStack.pop();
                    outfile<<"P"<<currentProcess->getPriority()<<" popped from S"<<endl;
                }
                else if(waitingStack.getTop()->getPriority() == 2) {

                    if(queue1.getHead() != nullptr) {

                        currentProcess = queue1.getHead();
                        queue1.deleteHead();
                        outfile<<"P"<<currentProcess->getPriority()<<" popped from Q1"<<endl;
                    }
                    else {

                        currentProcess = waitingStack.getTop();
                        waitingStack.pop();
                        outfile<<"P"<<currentProcess->getPriority()<<" popped from S"<<endl;
                    }
                }
                else if(waitingStack.getTop()->getPriority() == 3) {

                    if(queue1.getSize() > 0) {

                        currentProcess = queue1.getHead();
                        queue1.deleteHead();
                        outfile<<"P"<<currentProcess->getID()<<" popped from Q1"<<endl;
                    }
                    else if(queue2.getSize() > 0) {

                        currentProcess = queue2.getHead();
                        queue2.deleteHead();
                        outfile<<"P"<<currentProcess->getID()<<" popped from Q2"<<endl;
                    }
                    else {

                        currentProcess = waitingStack.getTop();
                        waitingStack.pop();
                        outfile<<"P"<<currentProcess->getID()<<" popped from S"<<endl;
                    }
                }
            }
            else if(waitingStack.getTop() == nullptr) {

                if(queue1.getSize() > 0) {

                    currentProcess = queue1.getHead();
                    queue1.deleteHead();
                    outfile<<"P"<<currentProcess->getID()<<" popped from Q1"<<endl;
                }
                else if(queue2.getSize() > 0) {

                    currentProcess = queue2.getHead();
                    queue2.deleteHead();
                    outfile<<"P"<<currentProcess->getID()<<" popped from Q2"<<endl;
                }
                else if(queue3.getSize() > 0) {

                    currentProcess = queue3.getHead();
                    queue3.deleteHead();
                    outfile<<"P"<<currentProcess->getID()<<" popped from Q3"<<endl;
                }
            }
            outfile<<endl;
        }

        currentTime +=1;

        if(currentProcess != nullptr) {

            currentProcess->setProceededTime(currentProcess->getProceededTime() + 1);
        }

        if(currentProcess == nullptr && waitingStack.getTop() == nullptr && queue1.getSize() == 0 && queue2.getSize() == 0 && queue3.getSize() == 0) {

            break;
        }
    }

    outfile.close();
    latfile.close();

    return 0;
}


