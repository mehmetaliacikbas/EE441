#include "queue.h"
#include "process.h"

//Constructor of queue
queue::queue()
{
    this->size = 0;
	this->head = nullptr;
}

queue::~queue()
{
    //dtor
}

//Getter function of head of queue
process* queue::getHead()
{
	return this->head;
}

//Getter function of size of queue
int queue::getSize()
{
	return this->size;
}

//This function increments the size of queue
void queue::incrSize()
{
	this->size = this->size + 1;
}

//This function decrements the size of queue
void queue::decrSize()
{
	this->size = this->size - 1;
}

//This function deletes the head of queue
void queue::deleteHead()
{

	this->head = this->head->getNext();
	this->decrSize();
}

//This function inserts the process to queue
void queue::addProcess(process *newProcess)
{
	if(this->head == nullptr) // if queue is empty, insert process at the head of queue
	{
		this->head = newProcess;
		//head->setNext(nullptr);
	}
	else // if queue is not empty, it inserts process according to below of the code
	{
		process *temp = this->head;
		process *temp2 = nullptr;

		if(temp->getNext() == nullptr) //if queue has a one process, insert process head of queue or insert process next of head of queue
		{
			if(newProcess->getArrivalTime() > temp->getArrivalTime())
			{
				temp->setNext(newProcess);
			}
			else
			{
				newProcess->setNext(temp);
				this->head = newProcess;
			}
		}
		else // if queue has more than one process, it is inserted according to below of the code
		{
			while(newProcess->getArrivalTime() > temp->getArrivalTime() && temp->getNext() != nullptr) // searching the process which it's priority bigger than our process's priority
			{
				temp2 = temp;
				temp = temp->getNext();
			}
			if(temp->getNext() == nullptr && temp->getArrivalTime() > newProcess->getArrivalTime()) // inserting our process in previous of the process which we found if we should insert the our process at end of the queue
			{
				temp2->setNext(newProcess);
				newProcess->setNext(temp);
			}
			if(temp->getNext() == nullptr && temp->getArrivalTime() <= newProcess->getArrivalTime()) // inserting our node in next of node which we found if we should insert the our node at previous of end of the linked list
			{
				temp->setNext(newProcess);
				//newProcess->setNext(nullptr);
			}
			else
			{
				if(temp2!=nullptr) // if we should insert the process between next of head of queue and previous of end of queue
				{
					newProcess->setNext(temp);
					temp2->setNext(newProcess);
				}
				else
				{
					newProcess->setNext(temp);
					head = newProcess;
				}
			}
		}
	}
	this->incrSize(); // increment size of queue for each insertation
}

