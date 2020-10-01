#ifndef PROCESS_H
#define PROCESS_H


class process
{
    public:
        process();
        process(int id, int priority, int arrivalTime, int runTime, process *next);
        virtual ~process();

        int getID();
        int getPriority();
        int getArrivalTime();
        int getRunTime();
        int getLatency();
        int getProceededTime();
        process* getProcess();
        process* getNext();

        void setNext(process *next);
        void setRunTime(int remainingRunTime);
        void setLatency(int latency);
        void setProceededTime(int proceededTime);


    protected:

    private:
        int id;
        int priority;
        int arrivalTime;
        int runTime;
        int latency;
        int proceededTime;

        process *next;
};



#endif // PROCESS_H
