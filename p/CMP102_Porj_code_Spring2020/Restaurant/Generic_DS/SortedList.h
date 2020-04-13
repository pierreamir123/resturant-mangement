#pragma once
#ifndef __SortedList_H_
#define _SortedList_H_
#include "Node.h"

template <class T>

class SortedList
{
	Node<T>* head;
	Node<T>* GetNodeAt ( int position ) const;
	Node<T>* GetPrevOf ( const T & anEntry ) const;

public:

	SortedList ();

	bool isEmpty () const;
	int getLength () const;
	bool insert ( int newPosition, const T & newEntry );
	bool insertSorted ( const T & newEntry );
	bool remove ( int position );           // Ambiguity fi 7alet en T integar
	bool remove (const T & anEntry );      // Ambiguity fi 7alet en T integar
	void clear ();
	bool getEntry ( int position, T & anEntry ) const;
	bool replace ( int position, const T & newEntry, T & oldEntry ); 
	T* toArray ( int & count );

	virtual ~SortedList ();
};

template <class T>
SortedList<T> :: SortedList ()
{
	head = nullptr;
}

template <class T>
Node<T>* SortedList<T> :: GetNodeAt ( int position ) const
{
	if ( position < 0 || position >  getLength () -1  )
	{
		return nullptr;
	}

	Node<T>* nptr = head;
	for ( int i=0; i<position; i++ )
	{
		nptr = nptr ->getNext();
	}

	return nptr;
}

template <class T>
Node<T>* SortedList<T> :: GetPrevOf ( const T & anEntry ) const
{
	Node<T>* nptr = head;
	if ( nptr == nullptr || nptr ->getNext () == nullptr )
	{
		return nullptr;
	}

	while ( nptr ->getNext() != nullptr && nptr ->getNext() ->getItem() != anEntry )
	{
		nptr = nptr ->getNext();
	}

	if ( nptr ->getNext() == nullptr )
	{
		return nullptr;
	}
	else 
	{
		return nptr; 
	}
}

template <class T>
bool SortedList<T> :: insert ( int newPosition, const T & newEntry )
{
	if ( newPosition < 0 || newPosition > getLength() )
	{
		return false;
	}

	Node<T>* newNode = new Node<T> ( newEntry );
	if ( newNode == nullptr )
	{
		return false;
	}

	if ( newPosition == 0 )
	{
		newNode ->setNext( head );
		head = newNode;
	}
	else 
	{
		Node<T>* prevNode = GetNodeAt ( newPosition -1 );
		newNode ->setNext ( prevNode ->getNext() );
		prevNode ->setNext ( newNode );
	}

	return true;
}

template <class T>
bool SortedList<T> :: insertSorted ( const T & newEntry )   //project Note: momken lama a-sort el cooks maslan, a3mel operator overloading eni bakoon bakaren been el cook-speed
{
	Node<T>* newNode = new Node<T> ( newEntry );
	if ( newNode == nullptr )
	{
		return false;
	}

	Node<T>* nptr = head;

	if ( nptr == nullptr )
	{
		head = newNode;
	}
	else if ( newEntry < nptr ->getItem()  )
	{
		newNode ->setNext( head );
		head = newNode;
	}
	else 
	{
		while ( nptr ->getNext() != nullptr && nptr ->getNext() ->getItem() <= newEntry )
		{
			nptr = nptr ->getNext();
		}

		newNode ->setNext ( nptr ->getNext() );
		nptr ->setNext ( newNode );
	}
	return true;
}

template <class T>
bool SortedList<T> :: remove ( int position )
{
	if ( position < 0 || position > getLength()- 1 )
	{
		return false;
	}

	Node<T>* nodeToDelete = nullptr;
	if ( position == 0 )
	{
		nodeToDelete = head;
		head = head ->getNext();
	}
	else 
	{
		Node<T>* prevNode = GetNodeAt ( position -1 );
		nodeToDelete = prevNode ->getNext();
		prevNode ->setNext ( nodeToDelete ->getNext() );
	}

	delete nodeToDelete;
	return true;
}

template <class T>
bool SortedList<T> :: remove ( const T & anEntry )
{
	if ( head == nullptr )
	{
		return false;
	}

	if ( head ->getItem () == anEntry )
	{
		Node<T>* nodeToDelete = head;
		head = head ->getNext();
		delete nodeToDelete;
		return true;
	}

	Node<T>* prevNode = GetPrevOf ( anEntry );

	if ( prevNode == nullptr )
	{
		return false;
	}
	else
	{
		Node<T>* nodeToDelete = prevNode ->getNext();
		prevNode ->setNext ( nodeToDelete ->getNext() );
		delete nodeToDelete;
		return true;
	}

}

template <class T>
bool SortedList<T> :: isEmpty () const
{
	return ( head == nullptr );
}

template <class T>
int SortedList<T> :: getLength () const
{
	int count = 0;
	Node<T>* nptr = head;
	while ( nptr != nullptr )
	{
		count++;
		nptr = nptr ->getNext();
	}
	return count;
}

template <class T>
void SortedList<T> :: clear ()
{
	while ( !isEmpty() )
	{
		remove(0);
	}
}

template <class T>
bool SortedList<T> :: getEntry ( int position, T & anEntry ) const
{
	Node<T>* required = GetNodeAt ( position );
	if ( required == nullptr )
	{
		return false;
	}

	anEntry = required ->getItem();
	return true;

}

template <class T>
bool SortedList<T> :: replace ( int position, const T & newEntry, T & oldEntry )
{
	Node<T>* required = GetNodeAt ( position );

	if ( required == nullptr )
	{
		return false;
	}

	oldEntry= required ->getItem();
	required ->setItem ( newEntry );
	return true;
}

template <class T>
T* SortedList<T> :: toArray ( int & count )
{
	count = getLength();
	T* Arr= new T[count];
	Node<T>* p = head;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template <class T>
SortedList<T> :: ~SortedList ()
{
	clear();
}
#endif