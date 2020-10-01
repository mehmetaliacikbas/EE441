#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"


class queue
{
    public:
        queue();
        virtual ~queue();

        void addProcess(process *process);
		int getSize();
		void incrSize();
		void decrSize();
		process* getHead();
		void deleteHead();


    protected:

    private:
        process *head;
        int size;
};

#endif // QUEUE_H
