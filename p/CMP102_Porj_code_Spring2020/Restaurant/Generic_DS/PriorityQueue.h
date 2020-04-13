#pragma once
#ifndef __PriorityQueue_H_
#define _priorityQueue_H_
#include "PriorityData.h"
#include "Node.h"

template <class T>
class PriorityQueue
{
	Node<PriorityData<T>>* front;    // heya heya el head
	Node<PriorityData<T>>* rear;

public:

	PriorityQueue ();

	bool isEmpty () const;
	bool Enqueue ( const PriorityData<T> newEntry );
	bool Dequeue ( T & anEntry );              // shoof law m7taga tet8ayar wel parameter yb2a no3o PriorityData mesh T wala la2 ?
	bool peekFront ( T & anEntry ) const;
	T* toArray ( int & count );
	int QueueCount () const;

	virtual ~PriorityQueue ();
};



template <class T>
PriorityQueue<T> :: PriorityQueue ()
{
	front = nullptr;
	rear = nullptr;
}

template <class T>
bool PriorityQueue<T> :: peekFront ( T & anEntry ) const
{
	if ( isEmpty() )
	{
		return false;
	}

	anEntry = front ->getItem();
	return true;
}

template <class T>
int PriorityQueue<T> :: QueueCount () const
{
	int count = 0;
	Node<PriorityData<T>>* nptr = front;

	while ( nptr != nullptr )
	{
		count++;
		nptr = nptr ->getNext();
	}

	return count;
}

template <class T>
bool PriorityQueue<T> :: isEmpty () const
{
	return ( rear == nullptr && front == nullptr );
}

template <class T>
bool PriorityQueue<T> :: Dequeue ( T & anEntry )
{
	if ( front == nullptr )
	{
		return false;
	}

	if ( front == rear )
	{
		rear = nullptr;
	}

	Node<PriorityData<T>>* nodeToDelete = front;
	anEntry = nodeToDelete ->getItem().getData();
	front = front ->getNext();
	delete nodeToDelete;
	return true;
}

template <class T>
bool PriorityQueue<T> :: Enqueue ( const PriorityData<T> newEntry )
{
	Node<PriorityData<T>>* newNode = new Node<PriorityData<T>> ( newEntry );

	if ( newNode == nullptr )
	{
		return false;
	}

	if ( rear == nullptr )
	{
		front = newNode;
		rear = newNode;
	} 
	else 
	{
		Node<PriorityData<T>>* nptr = front;
		if ( newEntry.getPriority() > nptr ->getItem().getPriority()  )
		{
			newNode ->setNext( front );
			front = newNode;
		}
		else
		{
			while ( nptr ->getNext() != nullptr && nptr ->getNext() ->getItem().getPriority() >= newEntry.getPriority() ) // law waraha null, yb2a 5alas ha3mel el new node ba3deha, lakn law feh node waraha, ha-check 3aleha el awl
			{
				nptr = nptr ->getNext();
			}

			if ( nptr ->getNext() == nullptr )
			{
				rear = newNode;
			}
			newNode ->setNext ( nptr ->getNext() );
			nptr ->setNext ( newNode );
		}
	}

	return true;
}

template <class T>
T* PriorityQueue<T> :: toArray ( int & count )
{
	count = QueueCount();
	T* Arr= new T[count];
	Node<PriorityData<T>>* p = front;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem().getData();
		p = p->getNext();
	}
	return Arr;
}

template <class T>
PriorityQueue<T> :: ~PriorityQueue ()
{

	T n;

	while ( Dequeue ( n ) )
	{

	}

}
#endif