#include "stack.h"
#include "process.h"

//Constructor of stack
stack::stack()
{
    this->top = nullptr;
    this->size = 0;
}

stack::~stack()
{
    //dtor
}

//Getter function of top of stack
process* stack::getTop() {

    return this->top;
}

//Setter function of top of stack
void stack::setTop(process *top) {

    this->top = top;
}

//Getter function of size of stack
int stack::getSize() {

    return this->size;
}

//Increment function of size of stack
void stack::incrementSize() {

    this->size += 1;
}

//Decrement function of size of stack
void stack::decrementSize() {

    this->size -= 1;
}

//This function pushes the process to stack
void stack::push(process *newProcess) {

    if(this->top == nullptr) { //If stack is empty, set new process to top of stack

        this->top = newProcess;
        newProcess->setNext(nullptr);
    }
    else { //If stack is not empty, push new process to back of top of stack

        newProcess->setNext(this->top);
        this->top = newProcess;
    }

    this->incrementSize();
}

//This function removes top of stack
void stack::pop() {

    this->top = this->top->getNext();
    this->decrementSize();
}



