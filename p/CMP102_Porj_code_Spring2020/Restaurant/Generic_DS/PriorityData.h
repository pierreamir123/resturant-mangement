#pragma once
#ifndef __PriorityData_H_
#define _priorityData_H_

template <class T>
class PriorityData
{
	T data;
	int priority;

public:

	PriorityData ( );
	PriorityData ( T d, int p = 0 );

	void setData ( T d );
	void setPriority ( int p );

	T getData () const;
	int getPriority () const;

	~PriorityData ();
};

template <class T>
PriorityData<T> :: PriorityData ( )
{
	priority = 0;
}

template <class T>
PriorityData<T> :: PriorityData ( T d, int p )
{
	data = d;
	setPriority ( p );
}

template <class T>
void PriorityData<T> :: setData ( T d )
{
	data = d;
}

template <class T>
void PriorityData<T> :: setPriority ( int p )
{
	priority = ( p >= 0 && p <= 10 ) ? p : 0;
}

template <class T>
T PriorityData<T> :: getData () const
{
	return data;
}

template <class T>
int PriorityData<T> :: getPriority () const
{
	return priority;
}

template <class T>
PriorityData<T> :: ~PriorityData ()
{

}
#endif