#ifndef STACK_H
#define STACK_H
#include "process.h"


class stack
{
    public:
        stack();
        virtual ~stack();

        void setTop(process *top);
        process* getTop();

        void incrementSize();
        void decrementSize();
        int getSize();

        void push(process *newProcess);

        void pop();

    protected:

    private:
        process *top;
        int size;
};

#endif // STACK_H
